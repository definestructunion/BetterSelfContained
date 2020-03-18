#include "../Impl/ImplLinux.hpp"
#include "../coreclrhost.h"
#include "../Util/Utilities.hpp"

#include <iostream>
#define LOG(X) std::cout << X << std::endl

int main() {
    SelfContainedConfig config("config.json");
    std::string executingPath = getExecutingPath();
    std::string fsSeparator = getFsSeparator();
    std::string clrName = getClrName();

    std::string coreClrPath = executingPath + fsSeparator + config.runtimePath + fsSeparator + clrName;
    std::string mainAssemblyPath = executingPath + config.assemblyName;

    void* coreClr = loadLibrary(coreClrPath);

    coreclr_initialize_ptr initializeCoreClr = (coreclr_initialize_ptr)dlsym(coreClr, "coreclr_initialize");
    coreclr_execute_assembly_ptr executeAssembly = (coreclr_execute_assembly_ptr)dlsym(coreClr, "coreclr_execute_assembly");
    coreclr_shutdown_ptr shutdownCoreClr = (coreclr_shutdown_ptr)dlsym(coreClr, "coreclr_shutdown");

    std::string tpaList;
    buildTPAList(config, getRuntimeLibraries(), executingPath, fsSeparator, getDelimiter(), tpaList);
    LOG(tpaList);


    const char* propertyKeys[] = {
            "TRUSTED_PLATFORM_ASSEMBLIES" // Trusted assemblies
    };

    const char* propertyValues[] = {
            tpaList.c_str()
    };


    void* hostHandle;
    unsigned int domainId;

    int hr = initializeCoreClr(
            executingPath.c_str(),                  // App base path
            config.domainName.c_str(),              // AppDomain friendly name
            sizeof(propertyKeys) / sizeof(char*),   // Property count
            propertyKeys,                           // Property names
            propertyValues,                         // Property values
            &hostHandle,                            // Host handle
            &domainId);                             // AppDomain ID

    if (hr >= 0)
    {
        printf("CoreCLR started\n");
    }
    else
    {
        printf("coreclr_initialize failed - status: 0x%08x\n", hr);
        return -1;
    }

    int exitCode = 0;

    const char** clrArgs = new const char*[config.clrArgs.size()];
    for(int i = 0; i < config.clrArgs.size(); ++i)
        clrArgs[i] = config.clrArgs[i].c_str();


    hr = executeAssembly(
            hostHandle,
            domainId,
            config.clrArgs.size(),
            clrArgs,
            config.assemblyName.c_str(),
            (unsigned int*)&exitCode);

    /*hr = executeAssembly(
            hostHandle,
            domainId,
            0,
            nullptr,
            //reinterpret_cast<const char **>(argv),
            "Hedgemen.dll",
            (unsigned int*)&exitCode);*/

    hr = shutdownCoreClr(hostHandle, domainId);

    //delete[] clrArgs;

    return exitCode;
}
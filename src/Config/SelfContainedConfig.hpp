#ifndef BETTERSELFCONTAINED_SELFCONTAINEDCONFIG_HPP
#define BETTERSELFCONTAINED_SELFCONTAINEDCONFIG_HPP

#include <string>
#include <vector>
#include <filesystem>

struct SelfContainedConfig {
    std::string assemblyName;
    std::string domainName;
    std::string runtimePath;
    std::vector<std::string> clrArgs;
    std::vector<std::string> referencedDll;
    bool grabAllInRuntimePath;

    SelfContainedConfig(std::string configName);
    ~SelfContainedConfig();

private:
    void readAndInit(const std::string& configName);
};

#endif //BETTERSELFCONTAINED_SELFCONTAINEDCONFIG_HPP

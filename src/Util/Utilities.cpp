#include "Utilities.hpp"
#include <filesystem>

#include <iostream>

std::string getExecutingPath() {
    return std::filesystem::current_path().string();
}

void buildTPAList(
        const SelfContainedConfig& config,
        const std::vector<std::string>& runtimeLibraries,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList) {

    if(config.grabAllInRuntimePath) {
        buildTPAListGrabAll(config, executingPath, fsSeparator, pathDelimiter, tpaList);
    } else {
        buildTPAListGrabRuntime(config, runtimeLibraries, executingPath, fsSeparator, pathDelimiter, tpaList);
    }

    buildTPAListGrabReferenced(config, executingPath, fsSeparator, pathDelimiter, tpaList);

    // remove the last PathDelimiter of the tpaList
    if(tpaList[tpaList.size() - 1] == pathDelimiter[0])
        tpaList.pop_back();
    if(tpaList[tpaList.size() - 1] == fsSeparator[0])
        tpaList.pop_back();
}

void buildTPAListGrabAll(
        const SelfContainedConfig& config,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList) {

    std::string directory = executingPath + fsSeparator + config.runtimePath;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        tpaList.append(entry.path().string());
        tpaList.append(pathDelimiter);
    }
}

void buildTPAListGrabReferenced(
        const SelfContainedConfig& config,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList) {

    std::string directory = executingPath;
    std::vector<std::string> referencedDll = config.referencedDll;

    for(int i = 0; i < referencedDll.size(); ++i) {
        std::filesystem::path file(referencedDll[i]);
        std::string path = directory + fsSeparator + file.string();

        tpaList.append(path);
        tpaList.append(pathDelimiter);
    }
}

void buildTPAListGrabRuntime(
        const SelfContainedConfig& config,
        const std::vector<std::string>& runtimeLibraries,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList) {

    std::cout << "Grabbing Runtime" << std::endl;

    std::string directory = executingPath + fsSeparator + config.runtimePath;

    for(int i = 0; i < runtimeLibraries.size(); ++i) {
        std::filesystem::path file(runtimeLibraries[i]);
        std::string path = directory + fsSeparator + file.string();

        tpaList.append(path);
        tpaList.append(pathDelimiter);
    }
}
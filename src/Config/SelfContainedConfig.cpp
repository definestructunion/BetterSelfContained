#include "SelfContainedConfig.hpp"

#include <fstream>
#include "../Vendor/nlohmann/json.hpp"

#include <iostream>

SelfContainedConfig::SelfContainedConfig(std::string configFile) {
    readAndInit(configFile);
}

SelfContainedConfig::~SelfContainedConfig() {

}

void SelfContainedConfig::readAndInit(const std::string& configName) {
    std::ifstream file;
    file.open(configName);

    nlohmann::json json = nlohmann::json::parse(file);
    json.at("assemblyName").get_to(assemblyName);
    json.at("domainName").get_to(domainName);
    json.at("runtimePath").get_to(runtimePath);
    json.at("clrArgs").get_to(clrArgs);
    json.at("referencedDll").get_to(referencedDll);
    json.at("grabAllInRuntimePath").get_to(grabAllInRuntimePath);

    file.close();
}
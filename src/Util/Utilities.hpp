#ifndef BETTERSELFCONTAINED_UTILITIES_HPP
#define BETTERSELFCONTAINED_UTILITIES_HPP

#include "../Config/SelfContainedConfig.hpp"
#include <string>

std::string getExecutingPath();

void buildTPAList(
        const SelfContainedConfig& config,
        const std::vector<std::string>& runtimeLibraries,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList);

void buildTPAListGrabAll(
        const SelfContainedConfig& config,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList);

void buildTPAListGrabReferenced(
        const SelfContainedConfig& config,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList);

void buildTPAListGrabRuntime(
        const SelfContainedConfig& config,
        const std::vector<std::string>& runtimeLibraries,
        const std::string& executingPath,
        const std::string& fsSeparator,
        const std::string& pathDelimiter,
        std::string& tpaList);

#endif //BETTERSELFCONTAINED_UTILITIES_HPP

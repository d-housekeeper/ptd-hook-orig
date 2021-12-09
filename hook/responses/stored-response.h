#pragma once

#include "json.hpp"
#include <filesystem>
#include <string>

std::filesystem::path getResponsesPath();

std::string getStoredResponse(const std::string &apiName);

std::string loadResponsePmFromFile(const std::string &apiName);

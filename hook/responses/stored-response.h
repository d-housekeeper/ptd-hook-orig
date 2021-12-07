#pragma once

#include <filesystem>
#include <string>

std::filesystem::path getResponsesPath();

std::string loadResponsePmFromFile(const std::string &apiName);

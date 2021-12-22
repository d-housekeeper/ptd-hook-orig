#pragma once

#include "json.hpp"

nlohmann::json loadConfigFromFile();

bool getBooleanConfigValue(const nlohmann::json &config, const char *configKey);

int getIntConfigValue(const nlohmann::json &config, const char *configKey, int defaultValue);

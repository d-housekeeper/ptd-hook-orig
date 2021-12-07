#pragma once

#include "json.hpp"
#include <string>

struct ResponseLoaderContext {
  nlohmann::ordered_json loginResponse;
};

std::string loadResponse(const std::string &apiName, const std::string &requestPM);

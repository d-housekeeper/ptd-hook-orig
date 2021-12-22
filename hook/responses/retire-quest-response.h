#pragma once

#include "json.hpp"
#include <string>

struct ResponseLoaderContext;

std::string getRetireQuestResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

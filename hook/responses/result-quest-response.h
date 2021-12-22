#pragma once

#include "json.hpp"
#include <string>

struct ResponseLoaderContext;

std::string getResultQuestResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

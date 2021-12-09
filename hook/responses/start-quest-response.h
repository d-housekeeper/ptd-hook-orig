#pragma once

#include "json.hpp"

struct ResponseLoaderContext;

std::string getStartQuestResponse(ResponseLoaderContext *context, const nlohmann::json &json);

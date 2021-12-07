#pragma once

#include "json.hpp"

struct ResponseLoaderContext;

std::string getSetIdolClassResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

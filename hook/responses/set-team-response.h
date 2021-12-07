#pragma once

#include "json.hpp"

struct ResponseLoaderContext;

std::string getSetTeamResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

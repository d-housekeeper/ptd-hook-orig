#pragma once

#include "json.hpp"

struct ResponseLoaderContext;

std::string getSetFavoriteCharacterResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

#pragma once

#include "json.hpp"

struct ResponseLoaderContext;

std::string getEquipmentAvatarResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

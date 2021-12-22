#pragma once

#include "json.hpp"
#include <string>

struct ResponseLoaderContext;

std::string getStartLessonResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

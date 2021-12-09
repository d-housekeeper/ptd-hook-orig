#pragma once

#include "json.hpp"
#include <chrono>

std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> getCurrentTime();

nlohmann::ordered_json getBaseResponse();

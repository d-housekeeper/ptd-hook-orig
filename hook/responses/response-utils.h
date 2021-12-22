#pragma once

#include "json.hpp"
#include "time-utils.h"
#include <chrono>

sec_time_point getModifiedCurrentTime(const nlohmann::json &config);

nlohmann::ordered_json getBaseResponse();

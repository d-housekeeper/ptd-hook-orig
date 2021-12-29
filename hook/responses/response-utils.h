#pragma once

#include "json.hpp"
#include "time-utils.h"
#include <chrono>

date::sys_seconds getModifiedCurrentTime(const nlohmann::json &config);

nlohmann::ordered_json getBaseResponse();

int getRandomNumber(int maxNumber);

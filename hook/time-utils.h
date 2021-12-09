#pragma once

#include <chrono>

int getTimeZoneOffsetInMillis();

static const char *strDateTimeFormat = "%F %T";
static const char *mdDateTimeFormat = "%m/%d/%Y %T";

using sec_time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>;

sec_time_point getCurrentTime();

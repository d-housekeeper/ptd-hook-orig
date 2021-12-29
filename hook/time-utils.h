#pragma once

#include "date/date.h"
#include <chrono>

int getTimeZoneOffsetInMillis();

static const char *strDateTimeFormat = "%F %T";
static const char *mdDateTimeFormat = "%m/%d/%Y %T";

date::sys_seconds getCurrentTime();

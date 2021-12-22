#include "android-utils.h"
#include "config.h"
#include "date/date.h"
#include "json.hpp"
#include "time-utils.h"
#include <android/log.h>
#include <chrono>

using json = nlohmann::json;

namespace chrono = std::chrono;

nlohmann::ordered_json getBaseResponse() {
  json config = loadConfigFromFile();
  std::string fakeTimeType;
  std::string fakeTimeValue;
  try {
    fakeTimeType = config["fakeTimeType"];
    fakeTimeValue = config["fakeTimeValue"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Invalid fakeTime config: %s", e.what());
    fakeTimeType = fakeTimeValue = "";
  }

  std::istringstream is(fakeTimeValue);
  is.exceptions(std::istringstream::failbit | std::istringstream::badbit);
  sec_time_point now = getCurrentTime();
  try {
    if (fakeTimeType == "fixedDateAndTime") {
      is >> date::parse(strDateTimeFormat, now);
    } else if (fakeTimeType == "fixedDate") {
      date::sys_days days;
      is >> date::parse("%F", days);

      date::sys_days datePart = date::floor<date::days>(now);
      chrono::duration timePart = now - datePart;
      now = floor<chrono::seconds>(days + timePart);
    } else if (fakeTimeType == "fixedYear") {
      date::year_month_day inYMD;
      is >> date::parse("%Y", inYMD);

      date::year_month_day today{floor<date::days>(now)};
      date::years yearDiff = date::years{inYMD.year() - today.year()};
      date::sys_days datePart = date::floor<date::days>(now);
      chrono::duration timePart = now - datePart;
      now = floor<chrono::seconds>(date::sys_days{today} + yearDiff + timePart);
    }
  } catch (std::istringstream::failure &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Invalid value \"%s\" for fakeTimeType %s: %s",
                        fakeTimeValue.c_str(), fakeTimeType.c_str(), e.what());
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Using current time");
  }

  std::string formattedDate = date::format(strDateTimeFormat, now);
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "fakeTimeType: %s Current date: %s", fakeTimeType.c_str(),
                      formattedDate.c_str());

  return {
      {"np", 0},
      {"tm", formattedDate},
      {"rt", 0},
  };
}

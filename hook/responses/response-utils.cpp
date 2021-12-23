#include "android-utils.h"
#include "config.h"
#include "date/date.h"
#include "json.hpp"
#include "time-utils.h"
#include <android/log.h>
#include <chrono>
#include <random>

using json = nlohmann::json;

namespace chrono = std::chrono;

void logInvalidValueError(const std::string &fakeTimeValue, const std::string &fakeTimeType, const std::exception &e) {
  __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Invalid value \"%s\" for fakeTimeType %s: %s",
                      fakeTimeValue.c_str(), fakeTimeType.c_str(), e.what());
  __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Using current time");
}

sec_time_point getModifiedCurrentTime(const json &config) {
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
  sec_time_point origNow = now;
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
      int inYear = std::stoi(fakeTimeValue);

      date::year_month_day today{floor<date::days>(now)};
      date::years yearDiff = date::years{date::year{inYear} - today.year()};
      date::sys_days datePart = date::floor<date::days>(now);
      chrono::duration timePart = now - datePart;
      now = floor<chrono::seconds>(date::sys_days{today} + yearDiff + timePart);
    }
  } catch (std::istringstream::failure &e) {
    logInvalidValueError(fakeTimeValue, fakeTimeType, e);
  } catch (std::invalid_argument &e) {
    logInvalidValueError(fakeTimeValue, fakeTimeType, e);
  } catch (std::out_of_range &e) {
    logInvalidValueError(fakeTimeValue, fakeTimeType, e);
  }

  date::year_month_day today{floor<date::days>(now)};
  if (today.year() < date::year{2017}) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag,
                        "Year part must be at least 2017 or higher. Using current date instead");
    return origNow;
  }

  return now;
}

nlohmann::ordered_json getBaseResponse() {
  json config = loadConfigFromFile();
  sec_time_point now = getModifiedCurrentTime(config);
  std::string formattedDateTime = date::format(strDateTimeFormat, now);
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Current time: %s", formattedDateTime.c_str());

  return {
      {"np", 0},
      {"tm", formattedDateTime},
      {"rt", 0},
  };
}

int getRandomNumber(int maxNumber) {
  static std::minstd_rand eng{std::random_device{}()};
  std::uniform_int_distribution<int> dist{0, maxNumber};
  return dist(eng);
}

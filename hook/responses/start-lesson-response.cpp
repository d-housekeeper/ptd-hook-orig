#include "start-lesson-response.h"
#include "android-utils.h"
#include "config.h"
#include "date/date.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include "response-utils.h"
#include <android/log.h>

using json = nlohmann::json;

namespace chrono = std::chrono;

std::string getStartLessonResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON) {
  std::string characterID;
  std::string lessonID;
  try {
    characterID = requestJSON["cId"];
    lessonID = requestJSON["lsId"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid StartLesson request: %s", e.what());
    return "";
  }

  json config = loadConfigFromFile();
  sec_time_point now = getModifiedCurrentTime(config);
  sec_time_point endTime = now + chrono::seconds{60};
  json responseJson = getBaseResponse();
  // clang-format off
  responseJson.merge_patch({
    {"rp", {
      {"crLs", {
        {characterID, {
          {"lsId", lessonID},
          {"ed", date::format(strDateTimeFormat, endTime)},
          {"sc", 1},
          {"exp", {
            {"A", 0},
            {"B", 0},
            {"C", 0},
            {"D", 0},
          }},
          {"bio", 0},
          {"ev", ""},
          {"rn", 0},
        }},
      }},
    }},
  });
  // clang-format on

  return responseJson.dump();
}

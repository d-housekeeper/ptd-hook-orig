#include "android-utils.h"
#include "json.hpp"
#include "responses/start-quest-response.h"
#include "string-utils.h"
#include <android/log.h>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

static std::string loadResponsePmFromFile(const std::string &apiName);
static std::string wrapResponsePm(const std::string &responsePm);

std::string loadResponse(const std::string &apiName, const std::string &requestPM) {
  if (apiName == "StartQuest") {
    return wrapResponsePm(getStartQuestResponse(requestPM));
  }

  std::string responsePm = loadResponsePmFromFile(apiName);
  return wrapResponsePm(responsePm);
}

static std::string loadResponsePmFromFile(const std::string &apiName) {
  std::string fileName = string_format("%s/Responses/%s.json", getExternalFilesDir(), apiName.c_str());

  std::ifstream t(fileName);
  if (t.fail()) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to load response file from %s", fileName.c_str());
  } else {
    __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Loading response file from %s", fileName.c_str());
  }
  std::stringstream buffer;
  buffer << t.rdbuf();

  return buffer.str();
}

static std::string wrapResponsePm(const std::string &responsePm) {
  json responseJson = {{"pm", responsePm}};

  return responseJson.dump();
}

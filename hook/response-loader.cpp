#include "json.hpp"
#include "start-quest-response.h"
#include "utils.h"
#include <android/log.h>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

const char *nativeTokenResponse = R"({"rp":{"nt":"none"}})";

static std::string loadResponsePmFromFile(const std::string &apiName);
static std::string wrapResponsePm(const std::string &responsePm);

std::string loadResponse(const std::string &apiName, const std::string &requestPM) {
  if (apiName == "GetNativeToken") {
    return wrapResponsePm(std::string(nativeTokenResponse));
  } else if (apiName == "StartQuest") {
    return wrapResponsePm(getStartQuestResponse(requestPM));
  }

  std::string responsePm = loadResponsePmFromFile(apiName);
  return wrapResponsePm(responsePm);
}

static std::string loadResponsePmFromFile(const std::string &apiName) {
  std::string fileName = string_format("%s/Responses/%s.json", filesPath, apiName.c_str());

  std::ifstream t(fileName);
  if (t.fail()) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to load response file from %s", fileName.c_str());
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

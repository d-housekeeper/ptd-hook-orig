#include "json.hpp"
#include "utils.h"
#include <android/log.h>
#include <fstream>
#include <sstream>
#include <string.h>

using json = nlohmann::json;

const char *dataPath = "/storage/emulated/0/Android/data/"
                       "com.square_enix.android_googleplay.PTD/files";
const char *nativeTokenResponse = R"({"rp":{"nt":"none"}})";

static std::string loadResponsePmFromFile(const char *apiName);
static std::string wrapResponsePm(const std::string &responsePm);

std::string loadResponse(const char *apiName) {
  if (strncmp(apiName, "GetNativeToken", 14) == 0) {
    return wrapResponsePm(std::string(nativeTokenResponse));
  }

  std::string responsePm = loadResponsePmFromFile(apiName);
  return wrapResponsePm(responsePm);
}

static std::string loadResponsePmFromFile(const char *apiName) {
  std::string fileName = string_format("%s/%s.json", dataPath, apiName);

  std::ifstream t(fileName);
  if (t.fail()) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag,
                        "Failed to load response file from %s",
                        fileName.c_str());
  } else {
    __android_log_print(ANDROID_LOG_DEBUG, androidLogTag,
                        "Loading1 response file from %s", fileName.c_str());
  }
  std::stringstream buffer;
  buffer << t.rdbuf();

  return buffer.str();
}

static std::string wrapResponsePm(const std::string &responsePm) {
  json responseJson = {{"pm", responsePm}};

  return std::string(responseJson.dump());
}

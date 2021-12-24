#include "stored-response.h"
#include "android-storage-path.h"
#include "android-utils.h"
#include "response-utils.h"
#include <android/log.h>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::filesystem::path getResponsesPath() {
  fs::path p{getExternalFilesDir()};
  return p.append("Responses");
}

std::string getStoredResponse(const std::string &apiName) {
  std::string responsePM = loadResponsePmFromFile(apiName);
  if (responsePM.empty()) {
    return "";
  }

  ordered_json storedJSON;
  try {
    storedJSON = ordered_json::parse(responsePM);
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to parse %s response: %s", apiName.c_str(), e.what());
    return "";
  }

  try {
    if (apiName != "GetNativeToken") {
      ordered_json baseJSON = getBaseResponse();
      storedJSON.merge_patch(baseJSON);
    }

    return storedJSON.dump();
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to patch %s response: %s", apiName.c_str(), e.what());
    return "";
  }
}

std::string loadResponsePmFromFile(const std::string &apiName) {
  std::string baseName = apiName + ".json";
  std::string fileName = getResponsesPath().append(baseName).string();

  std::ifstream t;
  std::stringstream buffer;
  t.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    t.open(fileName);
    buffer << t.rdbuf();
    t.close();
  } catch (std::ifstream::failure &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to read response file from %s: %s", fileName.c_str(),
                        e.what());
    return "";
  }

  return buffer.str();
}

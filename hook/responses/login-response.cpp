#include "login-response.h"
#include "android-utils.h"
#include "json.hpp"
#include "response-loader.h"
#include "stored-response.h"
#include <android/log.h>
#include <chrono>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;
namespace fs = std::filesystem;

bool loadParsedLoginResponse(ResponseLoaderContext *context, const std::string &responsePM) {
  try {
    context->loginResponse = ordered_json::parse(responsePM);
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid Login response: %s", e.what());
    return false;
  }

  return true;
}

bool saveLoginResponse(ResponseLoaderContext *context) {
  std::string tmpFileName = getResponsesPath().append("Login.tmp.json").string();
  std::string fileName = getResponsesPath().append("Login.json").string();

  std::ofstream out;
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Saving Login response to %s", fileName.c_str());
  std::chrono::steady_clock::time_point beginTime = std::chrono::steady_clock::now();
  try {
    out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    out.open(tmpFileName);
    out << context->loginResponse.dump();
    out.close();
  } catch (std::ifstream::failure e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to write Login response to file at %s: %s",
                        fileName.c_str(), e.what());
    return false;
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to encode Login response to JSON at %s: %s",
                        fileName.c_str(), e.what());
    return false;
  }

  try {
    std::filesystem::rename(tmpFileName, fileName);
  } catch (std::filesystem::filesystem_error &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to rename temporary Login response %s to %s: %s",
                        tmpFileName.c_str(), fileName.c_str(), e.what());
  }

  std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Saving Login response took %lldms",
                      std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count());

  return true;
}

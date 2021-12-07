#include "stored-response.h"
#include "android-utils.h"
#include "string-utils.h"
#include <android/log.h>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

std::filesystem::path getResponsesPath() {
  fs::path p{getExternalFilesDir()};
  return p.append("Responses");
}

std::string loadResponsePmFromFile(const std::string &apiName) {
  std::string baseName = string_format("%s.json", apiName.c_str());
  std::string fileName = getResponsesPath().append(baseName).string();

  std::ifstream t;
  std::stringstream buffer;
  t.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    t.open(fileName);
    buffer << t.rdbuf();
    t.close();
  } catch (std::ifstream::failure e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to read response file from %s: %s", fileName.c_str(),
                        e.what());
    return "";
  }

  return buffer.str();
}

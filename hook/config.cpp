#include "config.h"
#include "android-storage-path.h"
#include "android-utils.h"
#include <android/log.h>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

static json defaultConfig = {
    {"fakeTimeType", "disabled"},
    {"fakeTimeValue", ""},
    {"enableUIMod", false},
    {"portraitHomeScene", false},
    {"portraitMyRoomScene", false},
    {"portraitPhotoModeScene", false},
    {"hideHomeSceneUIElements", false},
    {"hideMyRoomSceneUIElements", false},
    {"adjustPortraitModeCameraPos", false},
    {"cameraYPosOffset", 33},
};

static void logUsingDefaultConfigMessage() {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Using default config");
}

json loadConfigFromFile() {
  fs::path p = fs::path(getExternalFilesDir()).append("ptd-hook-config.json");
  std::string fileName = p.string();

  std::ifstream t;
  std::stringstream buffer;
  t.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    t.open(fileName);
    buffer << t.rdbuf();
    t.close();
  } catch (std::ifstream::failure &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to read config file from %s: %s", fileName.c_str(),
                        e.what());
    logUsingDefaultConfigMessage();
    return defaultConfig;
  }

  try {
    return json::parse(buffer);
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to parse config file: %s", e.what());
  }

  logUsingDefaultConfigMessage();
  return defaultConfig;
}

bool getBooleanConfigValue(const nlohmann::json &config, const char *configKey) {
  bool value = false;
  try {
    value = config[configKey];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Invalid boolean config value for %s: %s", configKey,
                        e.what());
  }

  return value;
}

int getIntConfigValue(const nlohmann::json &config, const char *configKey, int defaultValue) {
  int value = defaultValue;
  try {
    value = config[configKey];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Invalid integer config value for %s: %s", configKey,
                        e.what());
  }

  return value;
}

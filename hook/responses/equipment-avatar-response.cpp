#include "equipment-avatar-response.h"
#include "android-utils.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include <android/log.h>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::string getEquipmentAvatarResponse(ResponseLoaderContext *context, const json &requestJSON) {
  json inAvatars;
  try {
    inAvatars = requestJSON["av"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid EquipmentAvatar request: %s", e.what());
    return "";
  }

  try {
    std::string strAvatars = context->loginResponse["td"]["User"]["eqAv"];
    ordered_json avatars = ordered_json::parse(strAvatars);
    avatars.merge_patch(inAvatars);
    context->loginResponse["td"]["User"]["eqAv"] = avatars.dump();
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag,
                        "Failed to patch Login response with EquipmentAvatar request: %s", e.what());
    return "";
  }

  if (!saveLoginResponse(context)) {
    return "";
  }

  // clang-format off
  json responseJson = {
    {"np", 0},
    {"tm", "2021-10-29 10:00:00"},
    {"rt", 0}
  };
  // clang-format on

  return responseJson.dump();
}

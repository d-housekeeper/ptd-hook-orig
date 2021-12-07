#include "set-idol-class-response.h"
#include "android-utils.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include <android/log.h>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::string getSetIdolClassResponse(ResponseLoaderContext *context, const json &requestJSON) {
  std::string characterID;
  std::string idolClass;
  try {
    characterID = requestJSON["cId"];
    idolClass = requestJSON["cls"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid SetIdolClass request: %s", e.what());
    return "";
  }

  try {
    std::string strCharacterStatuses = context->loginResponse["td"]["User"]["csts"];
    ordered_json characterStatuses = ordered_json::parse(strCharacterStatuses);
    characterStatuses[characterID]["cls"] = idolClass;
    context->loginResponse["td"]["User"]["csts"] = characterStatuses.dump();
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag,
                        "Failed to patch Login response with SetIdolClass request: %s", e.what());
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

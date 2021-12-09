#include "set-favorite-character-response.h"
#include "android-utils.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include "response-utils.h"
#include <android/log.h>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::string getSetFavoriteCharacterResponse(ResponseLoaderContext *context, const json &requestJSON) {
  std::string characterID;
  try {
    characterID = requestJSON["chId"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid SetFavoriteCharacter request: %s", e.what());
    return "";
  }

  try {
    context->loginResponse["td"]["User"]["fCrId"] = characterID;
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag,
                        "Failed to patch Login response with SetFavoriteCharacter: %s", e.what());
    return "";
  }

  if (!saveLoginResponse(context)) {
    return "";
  }

  return getBaseResponse().dump();
}

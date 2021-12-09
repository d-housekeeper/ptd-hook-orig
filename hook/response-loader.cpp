#include "response-loader.h"
#include "android-utils.h"
#include "json.hpp"
#include "responses/equipment-avatar-response.h"
#include "responses/login-response.h"
#include "responses/set-favorite-character-response.h"
#include "responses/set-idol-class-response.h"
#include "responses/set-team-response.h"
#include "responses/start-quest-response.h"
#include "responses/stored-response.h"
#include "string-utils.h"
#include <android/log.h>
#include <filesystem>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using ResponseLoaderFunc = std::function<std::string(ResponseLoaderContext *, json)>;
using ResponseLoaderMap = std::map<std::string, ResponseLoaderFunc>;

static std::string wrapResponsePm(const std::string &responsePm);

ResponseLoaderContext context;

std::string loadResponse(const std::string &apiName, const std::string &requestPM) {
  json requestJSON;
  try {
    requestJSON = json::parse(requestPM);
    __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Request: %s", requestJSON.dump().c_str());
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to parse %s request: %s", apiName.c_str(), e.what());
    return "";
  }

  ResponseLoaderMap responseLoaders = {
      {"Login", getLoginResponse},
      {"EquipmentAvatar", getEquipmentAvatarResponse},
      {"SetFavoriteCharacter", getSetFavoriteCharacterResponse},
      {"SetIdolClass", getSetIdolClassResponse},
      {"SetTeam", getSetTeamResponse},
      {"StartQuest", getStartQuestResponse},
  };
  std::string responsePM;
  ResponseLoaderMap::const_iterator responseLoaderIt = responseLoaders.find(apiName);
  if (responseLoaderIt != responseLoaders.end()) {
    ResponseLoaderFunc responseLoader = (*responseLoaderIt).second;
    responsePM = responseLoader(&context, requestJSON);
  } else {
    responsePM = getStoredResponse(apiName);
  }

  return wrapResponsePm(responsePM);
}

static std::string wrapResponsePm(const std::string &responsePm) {
  try {
    json responseJSON = {{"pm", responsePm}};
    return responseJSON.dump();
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to encode response JSON: %s", e.what());
  }

  return "";
}

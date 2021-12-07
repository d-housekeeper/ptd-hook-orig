#include "set-team-response.h"
#include "android-utils.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include <android/log.h>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

std::string getSetTeamResponse(ResponseLoaderContext *context, const json &requestJSON) {
  json inTeams;
  try {
    inTeams = requestJSON["teams"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid SetTeam request: %s", e.what());
    return "";
  }

  try {
    std::string strTeams = context->loginResponse["td"]["User"]["team"];
    ordered_json teams = ordered_json::parse(strTeams);
    teams.merge_patch(inTeams);
    context->loginResponse["td"]["User"]["team"] = teams.dump();
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to patch Login response with SetTeam request: %s",
                        e.what());
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

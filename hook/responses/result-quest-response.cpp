#include "result-quest-response.h"
#include "login-response.h"
#include "response-loader.h"
#include "response-utils.h"

using json = nlohmann::json;

std::string getResultQuestResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON) {
  clearPlayQuestData(context);

  if (!saveLoginResponse(context)) {
    return "";
  }

  json responseJSON = getBaseResponse();
  // clang-format off
  responseJSON.merge_patch({
    {"rp", {
      {"adExp", 0},
      {"gfbr", {}},
      {"adGco", 0},
      {"adFel", {
        {"A", 0},
        {"B", 0},
        {"C", 0},
        {"D", 0},
      }},
      {"adCst", {}},
    }},
  });
  // clang-format on

  return responseJSON.dump();
}

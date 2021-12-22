#include "retire-quest-response.h"
#include "login-response.h"
#include "response-loader.h"
#include "response-utils.h"

using json = nlohmann::json;

std::string getRetireQuestResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON) {
  clearPlayQuestData(context);

  if (!saveLoginResponse(context)) {
    return "";
  }

  return getBaseResponse().dump();
}

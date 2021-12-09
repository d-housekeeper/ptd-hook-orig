#include "json.hpp"
#include <string>

struct ResponseLoaderContext;

std::string getLoginResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON);

bool saveLoginResponse(ResponseLoaderContext *context);

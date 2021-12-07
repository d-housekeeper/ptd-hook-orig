#include "json.hpp"
#include <string>

struct ResponseLoaderContext;

bool loadParsedLoginResponse(ResponseLoaderContext *context, const std::string &response);

bool saveLoginResponse(ResponseLoaderContext *context);

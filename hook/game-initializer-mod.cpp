#include "game-initializer-mod.h"
#include "android-storage-path.h"
#include "android-utils.h"
#include "config.h"
#include "frida-gum.h"
#include "il2cpp-appdata.h"
#include "string-utils.h"
#include "time-utils.h"
#include "ui-mod.h"
#include <android/log.h>

using namespace app;
using json = nlohmann::json;

static void replacement_SceneTitleRoot_Initialize(SceneTitleRoot *__this, MethodInfo *method) {
  SceneTitleRoot_Initialize(__this, method);

  static bool gameInitializerModLoaded = false;
  if (gameInitializerModLoaded) {
    __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Game initializer mod already loaded");
    return;
  }

  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "caching values fetched from Java API");
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "externalFilesDir: %s", getExternalFilesDir());
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "timeZoneOffsetInMillis: %d", getTimeZoneOffsetInMillis());
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "initializing optional mods");
  json config = loadConfigFromFile();
  initScreenOrientationMod(config);
  gameInitializerModLoaded = true;
}

void initGameInitializerMod() {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Initializing Game initializer mod");
  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneTitleRoot_Initialize),
                          (void *)replacement_SceneTitleRoot_Initialize, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

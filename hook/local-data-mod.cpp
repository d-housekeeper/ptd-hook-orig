#include "frida-gum.h"
#include "il2cpp-appdata.h"
#include "utils.h"
#include <android/log.h>

using namespace app;

bool replacement_LocalData_get_DisuseGooglePlayService(LocalData *__this,
                                                       MethodInfo *method) {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag,
                      "LocalData_get_DisuseGooglePlayService");
  return true;
}

void initLocalDataMod() {
  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(
      interceptor, GSIZE_TO_POINTER(LocalData_get_DisuseGooglePlayService),
      (void *)replacement_LocalData_get_DisuseGooglePlayService, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

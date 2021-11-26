#include "api-mod.h"
#include "frida-gum.h"
#include "helpers.h"
#include "il2cpp-init.h"
#include "utils.h"

#include <android/log.h>
#include <dlfcn.h>

static bool allHooksLoaded = false;

static void initAllHooks();

static void *replacement_dlopen(const char *__filename, int __flag) {
  void *handle = dlopen(__filename, __flag);
  if (allHooksLoaded) {
    return handle;
  }

  if (stringEndsWith(__filename, libName)) {
    initAllHooks();
  }

  return handle;
}

void initDLOpenHook() {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag,
                      "Initializing dlopen hook");
  GumInterceptor *interceptor = gum_interceptor_obtain();
  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(
      interceptor,
      GSIZE_TO_POINTER(gum_module_find_export_by_name(nullptr, "dlopen")),
      (void *)replacement_dlopen, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

static void initAllHooks() {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag,
                      "Initializing all hooks");
  init_il2cpp();
  initApiMod();
  allHooksLoaded = true;
}

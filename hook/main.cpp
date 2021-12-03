#include "disable-connect-hook.h"
#include "dlopen-hook.h"
#include "frida-gum.h"
#include "utils.h"
#include <android/log.h>

__attribute__((constructor)) void hookMain() {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Initializing frida gum");
  gum_init_embedded();
  initDLOpenHook();
  initDisableConnectHook();
}

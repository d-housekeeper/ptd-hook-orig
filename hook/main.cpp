#include "android-utils.h"
#include "dlopen-hook.h"
#include "frida-gum.h"
#include <android/log.h>
#include <jni.h>

extern "C" JNIEXPORT void JNICALL Java_com_hook_HookLoader_initHook(JNIEnv *, jclass) {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Initializing frida gum");
  gum_init_embedded();
  initDLOpenHook();
}

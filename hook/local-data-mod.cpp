#include "android-utils.h"
#include "frida-gum.h"
#include "il2cpp-appdata.h"
#include <android/log.h>

using namespace app;

static String *replacement_EnvironmentData_get_UUID(EnvironmentData *__this, MethodInfo *method) {
  // Prevents terms of service dialog from showing up in case you don't have existing local data
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "EnvironmentData_get_UUID");
  return (String *)il2cpp_string_new("5b003217-14f9-42a1-a3b5-2c136eb30aa5");
}

static bool replacement_LocalData_get_DisuseGooglePlayService(LocalData *__this, MethodInfo *method) {
  // Prevents google sign in dialog from showing up when you run the game for the first time after restoring save data
  // from backup
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "LocalData_get_DisuseGooglePlayService");
  return true;
}

static List_1_System_Int32_ *replacement_LocalData_get_TutorialProgressData(LocalData *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "LocalData_get_TutorialProgressData");
  List_1_System_Int32_ *list = LocalData_get_TutorialProgressData(__this, method);
  MethodInfo *addMethod = (MethodInfo *)list->klass->vtable.Add.method;
  List_1_System_Int32__Clear(list, *List_1_System_Int32__Clear__MethodInfo);
  List_1_System_Int32__Add(list, 23, addMethod);
  List_1_System_Int32__Add(list, 16, addMethod);

  return list;
}

void initLocalDataMod() {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Initializing Local data mod");
  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(EnvironmentData_get_UUID),
                          (void *)replacement_EnvironmentData_get_UUID, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(LocalData_get_DisuseGooglePlayService),
                          (void *)replacement_LocalData_get_DisuseGooglePlayService, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(LocalData_get_TutorialProgressData),
                          (void *)replacement_LocalData_get_TutorialProgressData, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

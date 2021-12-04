#include "frida-gum.h"
#include "il2cpp-appdata.h"
#include "utils.h"
#include <android/log.h>

using namespace app;

String *replacement_EnvironmentData_get_UUID(EnvironmentData *__this, MethodInfo *method) {
  // Prevents terms of service dialog from showing up in case you don't have existing local data
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "EnvironmentData_get_UUID");
  return (String *)il2cpp_string_new("5b003217-14f9-42a1-a3b5-2c136eb30aa5");
}

bool replacement_LocalData_get_DisuseGooglePlayService(LocalData *__this, MethodInfo *method) {
  // Prevents google sign in dialog from showing up when you run the game for the first time after restoring save data
  // from backup
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "LocalData_get_DisuseGooglePlayService");
  return true;
}

Dictionary_2_System_String_System_Int32_ *replacement_LocalData_get_DownloadedMovieVer(LocalData *__this,
                                                                                       MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "LocalData_get_DownloadedMovieVer");
  Dictionary_2_System_String_System_Int32_ *dict = LocalData_get_DownloadedMovieVer(__this, method);
  MethodInfo *setItemMethod = (MethodInfo *)dict->klass->vtable.set_Item.method;
  Dictionary_2_System_String_System_Int32__Clear(dict, *Dictionary_2_System_String_System_Int32__Clear__MethodInfo);
  Dictionary_2_System_String_System_Int32__set_Item(
      dict, (String *)il2cpp_string_new("RCyo9jGyLHc4CaMe88zyyPq8TBCtYpCC/bb6246d6b4b41627d21be8fbcdbfb12b"), 1,
      setItemMethod);
  Dictionary_2_System_String_System_Int32__set_Item(
      dict, (String *)il2cpp_string_new("RCyo9jGyLHc4CaMe88zyyPq8TBCtYpCC/1d30d34334f1f008cd6aebb610acb1fa"), 1,
      setItemMethod);
  Dictionary_2_System_String_System_Int32__set_Item(
      dict, (String *)il2cpp_string_new("lKFWrl0Kkyscz80Fmzy6TENSHFtCJYla/Et7ZHjisO3QASNiuhMGeeiVQbUfIoqos"), 0,
      setItemMethod);
  return dict;
}

List_1_System_Int32_ *replacement_LocalData_get_TutorialProgressData(LocalData *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "LocalData_get_TutorialProgressData");
  List_1_System_Int32_ *list = LocalData_get_TutorialProgressData(__this, method);
  MethodInfo *addMethod = (MethodInfo *)list->klass->vtable.Add.method;
  List_1_System_Int32__Clear(list, *List_1_System_Int32__Clear__MethodInfo);
  List_1_System_Int32__Add(list, 23, addMethod);
  List_1_System_Int32__Add(list, 16, addMethod);

  return list;
}

void initLocalDataMod() {
  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(EnvironmentData_get_UUID),
                          (void *)replacement_EnvironmentData_get_UUID, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(LocalData_get_DisuseGooglePlayService),
                          (void *)replacement_LocalData_get_DisuseGooglePlayService, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(LocalData_get_DownloadedMovieVer),
                          (void *)replacement_LocalData_get_DownloadedMovieVer, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(LocalData_get_TutorialProgressData),
                          (void *)replacement_LocalData_get_TutorialProgressData, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

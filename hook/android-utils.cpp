#include "android-utils.h"
#include "helpers.h"
#include "il2cpp-appdata.h"
#include <memory>
#include <string>

using namespace app;

std::string externalStoragePath;

struct AndroidJavaObjectDisposer {
  void operator()(AndroidJavaObject *obj) const { AndroidJavaObject__Dispose(obj, nullptr); }
};

using AndroidJavaObjectPtr = std::unique_ptr<AndroidJavaObject, AndroidJavaObjectDisposer>;

AndroidJavaObjectPtr getUnityPlayerClass() {
  AndroidJavaClass *unityPlayerClass =
      (AndroidJavaClass *)il2cpp_object_new((Il2CppClass *)*AndroidJavaClass__TypeInfo);
  AndroidJavaClass__ctor(unityPlayerClass, (String *)il2cpp_string_new("com.unity3d.player.UnityPlayer"), nullptr);
  return AndroidJavaObjectPtr((AndroidJavaObject *)unityPlayerClass);
}

AndroidJavaObjectPtr getCurrentActivity(const AndroidJavaObjectPtr &unityPlayerClass) {
  return AndroidJavaObjectPtr(AndroidJavaObject_GetStatic_3(unityPlayerClass.get(),
                                                            (String *)il2cpp_string_new("currentActivity"),
                                                            *AndroidJavaObject_GetStatic_3__MethodInfo));
}

AndroidJavaObjectPtr getApplicationContext(const AndroidJavaObjectPtr &activity) {
  Object__Array *args = (Object__Array *)il2cpp_array_new((Il2CppClass *)*Object__Array__TypeInfo, 0);
  return AndroidJavaObjectPtr(AndroidJavaObject_Call_2(activity.get(),
                                                       (String *)il2cpp_string_new("getApplicationContext"), args,
                                                       *AndroidJavaObject_Call_2__MethodInfo));
}

AndroidJavaObjectPtr getExternalFilesDirFromContext(const AndroidJavaObjectPtr &context) {
  Object__Array *args = (Object__Array *)il2cpp_array_new((Il2CppClass *)*Object__Array__TypeInfo, 1);
  args->vector[0] = nullptr;
  return AndroidJavaObjectPtr(AndroidJavaObject_Call_2(
      context.get(), (String *)il2cpp_string_new("getExternalFilesDir"), args, *AndroidJavaObject_Call_2__MethodInfo));
}

String *getPathFromFilesDir(const AndroidJavaObjectPtr &filesDir) {
  Object__Array *args = (Object__Array *)il2cpp_array_new((Il2CppClass *)*Object__Array__TypeInfo, 0);
  return AndroidJavaObject_Call_3(filesDir.get(), (String *)il2cpp_string_new("getPath"), args,
                                  *AndroidJavaObject_Call_3__MethodInfo);
}

std::string getExternalFilesPathFromJNI() {
  AndroidJavaObjectPtr unityPlayerClass = getUnityPlayerClass();
  AndroidJavaObjectPtr activity = getCurrentActivity(unityPlayerClass);
  AndroidJavaObjectPtr context = getApplicationContext(activity);
  AndroidJavaObjectPtr filesDir = getExternalFilesDirFromContext(context);

  return il2cppi_to_string(getPathFromFilesDir(filesDir));
}

const char *getExternalFilesDir() {
  if (!externalStoragePath.empty()) {
    return externalStoragePath.c_str();
  }

  externalStoragePath = getExternalFilesPathFromJNI();
  return externalStoragePath.c_str();
}

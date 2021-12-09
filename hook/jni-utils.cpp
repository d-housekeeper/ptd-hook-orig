#include "jni-utils.h"
#include "helpers.h"
#include "il2cpp-appdata.h"

using namespace app;

AndroidJavaObjectPtr getJavaClass(const char *className) {
  AndroidJavaClass *clazz = (AndroidJavaClass *)il2cpp_object_new((Il2CppClass *)*AndroidJavaClass__TypeInfo);
  AndroidJavaClass__ctor(clazz, (String *)il2cpp_string_new(className), nullptr);
  return AndroidJavaObjectPtr((AndroidJavaObject *)clazz);
}

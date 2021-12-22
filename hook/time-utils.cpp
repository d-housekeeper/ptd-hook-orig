#include "android-utils.h"
#include "jni-utils.h"
#include <android/log.h>
#include <chrono>

using namespace app;
namespace chrono = std::chrono;
static bool timeZoneOffsetInMillisCached = false;
static int timeZoneOffsetInMillis = 0;

static AndroidJavaObjectPtr getDefaultTimeZone(const AndroidJavaObjectPtr &timeZoneClass) {
  Object__Array *args = (Object__Array *)il2cpp_array_new((Il2CppClass *)*Object__Array__TypeInfo, 0);
  return AndroidJavaObjectPtr(AndroidJavaObject_CallStatic_2(timeZoneClass.get(),
                                                             (String *)il2cpp_string_new("getDefault"), args,
                                                             *AndroidJavaObject_CallStatic_2__MethodInfo));
}

static int getTimeZoneOffset(const AndroidJavaObjectPtr &timeZone, int64_t currentTime) {
  Object__Array *args = (Object__Array *)il2cpp_array_new((Il2CppClass *)*Object__Array__TypeInfo, 1);
  args->vector[0] = (Object *)il2cpp_value_box((Il2CppClass *)*Int64__TypeInfo, &currentTime);
  return AndroidJavaObject_Call_5(timeZone.get(), (String *)il2cpp_string_new("getOffset"), args,
                                  *AndroidJavaObject_Call_5__MethodInfo);
}

int getTimeZoneOffsetInMillis() {
  if (timeZoneOffsetInMillisCached) {
    return timeZoneOffsetInMillis;
  }

  AndroidJavaObjectPtr timeZoneClass = getJavaClass("java.util.TimeZone");
  AndroidJavaObjectPtr timeZone = getDefaultTimeZone(timeZoneClass);

  chrono::system_clock::time_point currentTime = chrono::system_clock::now();
  chrono::duration timeSinceEpoch = currentTime.time_since_epoch();
  int64_t millis = chrono::duration_cast<chrono::milliseconds>(timeSinceEpoch).count();
  timeZoneOffsetInMillis = getTimeZoneOffset(timeZone, millis);
  timeZoneOffsetInMillisCached = true;

  return timeZoneOffsetInMillis;
}

std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> getCurrentTime() {
  chrono::milliseconds timeZoneOffset = chrono::milliseconds(getTimeZoneOffsetInMillis());
  return time_point_cast<chrono::seconds>(chrono::system_clock::now() + timeZoneOffset);
}

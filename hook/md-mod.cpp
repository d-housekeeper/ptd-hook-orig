#include "android-utils.h"
#include "frida-gum.h"
#include "helpers.h"
#include "il2cpp-appdata.h"
#include <android/log.h>

using namespace app;

static MD_TowerSeasonList *replacement_MDLoader3_c__LoadMain_b__21_47(MDLoader3_c *__this, Byte__Array *sbfByteData,
                                                                      MethodInfo *method) {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Modifying TowerSeason MD to make one of them last forever");
  MD_TowerSeasonList *list = MDLoader3_c__LoadMain_b__21_47(__this, sbfByteData, method);

  for (int i = 0; i < list->_List->_size; i++) {
    MD_TowerSeason *season = list->_List->_items->vector[i];
    String *seasonID = MD_TowerSeason_get_ID(season, nullptr);
    std::string stdSeasonID = il2cppi_to_string(seasonID);
    std::string releaseDate;
    std::string closeDate;

    if (stdSeasonID == "S202109xx") {
      releaseDate = "06/22/2017 00:00:00";
      closeDate = "01/01/3000 00:00:00";
    } else {
      releaseDate = "01/01/3000 00:00:00";
      closeDate = "01/01/3000 00:00:00";
    }

    season->_ReleaseDate = DateTime_Parse((String *)il2cpp_string_new(releaseDate.c_str()), nullptr);
    season->_CloseDate = DateTime_Parse((String *)il2cpp_string_new(closeDate.c_str()), nullptr);
  }

  return list;
}

static MD_EventControlList *replacement_MDLoader3_c__LoadMain_b__21_186(MDLoader3_c *__this, Byte__Array *sbfByteData,
                                                                        MethodInfo *method) {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Modifying EventControl MD to prevent movies from playing");
  MD_EventControlList *list = MDLoader3_c__LoadMain_b__21_186(__this, sbfByteData, method);
  for (int i = 0; i < list->_List->_size; i++) {
    MD_EventControl *eventControl = list->_List->_items->vector[i];
    std::string id = il2cppi_to_string(MD_EventControl_get_ID(eventControl, nullptr));
    std::string eventType = il2cppi_to_string(MD_EventControl_get_EventType(eventControl, nullptr));
    std::string parameter3 = il2cppi_to_string(MD_EventControl_get_Parameter3(eventControl, nullptr));

    if (eventType == "Movie" && (parameter3 == "Home" || parameter3 == "Tower")) {
      DateTime dummyDate = DateTime_Parse((String *)il2cpp_string_new("01/01/3000 00:00:00"), nullptr);
      eventControl->_ReleaseDate = dummyDate;
      eventControl->_CloseDate = dummyDate;
      eventControl->_EventCloseDate = dummyDate;
    }
  }

  return list;
}

void initMDMod() {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Initializing MD mod");
  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(MDLoader3_c__LoadMain_b__21_47),
                          (void *)replacement_MDLoader3_c__LoadMain_b__21_47, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(MDLoader3_c__LoadMain_b__21_186),
                          (void *)replacement_MDLoader3_c__LoadMain_b__21_186, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

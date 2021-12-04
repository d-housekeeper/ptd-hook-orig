#include "helpers.h"
#include "il2cpp-appdata.h"
#include "json.hpp"
#include "utils.h"
#include <android/log.h>

using json = nlohmann::json;
using namespace app;

using EnemyGroupList_GetData_Func = MD_EnemyGroup *(MD_EnemyGroupList *__this, String *id, MethodInfo *method);
using IMD_Quest_Get_EnemyGroupID_Func = String *(IMD_Quest *__this, MethodInfo *method);

static List_1_MD_EnemyGroupHelper_WaveInfo_ *getWaveInfoListFromMDQuest(IMD_Quest *quest);
static std::vector<json> getPlayerQuestEnemies(List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList);

std::string getStartQuestResponse(const std::string &requestPM) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "request: %s", requestPM.c_str());
  json requestJSON = json::parse(requestPM, nullptr, true);
  if (requestJSON.is_discarded()) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to parse StartQuest request");
    return "";
  }
  json::const_iterator masterNameIt = requestJSON.find("mn");
  json::const_iterator questIDIt = requestJSON.find("qId");
  if (masterNameIt == requestJSON.end() || questIDIt == requestJSON.end() || !(*masterNameIt).is_string() ||
      !(*questIDIt).is_string()) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag,
                        "StartQuest request missing required attributes, or its values are invalid (mn, qId)");
    return "";
  }

  std::string inMasterName = *masterNameIt;
  std::string inQuestID = *questIDIt;
  String *masterName = (String *)il2cpp_string_new(inMasterName.c_str());
  String *questID = (String *)il2cpp_string_new(inQuestID.c_str());
  IMD_Quest *quest = (IMD_Quest *)MDManager_GetScenarioQuestFromMasterName(masterName, questID, nullptr);

  if (quest == nullptr) {
    quest = (IMD_Quest *)MDManager_GetGirlLabyrinthQuest(masterName, questID, nullptr);
  }

  if (quest == nullptr) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to get quest by ID. masterName: %s, questID: %s",
                        inMasterName.c_str(), inQuestID.c_str());
    return "";
  }

  List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList = getWaveInfoListFromMDQuest(quest);

  if (waveInfoList == nullptr) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag, "Failed to get WaveInfoList");

    return "";
  }

  std::vector<json> playerQuestEnemies = getPlayerQuestEnemies(waveInfoList);

  if (playerQuestEnemies.empty()) {
    __android_log_print(ANDROID_LOG_WARN, androidLogTag,
                        "StartQuest request missing required attributes or invalid (mn, qId)");

    return "";
  }

  json responseJson = {{"np", 0},
                       {"tm", "2021-10-29 10:00:00"},
                       {"rt", 0},
                       {"rp", {{"pqe", playerQuestEnemies}, {"pqTmp", "12345678"}}}};

  return responseJson.dump();
}

static std::vector<json> getPlayerQuestEnemies(List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList) {
  std::vector<json> enemies;
  for (int k = 0; k < waveInfoList->_size; ++k) {
    MD_EnemyGroupHelper_WaveInfo waveInfo = waveInfoList->_items->vector[k];
    int j = 0;
    if (waveInfo.LotEnemyList->_size < 1) {
      return std::vector<json>();
    }
    MD_EnemyGroupHelper_WaveInfo_LotEnemy lotEnemy = waveInfo.LotEnemyList->_items->vector[j];
    std::vector<json> enemiesForWave;
    for (int i = 0; i < lotEnemy.EnemyIdList->_size; ++i) {
      String *enemyID = lotEnemy.EnemyIdList->_items->vector[i];
      std::string stdEnemyID = il2cppi_to_string(enemyID);
      enemiesForWave.push_back({{stdEnemyID, json::array()}});
    }
    enemies.push_back(json(enemiesForWave));
  }

  return enemies;
}

static List_1_MD_EnemyGroupHelper_WaveInfo_ *getWaveInfoListFromMDQuest(IMD_Quest *quest) {
  IMD_Quest__VTable *vtable =
      (IMD_Quest__VTable *)il2cppi_get_interface_vtable((Object *)quest, (Il2CppClass *)*IMD_Quest__TypeInfo);
  IMD_Quest_Get_EnemyGroupID_Func *getEnemyGroupIDFunc =
      (IMD_Quest_Get_EnemyGroupID_Func *)(vtable->get_EnemyGroupID.methodPtr);
  String *enemyGroupID = getEnemyGroupIDFunc(quest, (MethodInfo *)vtable->get_EnemyGroupID.method);
  std::string stdEnemyGroupID = il2cppi_to_string(enemyGroupID);

  MD_EnemyGroupList *enemyGroupList = (MD_EnemyGroupList *)MDManager_GetData(MDType__Enum::EnemyGroup, nullptr);
  EnemyGroupList_GetData_Func *enemyGroupListGetDataFunc =
      (EnemyGroupList_GetData_Func *)enemyGroupList->klass->vtable.GetData.methodPtr;
  MD_EnemyGroup *enemyGroup = enemyGroupListGetDataFunc(enemyGroupList, enemyGroupID,
                                                        (MethodInfo *)enemyGroupList->klass->vtable.GetData.method);

  if (enemyGroup == nullptr) {
    __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Failed to get EnemyGroup by ID: %s",
                        stdEnemyGroupID.c_str());
    return nullptr;
  }

  MD_EnemyGroupHelper *enemyGroupHelper =
      (MD_EnemyGroupHelper *)il2cpp_object_new((Il2CppClass *)*MD_EnemyGroupList__TypeInfo);
  MD_EnemyGroupHelper__ctor(enemyGroupHelper, enemyGroup, nullptr);

  return (List_1_MD_EnemyGroupHelper_WaveInfo_ *)MD_EnemyGroupHelper_get_WaveInfoList(enemyGroupHelper, nullptr);
}

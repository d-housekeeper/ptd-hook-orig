#include "start-quest-response.h"
#include "android-utils.h"
#include "helpers.h"
#include "il2cpp-appdata.h"
#include "json.hpp"
#include "login-response.h"
#include "response-loader.h"
#include "response-utils.h"
#include "string-utils.h"
#include <android/log.h>
#include <functional>
#include <vector>

using json = nlohmann::json;
using namespace app;

using EnemyGroupList_GetData_Func = MD_EnemyGroup *(MD_EnemyGroupList *__this, String *id, MethodInfo *method);
using IMD_Quest_Get_EnemyGroupID_Func = String *(IMD_Quest *__this, MethodInfo *method);

static std::vector<json> getPlayerQuestEnemies(List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList);
static List_1_MD_EnemyGroupHelper_WaveInfo_ *getWaveInfoListFromMDQuest(IMD_Quest *quest);
static IMD_Quest *tryGetQuest(String *masterName, String *questID);

std::string getStartQuestResponse(ResponseLoaderContext *context, const nlohmann::json &requestJSON) {
  std::string inMasterName;
  std::string inQuestID;
  int inTeamNumber = 0;

  try {
    inMasterName = requestJSON["mn"];
    inQuestID = requestJSON["qId"];
    inTeamNumber = requestJSON["tn"];
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Invalid StartQuest request: %s", e.what());
    return "";
  }

  String *masterName = (String *)il2cpp_string_new(inMasterName.c_str());
  String *questID = (String *)il2cpp_string_new(inQuestID.c_str());
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Generating StartQuestResponse. masterName: %s questID: %s",
                      inMasterName.c_str(), inQuestID.c_str());
  IMD_Quest *quest = tryGetQuest(masterName, questID);

  if (quest == nullptr) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to get quest by ID. masterName: %s questID: %s",
                        inMasterName.c_str(), inQuestID.c_str());
    return "";
  }

  List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList = getWaveInfoListFromMDQuest(quest);

  if (waveInfoList == nullptr) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to get WaveInfoList");

    return "";
  }

  std::vector<json> playerQuestEnemies = getPlayerQuestEnemies(waveInfoList);

  if (playerQuestEnemies.empty()) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag,
                        "StartQuest request missing required attributes or invalid (mn, qId)");

    return "";
  }

  const char *playQuestTempID = "12345678";
  try {
    // clang-format off
    context->loginResponse["td"]["User"].merge_patch({
      {"pQId", inQuestID},
      {"pQNm", inMasterName},
      {"pQTNm", inTeamNumber},
      {"pqe", json(playerQuestEnemies).dump()},
      {"pqTmp", playQuestTempID},
    });
    // clang-format on
  } catch (json::exception &e) {
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to patch Login response with StartQuest: %s",
                        e.what());
    return "";
  }

  if (!saveLoginResponse(context)) {
    return "";
  }

  json responseJson = getBaseResponse();
  // clang-format off
  responseJson.merge_patch({
    {"rp", {
      {"pqe", playerQuestEnemies},
      {"pqTmp", playQuestTempID}
    }}
  });
  // clang-format on
  return responseJson.dump();
}

static std::vector<json> getPlayerQuestEnemies(List_1_MD_EnemyGroupHelper_WaveInfo_ *waveInfoList) {
  std::vector<json> enemies;

  for (int j = 0; j < waveInfoList->_size; ++j) {
    MD_EnemyGroupHelper_WaveInfo waveInfo = waveInfoList->_items->vector[j];
    if (waveInfo.LotEnemyList->_size < 1) {
      return std::vector<json>();
    }
    int lotEnemyIndex = getRandomNumber(waveInfo.LotEnemyList->_size - 1);
    __android_log_print(ANDROID_LOG_INFO, androidLogTag, "lotEnemy(%d): %d/%d", j, lotEnemyIndex,
                        waveInfo.LotEnemyList->_size);
    MD_EnemyGroupHelper_WaveInfo_LotEnemy lotEnemy = waveInfo.LotEnemyList->_items->vector[lotEnemyIndex];
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
    __android_log_print(ANDROID_LOG_ERROR, androidLogTag, "Failed to get EnemyGroup by ID: %s",
                        stdEnemyGroupID.c_str());
    return nullptr;
  }

  MD_EnemyGroupHelper *enemyGroupHelper =
      (MD_EnemyGroupHelper *)il2cpp_object_new((Il2CppClass *)*MD_EnemyGroupHelper__TypeInfo);
  MD_EnemyGroupHelper__ctor(enemyGroupHelper, enemyGroup, nullptr);

  return (List_1_MD_EnemyGroupHelper_WaveInfo_ *)MD_EnemyGroupHelper_get_WaveInfoList(enemyGroupHelper, nullptr);
}

static IMD_Quest *tryGetQuest(String *masterName, String *questID) {
  // clang-format off
  std::function<IMD_Quest*()> questLoaders[] = {
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetNormalEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetToubatsuEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetTouhaEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetRankingEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetPointEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetMultiEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetDamageEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetVoteEventQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      return (IMD_Quest *)MDManager_GetGirlLabyrinthQuest(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest * {
      return (IMD_Quest *)MDManager_GetScenarioQuestFromMasterName(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest * {
      return (IMD_Quest *)MDManager_GetRaidEventQuest_1(masterName, questID, nullptr);
    },
    [=]() -> IMD_Quest* {
      MD_TowerQuestList *towerQuestList = (MD_TowerQuestList *)MDManager_GetData(MDType__Enum::TowerQuest, nullptr);
      return (IMD_Quest *)MD_TowerQuestList_GetData(towerQuestList, questID, nullptr);
    },
  };
  // clang-format on
  size_t questLoaderCount = sizeof(questLoaders) / sizeof(questLoaders[0]);

  for (int i = 0; i < questLoaderCount; ++i) {
    IMD_Quest *quest = questLoaders[i]();
    if (quest != nullptr) {
      return quest;
    }
  }

  return nullptr;
}

// EnvironmentData
DO_APP_FUNC(0x0182002C, String *, EnvironmentData_get_UUID, (EnvironmentData * __this, MethodInfo * method));
DO_APP_FUNC(0x0181FD00, bool, EnvironmentData_get_CurrentIsAesEncrypt, (EnvironmentData * __this, MethodInfo * method));

// UnityWebRequest
DO_APP_FUNC(0x0265935C, bool, UnityWebRequest_get_isDone, (UnityWebRequest * __this, MethodInfo * method));
DO_APP_FUNC(0x02658528, UnityWebRequestAsyncOperation *, UnityWebRequest_SendWebRequest, (UnityWebRequest * __this, MethodInfo * method));
DO_APP_FUNC(0x026589A4, String *, UnityWebRequest_get_error, (UnityWebRequest * __this, MethodInfo * method));

// DownloadHandler
DO_APP_FUNC(0x02657204, String *, DownloadHandler_GetText, (DownloadHandler * __this, MethodInfo * method));

// RequestBase
DO_APP_FUNC(0x01825634, RequestBase_ResponseParameter *, RequestBase_DecodeResultData, (RequestBase * __this, String * receiveData, MethodInfo * method));

// EnvironmentData
DO_APP_FUNC(0x0181FC34, void, EnvironmentData_set_IsGZipCompress, (EnvironmentData * __this, bool value, MethodInfo * method));

// LocalData
DO_APP_FUNC(0x0098CD24, bool, LocalData_get_DisuseGooglePlayService, (LocalData * __this, MethodInfo * method));
DO_APP_FUNC(0x0098CBF8, List_1_System_Int32_ *, LocalData_get_TutorialProgressData, (LocalData * __this, MethodInfo * method));
DO_APP_FUNC(0x0098CC08, int32_t, LocalData_get_PartialTutorialData, (LocalData * __this, MethodInfo * method));

// Dictionary_2_System_String_System_Object_
DO_APP_FUNC(0x0239AFE8, bool, Dictionary_2_System_String_System_Object__TryGetValue, (Dictionary_2_System_String_System_Object_ * __this, String * key, Object * * value, MethodInfo * method));

// Dictionary_2_System_String_System_Int32_
DO_APP_FUNC(0x0232625C, void, Dictionary_2_System_String_System_Int32__Clear, (Dictionary_2_System_String_System_Int32_ * __this, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F338FC, Dictionary_2_System_String_System_Int32__Clear__MethodInfo);
DO_APP_FUNC(0x02325EBC, void, Dictionary_2_System_String_System_Int32__set_Item, (Dictionary_2_System_String_System_Int32_ * __this, String * key, int32_t value, MethodInfo * method));

// MDManager
DO_APP_FUNC(0x0074BA9C, Object *, MDManager_GetData, (MDType__Enum key, MethodInfo * method));
DO_APP_FUNC(0x0075016C, MD_NormalEventQuest *, MDManager_GetNormalEventQuest, (String * noramlQuestMaster, String * normalQuestID, MethodInfo * method));
DO_APP_FUNC(0x0075105C, MD_ToubatsuEventQuest *, MDManager_GetToubatsuEventQuest, (String * toubatsuQuestMaster, String * toubatsuQuestID, MethodInfo * method));
DO_APP_FUNC(0x00751478, MD_TouhaEventQuest *, MDManager_GetTouhaEventQuest, (String * touhaQuestMaster, String * touhaQuestID, MethodInfo * method));
DO_APP_FUNC(0x00751894, MD_RankingEventQuest *, MDManager_GetRankingEventQuest, (String * questMaster, String * questID, MethodInfo * method));
DO_APP_FUNC(0x0075234C, MD_PointEventQuest *, MDManager_GetPointEventQuest, (String * questMaster, String * questID, MethodInfo * method));
DO_APP_FUNC(0x00752768, MD_MultiEventQuest *, MDManager_GetMultiEventQuest, (String * questMaster, String * questID, MethodInfo * method));
DO_APP_FUNC(0x00752B84, MD_DamageEventQuest *, MDManager_GetDamageEventQuest, (String * questMaster, String * questID, MethodInfo * method));
DO_APP_FUNC(0x00753450, MD_VoteQuest *, MDManager_GetVoteEventQuest, (String * questMaster, String * questID, MethodInfo * method));
DO_APP_FUNC(0x00755C90, MD_GirlLabyrinthQuest *, MDManager_GetGirlLabyrinthQuest, (String * questMasterName, String * questID, MethodInfo * method));
DO_APP_FUNC(0x00758998, MD_ScenarioQuest *, MDManager_GetScenarioQuestFromMasterName, (String * masterName, String * id, MethodInfo * method));
DO_APP_FUNC(0x007670AC, MD_RaidEventQuest *, MDManager_GetRaidEventQuest_1, (String * mdname, String * questid, MethodInfo * method));

// MD_EnemyGroupHelper
DO_APP_FUNC(0x01B0A0FC, void, MD_EnemyGroupHelper__ctor, (MD_EnemyGroupHelper * __this, MD_EnemyGroup * mdData, MethodInfo * method));
DO_APP_FUNC(0x01B0A0F4, IList_1_MD_EnemyGroupHelper_WaveInfo_ *, MD_EnemyGroupHelper_get_WaveInfoList, (MD_EnemyGroupHelper * __this, MethodInfo * method));

// List_1_MD_EnemyGroupHelper_WaveInfo
DO_APP_FUNC(0x02496748, MD_EnemyGroupHelper_WaveInfo, List_1_MD_EnemyGroupHelper_WaveInfo__get_Item, (List_1_MD_EnemyGroupHelper_WaveInfo_ * __this, int32_t index, MethodInfo * method));
DO_APP_FUNC(0x02496694, int32_t, List_1_MD_EnemyGroupHelper_WaveInfo__get_Count, (List_1_MD_EnemyGroupHelper_WaveInfo_ * __this, MethodInfo * method));

// List_1_MD_EnemyGroupHelper_WaveInfo_LotEnemy
DO_APP_FUNC(0x02493140, int32_t, List_1_MD_EnemyGroupHelper_WaveInfo_LotEnemy__get_Count, (List_1_MD_EnemyGroupHelper_WaveInfo_LotEnemy_ * __this, MethodInfo * method));
DO_APP_FUNC(0x024931F4, MD_EnemyGroupHelper_WaveInfo_LotEnemy, List_1_MD_EnemyGroupHelper_WaveInfo_LotEnemy__get_Item, (List_1_MD_EnemyGroupHelper_WaveInfo_LotEnemy_ * __this, int32_t index, MethodInfo * method));

// List_1_System_String
DO_APP_FUNC(0x02510F18, int32_t, List_1_System_String__get_Count, (List_1_System_String_ * __this, MethodInfo * method));
DO_APP_FUNC(0x02510FCC, String *, List_1_System_String__get_Item, (List_1_System_String_ * __this, int32_t index, MethodInfo * method));

// List_1_System_Int32_
DO_APP_FUNC(0x025079C8, void, List_1_System_Int32__Clear, (List_1_System_Int32_ * __this, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F351DC, List_1_System_Int32__Clear__MethodInfo);
DO_APP_FUNC(0x0250769C, void, List_1_System_Int32__Add, (List_1_System_Int32_ * __this, int32_t item, MethodInfo * method));

// MD_TowerQuestList
DO_APP_FUNC(0x01E769A4, MD_TowerQuest *, MD_TowerQuestList_GetData, (MD_TowerQuestList * __this, String * id, MethodInfo * method));

// AndroidJavaClass
DO_APP_FUNC(0x01E9F520, void, AndroidJavaClass__ctor, (AndroidJavaClass * __this, String * className, MethodInfo * method));

// AndroidJavaObject
DO_APP_FUNC(0x01D3B0D8, AndroidJavaObject *, AndroidJavaObject_Call_2, (AndroidJavaObject * __this, String * methodName, Object__Array * args, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F20B88, AndroidJavaObject_Call_2__MethodInfo);
DO_APP_FUNC(0x01D3B0D8, String *, AndroidJavaObject_Call_3, (AndroidJavaObject * __this, String * methodName, Object__Array * args, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F20B84, AndroidJavaObject_Call_3__MethodInfo);
DO_APP_FUNC(0x01EA0034, void, AndroidJavaObject__Dispose, (AndroidJavaObject * __this, MethodInfo * method));
DO_APP_FUNC(0x01D5A328, AndroidJavaObject *, AndroidJavaObject_GetStatic_3, (AndroidJavaObject * __this, String * fieldName, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F1E44C, AndroidJavaObject_GetStatic_3__MethodInfo);
DO_APP_FUNC(0x01D3B240, AndroidJavaObject *, AndroidJavaObject_CallStatic_2, (AndroidJavaObject * __this, String * methodName, Object__Array * args, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F20B90, AndroidJavaObject_CallStatic_2__MethodInfo);
DO_APP_FUNC(0x01D3B048, int32_t, AndroidJavaObject_Call_5, (AndroidJavaObject * __this, String * methodName, Object__Array * args, MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F20B78, AndroidJavaObject_Call_5__MethodInfo);

// ReLoginUtility
DO_APP_FUNC(0x00EA6838, bool, ReLoginUtility_CheckMustReLogin, (MethodInfo * method));

// MDLoader3
DO_APP_FUNC(0x00741950, MD_TowerSeasonList *, MDLoader3_c__LoadMain_b__21_47, (MDLoader3_c * __this, Byte__Array * sbfByteData, MethodInfo * method));
DO_APP_FUNC(0x007485D4, MD_EventControlList *, MDLoader3_c__LoadMain_b__21_186, (MDLoader3_c * __this, Byte__Array * sbfByteData, MethodInfo * method));

// MD_TowerSeason
DO_APP_FUNC(0x019F42D4, String *, MD_TowerSeason_get_ID, (MD_TowerSeason * __this, MethodInfo * method));

// DateTime
DO_APP_FUNC(0x01B9B0EC, DateTime, DateTime_Parse, (String * s, MethodInfo * method));

// MD_EventControl
DO_APP_FUNC(0x01B0F518, String *, MD_EventControl_get_ID, (MD_EventControl * __this, MethodInfo * method));
DO_APP_FUNC(0x01B0F634, String *, MD_EventControl_get_EventType, (MD_EventControl * __this, MethodInfo * method));
DO_APP_FUNC(0x01B104C0, String *, MD_EventControl_get_Parameter3, (MD_EventControl * __this, MethodInfo * method));

// SceneHomeTop
DO_APP_FUNC(0x00A9EE0C, void, SceneHomeTop_MoveInAllUI, (SceneHomeTop * __this, MethodInfo * method));
DO_APP_FUNC(0x00A9EEFC, void, SceneHomeTop_MoveOutAllUI, (SceneHomeTop * __this, MethodInfo * method));

// CommuManager
DO_APP_FUNC(0x00FE0F60, void, CommuManager_SetDisplayVertical, (CommuManager * __this, bool set, MethodInfo * method));

// SystemBase_1_CommuManager_
DO_APP_FUNC(0x020CD108, CommuManager *, SystemBase_1_CommuManager__get_Instance, (MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F3AB6C, SystemBase_1_CommuManager__get_Instance__MethodInfo);

// ShootingUIShooting
DO_APP_FUNC(0x00C6AF88, void, ShootingUIShooting_UIMoveInAll, (ShootingUIShooting * __this, MethodInfo * method));
DO_APP_FUNC(0x00C6AE30, void, ShootingUIShooting_UIMoveOutAll, (ShootingUIShooting * __this, MethodInfo * method));

// OutGameCameraManager
DO_APP_FUNC(0x01146DF4, void, OutGameCameraManager_SetTargetPosition, (OutGameCameraManager * __this, Vector3 position, float fieldOfView, bool isMove, MethodInfo * method));
DO_APP_FUNC(0x01142E58, void, OutGameCameraManager_set_ImmediatelyMove, (OutGameCameraManager * __this, bool value, MethodInfo * method));

// SystemBase_1_OutGameCameraManager_
DO_APP_FUNC(0x020CD108, OutGameCameraManager *, SystemBase_1_OutGameCameraManager__get_Instance, (MethodInfo * method));
DO_APP_FUNC_METHODINFO(0x02F3ABBC, SystemBase_1_OutGameCameraManager__get_Instance__MethodInfo);

// Component
DO_APP_FUNC(0x01EAD08C, Transform *, Component_get_transform, (Component * __this, MethodInfo * method));
DO_APP_FUNC(0x01EAD11C, GameObject *, Component_get_gameObject, (Component * __this, MethodInfo * method));

// Camera
DO_APP_FUNC(0x01EA8CF8, float, Camera_get_fieldOfView, (Camera * __this, MethodInfo * method));

// Transform
DO_APP_FUNC(0x0237EFEC, Vector3, Transform_get_position, (Transform * __this, MethodInfo * method));
DO_APP_FUNC(0x023812AC, int32_t, Transform_get_childCount, (Transform * __this, MethodInfo * method));
DO_APP_FUNC(0x02381904, Transform *, Transform_GetChild, (Transform * __this, int32_t index, MethodInfo * method));
DO_APP_FUNC(0x02381628, Transform *, Transform_Find, (Transform * __this, String * n, MethodInfo * method));
DO_APP_FUNC(0x02380590, void, Transform_Translate_2, (Transform * __this, float x, float y, float z, MethodInfo * method));

// GameObject
DO_APP_FUNC(0x01E79934, void, GameObject_SetActive, (GameObject * __this, bool value, MethodInfo * method));
DO_APP_FUNC(0x01E79778, Transform *, GameObject_get_transform, (GameObject * __this, MethodInfo * method));

// MoveUI2
DO_APP_FUNC(0x00DC4290, void, MoveUI2_MoveIn, (MoveUI2 * __this, MethodInfo * method));
DO_APP_FUNC(0x00DC42C4, void, MoveUI2_MoveOut, (MoveUI2 * __this, MethodInfo * method));

// SceneMyroomTop_CoroutineCharaChange_d_46
DO_APP_FUNC(0x00E8C5C8, bool, SceneMyroomTop_CoroutineCharaChange_d_46_MoveNext, (SceneMyroomTop_CoroutineCharaChange_d_46 * __this, MethodInfo * method));

// SceneTitleRoot
DO_APP_FUNC(0x00B22DD4, void, SceneTitleRoot_Initialize, (SceneTitleRoot * __this, MethodInfo * method));

// MD_Character
DO_APP_FUNC(0x01D9A40C, int32_t, MD_Character_get_Playable, (MD_Character * __this, MethodInfo * method));

// SceneMyroomTop
DO_APP_FUNC(0x00E89438, void, SceneMyroomTop_ChangeTopUIActive, (SceneMyroomTop * __this, ePlayableType__Enum playableType, MethodInfo * method));

// SceneHomeTop_InitScene_d_29
DO_APP_FUNC(0x00AA6398, bool, SceneHomeTop_InitScene_d_29_MoveNext, (SceneHomeTop_InitScene_d_29 * __this, MethodInfo * method));

// SceneMyroomTop_InitScene_d_23
DO_APP_FUNC(0x00E8D850, bool, SceneMyroomTop_InitScene_d_23_MoveNext, (SceneMyroomTop_InitScene_d_23 * __this, MethodInfo * method));

// ScenePrefabEventTopVote
DO_APP_FUNC(0x011AA514, void, ScenePrefabEventTopVote_WindowUI_VotePointUI_SetText, (ScenePrefabEventTopVote_WindowUI_VotePointUI * __this, ScenePrefabEventTopVote_WindowUI_Param * param, MethodInfo * method));

// RankingListAPIManager
DO_APP_FUNC(0x00E96040, void, RankingListAPIManager_OnDownloadRankingCompleted, (RankingListAPIManager * __this, String * fileName, MethodInfo * method));

// RankingListAPIManager
DO_APP_FUNC(0x00E958F4, String *, RankingListAPIManager_get_RankingDirectory, (MethodInfo * method));

// SceneEventTopBase_InitTradeList_d_67
DO_APP_FUNC(0x009AC398, bool, SceneEventTopBase_InitTradeList_d_67_MoveNext, (SceneEventTopBase_InitTradeList_d_67 * __this, MethodInfo * method));

// AllNotificationManager
DO_APP_FUNC(0x010CF98C, void, AllNotificationManager_Initialize, (MethodInfo * method));

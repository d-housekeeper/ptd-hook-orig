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
DO_APP_FUNC(0x0098CD14, Dictionary_2_System_String_System_Int32_ *, LocalData_get_DownloadedMovieVer, (LocalData * __this, MethodInfo * method));
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
DO_APP_FUNC(0x00758998, MD_ScenarioQuest *, MDManager_GetScenarioQuestFromMasterName, (String * masterName, String * id, MethodInfo * method));
DO_APP_FUNC(0x00755C90, MD_GirlLabyrinthQuest *, MDManager_GetGirlLabyrinthQuest, (String * questMasterName, String * questID, MethodInfo * method));

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

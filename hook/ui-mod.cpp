#include "ui-mod.h"
#include "android-utils.h"
#include "config.h"
#include "frida-gum.h"
#include "helpers.h"
#include "il2cpp-appdata.h"
#include <android/log.h>

using namespace app;
using json = nlohmann::json;

static bool hideHomeSceneUIElementsEnabled =
    true; // Indicates whether hideHomeSceneUIElements is enabled when home scene is initialized

static void forcePortraitMode() {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Forcing portrait mode");
  CommuManager *commuManager =
      SystemBase_1_CommuManager__get_Instance(*SystemBase_1_CommuManager__get_Instance__MethodInfo);
  CommuManager_eScenePlace__Enum oldScenePlace = commuManager->_ScenePlace;
  commuManager->_ScenePlace = (CommuManager_eScenePlace__Enum)0x18;
  CommuManager_SetDisplayVertical(commuManager, true, nullptr);
  commuManager->_ScenePlace = oldScenePlace;
}

static void adjustPortraitModeCameraPos(const json &config) {
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Adjusting camera pos for forced portrait mode");
  float baseCameraPosY = 133.0f;
  int cameraPosOffsetY = getIntConfigValue(config, "cameraPosOffsetY", 0);

  OutGameCameraManager *cameraManager =
      SystemBase_1_OutGameCameraManager__get_Instance(*SystemBase_1_OutGameCameraManager__get_Instance__MethodInfo);
  Camera__Array *cameras = cameraManager->_CharacterCamera;
  Camera *camera = (Camera *)cameras->vector[0];
  Transform *cameraTransform = Component_get_transform((Component *)camera, nullptr);
  Vector3 cameraPos = Transform_get_position(cameraTransform, nullptr);
  float fieldOfView = Camera_get_fieldOfView(camera, nullptr);
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "old cameraPos Y: %f", cameraPos.y);
  cameraPos.y = baseCameraPosY - (float)cameraPosOffsetY;
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "new cameraPos Y: %f", cameraPos.y);

  OutGameCameraManager_SetTargetPosition(cameraManager, cameraPos, fieldOfView, true, nullptr);
  OutGameCameraManager_set_ImmediatelyMove(cameraManager, true, nullptr);
}

static void hideHomeSceneUIElementsIfNeeded(const json &config, SceneHomeTop *scene) {
  hideHomeSceneUIElementsEnabled = getBooleanConfigValue(config, "hideHomeSceneUIElements");
  if (!hideHomeSceneUIElementsEnabled) {
    return;
  }
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Hiding home scene UI elements");

  GameObject_SetActive(scene->_GlobalMenu->_GlobalHeader_k__BackingField->_StatusRoot, false, nullptr);

  GameObject_SetActive(scene->_GlobalMenu->_GlobalAppend_k__BackingField->_Root_k__BackingField, false, nullptr);
  GameObject_SetActive(scene->_HomeTop->_HomeTopContainer->_NewsBanner->_ObjectRoot, false, nullptr);
  GameObject_SetActive(scene->_HomeTop->_HomeTopContainer->_EventBanner->_ObjectRoot, false, nullptr);

  GameObject *loginBonusButtonObject = Component_get_gameObject(
      (Component *)
          scene->_GlobalMenu->_GlobalHeader_k__BackingField->_LoginBonusButton_k__BackingField->_LoginBonusButton,
      nullptr);
  GameObject_SetActive(loginBonusButtonObject, false, nullptr);

  Transform *homeTopTransform = GameObject_get_transform(scene->_HomeTop->_Root, nullptr);
  Transform_Translate_2(homeTopTransform, 0.0f, 48.0f, 0.0f, nullptr);

  Transform *globalHeaderTransform =
      GameObject_get_transform(scene->_GlobalMenu->_GlobalHeader_k__BackingField->_Root_k__BackingField, nullptr);
  int globalHeaderTransformChildCount = Transform_get_childCount(globalHeaderTransform, nullptr);

  for (int i = 0; i < globalHeaderTransformChildCount; i++) {
    Transform *childTransform = Transform_GetChild(globalHeaderTransform, i, nullptr);
    GameObject *gameObject = Component_get_gameObject((Component *)childTransform, nullptr);
  }

  Transform *topButtonsTransform =
      Transform_Find(homeTopTransform, (String *)il2cpp_string_new("top_buttons"), nullptr);

  int topButtonsTransformChildCount = Transform_get_childCount(topButtonsTransform, nullptr);

  for (int i = 0; i < topButtonsTransformChildCount; i++) {
    Transform *childTransform = Transform_GetChild(topButtonsTransform, i, nullptr);
    GameObject *gameObject = Component_get_gameObject((Component *)childTransform, nullptr);
    GameObject_SetActive(gameObject, false, nullptr);
  }
  GameObject_SetActive(scene->_HomeTop->_HomeTopContainer->_SideButton->_ObjectRoom, true, nullptr);
  GameObject_SetActive(scene->_HomeTop->_HomeTopContainer->_SideButton->_ObjectCharaChange, true, nullptr);
}

static void hideMyRoomSceneUIElementsIfNeeded(const json &config, SceneMyroomTop *scene) {
  bool show = !getBooleanConfigValue(config, "hideMyRoomSceneUIElements");

  if (show) {
    __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Showing my room scene UI elements again");
    int playableType = MD_Character_get_Playable(scene->_MD_Character, nullptr);
    SceneMyroomTop_ChangeTopUIActive(scene, (ePlayableType__Enum)playableType, nullptr);
    return;
  }

  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Hiding my room scene UI elements");

  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__MemoryButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__ProfileButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__SubScenarioButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__FeelButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__GiftItemButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__CostumeButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);

  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__LockedFeelButton_k__BackingField->__Root_k__BackingField, false,
                       nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__LockedGiftItemButton_k__BackingField->__Root_k__BackingField,
                       false, nullptr);
  GameObject_SetActive(scene->_ScenePrefabMyroomTop->__LockedMemoryButton_k__BackingField->__Root_k__BackingField,
                       false, nullptr);
}

static bool replacement_SceneHomeTop_InitScene_d_29_MoveNext(SceneHomeTop_InitScene_d_29 *__this, MethodInfo *method) {
  bool ret = SceneHomeTop_InitScene_d_29_MoveNext(__this, method);
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "SceneHomeTop_InitScene_d_29_MoveNext: %d", ret);
  if (!ret) {
    json config = loadConfigFromFile();
    if (getBooleanConfigValue(config, "portraitHomeScene")) {
      forcePortraitMode();
      adjustPortraitModeCameraPos(config);
    }

    hideHomeSceneUIElementsIfNeeded(config, __this->__4__this);
  }

  return ret;
}

static bool replacement_SceneMyroomTop_InitScene_d_23_MoveNext(SceneMyroomTop_InitScene_d_23 *__this,
                                                               MethodInfo *method) {
  bool ret = SceneMyroomTop_InitScene_d_23_MoveNext(__this, method);
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "SceneMyroomTop_InitScene_d_23: %d", ret);
  if (!ret) {
    json config = loadConfigFromFile();
    if (getBooleanConfigValue(config, "portraitMyRoomScene")) {
      forcePortraitMode();
      adjustPortraitModeCameraPos(config);
    }
    hideMyRoomSceneUIElementsIfNeeded(config, __this->__4__this);
  }

  return ret;
}

static void replacement_ShootingUIShooting_UIMoveInAll(ShootingUIShooting *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "ShootingUIShooting_UIMoveInAll");
  CommuManager *commuManager =
      SystemBase_1_CommuManager__get_Instance(*SystemBase_1_CommuManager__get_Instance__MethodInfo);
  json config = loadConfigFromFile();
  if (getBooleanConfigValue(config, "portraitPhotoModeScene")) {
    CommuManager_SetDisplayVertical(commuManager, true, nullptr);
  }
  return ShootingUIShooting_UIMoveInAll(__this, method);
}

static void replacement_ShootingUIShooting_UIMoveOutAll(ShootingUIShooting *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "ShootingUIShooting_UIMoveOutAll");
  CommuManager *commuManager =
      SystemBase_1_CommuManager__get_Instance(*SystemBase_1_CommuManager__get_Instance__MethodInfo);
  CommuManager_SetDisplayVertical(commuManager, false, nullptr);
  return ShootingUIShooting_UIMoveOutAll(__this, method);
}

static void replacement_SceneHomeTop_MoveInAllUI(SceneHomeTop *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "SceneHomeTop_MoveInAllUI");
  if (!hideHomeSceneUIElementsEnabled) {
    SceneHomeTop_MoveInAllUI(__this, method);
    return;
  }

  MoveUI2_MoveIn((MoveUI2 *)__this->_GlobalMenu->_GlobalFooter_k__BackingField, nullptr);
  GameObject_SetActive(__this->_HomeTop->_HomeTopContainer->_SideButton->_ObjectRoom, true, nullptr);
  GameObject_SetActive(__this->_HomeTop->_HomeTopContainer->_SideButton->_ObjectCharaChange, true, nullptr);
}

static void replacement_SceneHomeTop_MoveOutAllUI(SceneHomeTop *__this, MethodInfo *method) {
  // __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "SceneHomeTop_MoveOutAllUI");
  if (!hideHomeSceneUIElementsEnabled) {
    SceneHomeTop_MoveOutAllUI(__this, method);
    return;
  }

  MoveUI2_MoveOut((MoveUI2 *)__this->_GlobalMenu->_GlobalFooter_k__BackingField, nullptr);
  GameObject_SetActive(__this->_HomeTop->_HomeTopContainer->_SideButton->_ObjectRoom, false, nullptr);
  GameObject_SetActive(__this->_HomeTop->_HomeTopContainer->_SideButton->_ObjectCharaChange, false, nullptr);
}

static bool
replacement_SceneMyroomTop_CoroutineCharaChange_d_46_MoveNext(SceneMyroomTop_CoroutineCharaChange_d_46 *__this,
                                                              MethodInfo *method) {
  bool ret = SceneMyroomTop_CoroutineCharaChange_d_46_MoveNext(__this, method);
  if (!ret) {
    json config = loadConfigFromFile();
    if (getBooleanConfigValue(config, "portraitMyRoomScene")) {
      forcePortraitMode();
      adjustPortraitModeCameraPos(config);
    }
    hideMyRoomSceneUIElementsIfNeeded(config, __this->__4__this);
  }

  return ret;
}

void initScreenOrientationMod(const json &config) {
  if (!getBooleanConfigValue(config, "enableUIMod")) {
    return;
  }
  __android_log_print(ANDROID_LOG_INFO, androidLogTag, "Initializing UI mod");

  GumInterceptor *interceptor = gum_interceptor_obtain();

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneHomeTop_InitScene_d_29_MoveNext),
                          (void *)replacement_SceneHomeTop_InitScene_d_29_MoveNext, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneMyroomTop_InitScene_d_23_MoveNext),
                          (void *)replacement_SceneMyroomTop_InitScene_d_23_MoveNext, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(ShootingUIShooting_UIMoveInAll),
                          (void *)replacement_ShootingUIShooting_UIMoveInAll, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(ShootingUIShooting_UIMoveOutAll),
                          (void *)replacement_ShootingUIShooting_UIMoveOutAll, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneHomeTop_MoveInAllUI),
                          (void *)replacement_SceneHomeTop_MoveInAllUI, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneHomeTop_MoveOutAllUI),
                          (void *)replacement_SceneHomeTop_MoveOutAllUI, nullptr);
  gum_interceptor_replace(interceptor, GSIZE_TO_POINTER(SceneMyroomTop_CoroutineCharaChange_d_46_MoveNext),
                          (void *)replacement_SceneMyroomTop_CoroutineCharaChange_d_46_MoveNext, nullptr);

  gum_interceptor_end_transaction(interceptor);
}

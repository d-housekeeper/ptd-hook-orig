#include "api-mod.h"
#include "frida-gum.h"
#include "helpers.h"
#include "il2cpp-init.h"
#include "local-data-mod.h"
#include "utils.h"

#include <android/log.h>

typedef struct _DLOpenListener DLOpenListener;

typedef struct {
  std::string *loadedLibName;
} DLOpenOperation;

struct _DLOpenListener {
  GObject parent;

  bool allHooksLoaded;
};

static void dlopen_listener_iface_init(gpointer g_iface, gpointer iface_data);

#define DLOPEN_TYPE_LISTENER (dlopen_listener_get_type())
G_DECLARE_FINAL_TYPE(DLOpenListener, dlopen_listener, DLOPEN, LISTENER, GObject)
G_DEFINE_TYPE_EXTENDED(DLOpenListener, dlopen_listener, G_TYPE_OBJECT, 0,
                       G_IMPLEMENT_INTERFACE(GUM_TYPE_INVOCATION_LISTENER, dlopen_listener_iface_init))

static void initAllHooks(DLOpenListener *self);

void initDLOpenHook() {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Initializing dlopen hook");
  GumInterceptor *interceptor = gum_interceptor_obtain();
  GumInvocationListener *listener =
      reinterpret_cast<GumInvocationListener *>(g_object_new(DLOPEN_TYPE_LISTENER, nullptr));

  gum_interceptor_begin_transaction(interceptor);
  gum_interceptor_attach(interceptor, GSIZE_TO_POINTER(gum_module_find_export_by_name(nullptr, "dlopen")), listener,
                         nullptr);
  gum_interceptor_end_transaction(interceptor);
}

static void dlopen_listener_on_enter(GumInvocationListener *listener, GumInvocationContext *ic) {
  DLOpenOperation *op = GUM_IC_GET_INVOCATION_DATA(ic, DLOpenOperation);
  const char *loadedLibName = (const char *)gum_invocation_context_get_nth_argument(ic, 0);
  op->loadedLibName = new std::string(loadedLibName);
}

static void dlopen_listener_on_leave(GumInvocationListener *listener, GumInvocationContext *ic) {
  DLOpenOperation *op = GUM_IC_GET_INVOCATION_DATA(ic, DLOpenOperation);
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "dlopen %s", op->loadedLibName->c_str());
  DLOpenListener *self = DLOPEN_LISTENER(listener);
  if (self->allHooksLoaded) {
    delete op->loadedLibName;
    op->loadedLibName = nullptr;
    return;
  }

  if (stringEndsWith(op->loadedLibName->c_str(), libName)) {
    __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Initializing IL2CPP");
    initAllHooks(self);
    delete op->loadedLibName;
    op->loadedLibName = nullptr;
  }
}

static void dlopen_listener_class_init(DLOpenListenerClass *klass) {
  (void)DLOPEN_IS_LISTENER;
  (void)glib_autoptr_cleanup_DLOpenListener;
}

static void initAllHooks(DLOpenListener *self) {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag, "Initializing all hooks");
  init_il2cpp();
  initApiMod();
  initLocalDataMod();
  self->allHooksLoaded = true;
}

static void dlopen_listener_iface_init(gpointer g_iface, gpointer iface_data) {
  GumInvocationListenerInterface *iface = (GumInvocationListenerInterface *)g_iface;

  iface->on_enter = dlopen_listener_on_enter;
  iface->on_leave = dlopen_listener_on_leave;
}

static void dlopen_listener_init(DLOpenListener *self) {}

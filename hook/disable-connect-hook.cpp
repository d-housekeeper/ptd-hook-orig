#include "frida-gum.h"
#include "utils.h"
#include <android/log.h>
#include <sys/socket.h>

static int replacement_connect(int __fd, const struct sockaddr *__addr,
                               socklen_t __addr_length) {
  if (__addr->sa_family == AF_INET || __addr->sa_family == AF_INET6) {
    __android_log_print(
        ANDROID_LOG_DEBUG, androidLogTag,
        "Refused connect system call with AF_INET or AF_INET6: %d",
        __addr->sa_family);
    return ECONNREFUSED;
  }

  return connect(__fd, __addr, __addr_length);
}

void initDisableConnectHook() {
  __android_log_print(ANDROID_LOG_DEBUG, androidLogTag,
                      "Initializing disable connection hook");
  GumInterceptor *interceptor = gum_interceptor_obtain();
  gum_interceptor_replace(
      interceptor,
      GSIZE_TO_POINTER(gum_module_find_export_by_name(nullptr, "connect")),
      (void *)replacement_connect, nullptr);
  gum_interceptor_end_transaction(interceptor);
}

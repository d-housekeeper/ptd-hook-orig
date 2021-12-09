#pragma once

#include "il2cpp-appdata.h"
#include <memory>

struct AndroidJavaObjectDisposer {
  void operator()(app::AndroidJavaObject *obj) const { app::AndroidJavaObject__Dispose(obj, nullptr); }
};

using AndroidJavaObjectPtr = std::unique_ptr<app::AndroidJavaObject, AndroidJavaObjectDisposer>;

AndroidJavaObjectPtr getJavaClass(const char *className);

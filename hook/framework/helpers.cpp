#include "helpers.h"
#include <codecvt>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

// https://github.com/joeyjurjens/Android-Hooking-Template/blob/110a40d58d9ebd274bdc6af2ac658ddc86556623/jni/Utils.h#L22
uintptr_t il2cppi_get_base_address() {
  FILE *fp;
  char filename[32], buffer[1024];
  snprintf(filename, 32, "/proc/%d/maps", getpid());
  fp = fopen(filename, "rt");
  if (fp != NULL) {
    while (fgets(buffer, sizeof(buffer), fp)) {
      if (strstr(buffer, libName)) {
        return (uintptr_t)strtoul(buffer, NULL, 16);
      }
    }
    fclose(fp);
  }

  return 0;
}

// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString *str) {
  std::u16string u16(reinterpret_cast<const char16_t *>(str->chars));
  return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String *str) { return il2cppi_to_string(reinterpret_cast<Il2CppString *>(str)); }

// Helper function to get object's vtable
uintptr_t il2cppi_get_interface_vtable(app::Object *object, Il2CppClass *interfaceType) {
  Il2CppClass *klass = (Il2CppClass *)object->klass;
  for (uint16_t i = 0; i < klass->interface_offsets_count; i++) {
    Il2CppRuntimeInterfaceOffsetPair interfaceOffset = klass->interfaceOffsets[i];
    if (interfaceOffset.interfaceType == interfaceType) {
      return (uintptr_t)&klass->vtable + (sizeof(VirtualInvokeData) * (uintptr_t)interfaceOffset.offset);
    }
  }

  return (uintptr_t) nullptr;
}

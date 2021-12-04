#pragma once

#include <cstdint>
#include <string>

static const char *libName = "libil2cpp.so";

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address();

// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString *str);

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String *str);

// Helper function to get object's vtable
uintptr_t il2cppi_get_interface_vtable(app::Object *object, Il2CppClass *interfaceType);

#pragma once

#include <memory>
#include <stdexcept>
#include <string>

static const char *androidLogTag = "PTDHook";

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf/26221725#26221725
template <typename... Args>
std::string string_format(const std::string &format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) +
               1; // Extra space for '\0'
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  auto buf = std::make_unique<char[]>(size);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1); // We don't want the '\0' inside
}

static bool stringEndsWith(const char *str, const char *suffix) {
  if (!str || !suffix) {
    return 0;
  }
  size_t lenStr = strlen(str);
  size_t lenSuffix = strlen(suffix);
  if (lenSuffix > lenStr) {
    return 0;
  }
  return strncmp(str + lenStr - lenSuffix, suffix, lenSuffix) == 0;
}

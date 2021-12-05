#pragma once

#include <memory>
#include <stdexcept>
#include <string>

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf/26221725#26221725
template <typename... Args> std::string string_format(const std::string &format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  auto buf = std::make_unique<char[]>(size);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c/42844629#42844629
static bool stringEndsWith(const std::string &str, const char *suffix, unsigned suffixLen) {
  return str.size() >= suffixLen && 0 == str.compare(str.size() - suffixLen, suffixLen, suffix, suffixLen);
}

static bool stringEndsWith(const std::string &str, const char *suffix) {
  return stringEndsWith(str, suffix, std::string::traits_type::length(suffix));
}

static bool stringStartsWith(const std::string &str, const char *prefix, unsigned prefixLen) {
  return str.size() >= prefixLen && 0 == str.compare(0, prefixLen, prefix, prefixLen);
}

static bool stringStartsWith(const std::string &str, const char *prefix) {
  return stringStartsWith(str, prefix, std::string::traits_type::length(prefix));
}

#pragma once

#include <cctype>
#include <cstdint>
#include <string>

#if defined(__GNUC__)
#include <strings.h>
#define _stricmp strcasecmp
#endif

namespace L4 {
namespace Utils {

namespace {

// https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
// http://burtleburtle.net/bob/hash/doobs.html
template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}  // namespace

// CaseInsensitiveStdStringComparer is a STL-compatible case-insensitive ANSI
// std::string comparer.
struct CaseInsensitiveStdStringComparer {
  bool operator()(const std::string& str1, const std::string& str2) const {
    return _stricmp(str1.c_str(), str2.c_str()) == 0;
  }
};

// CaseInsensitiveStringComparer is a STL-compatible case-insensitive ANSI
// string comparer.
struct CaseInsensitiveStringComparer {
  bool operator()(const char* const str1, const char* const str2) const { return _stricmp(str1, str2) == 0; }
};

// CaseInsensitiveStringHasher is a STL-compatible case-insensitive ANSI
// std::string hasher.
struct CaseInsensitiveStdStringHasher {
  std::size_t operator()(const std::string& str) const {
    std::size_t seed = 0;

    for (auto c : str) {
      hash_combine(seed, std::toupper(c));
    }

    return seed;
  }
};

// CaseInsensitiveStringHasher is a STL-compatible case-insensitive ANSI string
// hasher.
struct CaseInsensitiveStringHasher {
  std::size_t operator()(const char* str) const {
    assert(str != nullptr);

    std::size_t seed = 0;

    while (*str) {
      hash_combine(seed, std::toupper(*str++));
    }

    return seed;
  }
};

}  // namespace Utils
}  // namespace L4

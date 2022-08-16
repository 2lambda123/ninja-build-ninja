// Copyright 2021 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NINJA_FILE_PATH_H_
#define NINJA_FILE_PATH_H_

#include <string>

#ifndef TEXT
#ifdef  UNICODE
#define __TEXT(quote) L##quote
#else   /* UNICODE */
#define __TEXT(quote) quote
#endif /* UNICODE */
#define TEXT(quote) __TEXT(quote)
#endif

#ifndef _TCHAR_DEFINED
#ifdef UNICODE
typedef wchar_t TCHAR, *PTCHAR;
#else
typedef char TCHAR, *PTCHAR;
#endif
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

#ifdef UNICODE
typedef std::wstring file_string_t;
#else
typedef std::string file_string_t;
#endif

#ifdef UNICODE

bool NarrowPath(const std::wstring& path, std::string* narrowPath, std::string* err);

#endif

inline bool NarrowPath(const std::string& path, std::string* narrowPath, std::string* err) {
  *narrowPath = path;
  return true;
}

inline std::wstring WidenPath(const std::string& path) {
  return std::wstring(path.begin(), path.end());
}

inline std::wstring WidenPath(const std::wstring& path) {
  return path;
}

#ifdef UNICODE
inline std::wstring ToPathWidth(const std::string& path) {
  return WidenPath(path);
}

inline std::wstring ToPathWidth(const std::wstring& path) {
  return path;
}
#else
inline std::string ToPathWidth(const std::string& path) {
  return path;
}

inline std::string ToPathWidth(const std::wstring& path) {
  return NarrowPath(path);
}
#endif

struct file_string : public file_string_t {
  file_string() : file_string_t() {}
  file_string(const std::string& path) : file_string_t(ToPathWidth(path)) {}
  file_string(const std::wstring& path) : file_string_t(ToPathWidth(path)) {}
  file_string(const char* path) : file_string_t(ToPathWidth(path)) {}
  file_string(const wchar_t* path) : file_string_t(ToPathWidth(path)) {}

  operator const TCHAR*() const { return c_str(); }

  file_string operator+(const std::string& r) {
    return this->append(ToPathWidth(r));
  }

  file_string operator+(const std::wstring& r) {
    return this->append(ToPathWidth(r));
  }

  file_string operator+(const char* r) {
    return this->append(ToPathWidth(r));
  }

  file_string operator+(const wchar_t* r) {
    return this->append(ToPathWidth(r));
  }

  bool operator==(const std::string& r) {
    return this->compare(ToPathWidth(r)) == 0;
  }

  bool operator==(const std::wstring& r) {
    return this->compare(ToPathWidth(r)) == 0;
  }

  bool operator==(const char* r) {
    return this->compare(ToPathWidth(r)) == 0;
  }

  bool operator==(const wchar_t* r) {
    return this->compare(ToPathWidth(r)) == 0;
  }
};

#endif  // NINJA_FILE_PATH_H_

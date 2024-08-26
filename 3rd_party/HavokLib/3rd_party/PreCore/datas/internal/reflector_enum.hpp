/*  Contains macros/classes for reflection of enums
    internal file

    Copyright 2018-2021 Lukas Cone

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once
#include <cstddef>

template <size_t n>
constexpr size_t _GetReflEnumItemSize(const char (&value)[n]) {
  size_t curIndex = 1;

  for (const auto c : value) {
    if (c == '=' || c == ' ' || !c) {
      curIndex--;
      break;
    }
    curIndex++;
  }

  return curIndex;
}

#define _REFLECTOR_ADDN_ENUM(value) {#value, _GetReflEnumItemSize(#value)},
#define _REFLECTOR_ADDN_ENUMVAL(value) value,
#define _REFLECTOR_ADDN_ENUMDUMMY(value) 0,

#define _REFLECTOR_ENUM_CLASS_CLASS class
#define _REFLECTOR_ENUM_CLASS_64
#define _REFLECTOR_ENUM_CLASS_32
#define _REFLECTOR_ENUM_CLASS_16
#define _REFLECTOR_ENUM_CLASS_8

#define _REFLECTOR_ENUM_SIZE_64 : uint64
#define _REFLECTOR_ENUM_SIZE_32 : uint32
#define _REFLECTOR_ENUM_SIZE_16 : uint16
#define _REFLECTOR_ENUM_SIZE_8 : uint8
#define _REFLECTOR_ENUM_SIZE_CLASS

#define _REFLECTOR_ENUM_MAIN_BODY(classname, ...)                              \
  {StaticFor(_REFLECTOR_ADDN_ENUMVAL, __VA_ARGS__)};                           \
  template <> struct _EnumWrap<classname> {                                    \
    static const size_t NUM_ITEMS = VA_NARGS(__VA_ARGS__);                     \
    static const es::string_view *GetNames() {                                 \
      static constexpr es::string_view names[] = {                             \
          StaticFor(_REFLECTOR_ADDN_ENUM, __VA_ARGS__)};                       \
      return names;                                                            \
    }                                                                          \
    static uint64 *GetValues() {                                               \
      static uint64 _reflectedValues[NUM_ITEMS] = {};                          \
      return _reflectedValues;                                                 \
    }                                                                          \
    static constexpr es::string_view GetClassName() { return #classname; }     \
    static constexpr JenHash GetHash() { return JenHash(#classname); }         \
    static bool Initialized(bool yes) {                                        \
      static bool inited = false;                                              \
      if (!inited && yes) {                                                    \
        inited = true;                                                         \
        return true;                                                           \
      }                                                                        \
      return inited;                                                           \
    }                                                                          \
  };

#define _REFLECTOR_ENUM_VER0(classname, ...)                                   \
  enum classname _REFLECTOR_ENUM_MAIN_BODY(classname, __VA_ARGS__);

#define _REFLECTOR_ENUM_VER1(classname, var01, ...)                            \
  enum _REFLECTOR_ENUM_CLASS_##var01 classname                                 \
      _REFLECTOR_ENUM_SIZE_##var01 _REFLECTOR_ENUM_MAIN_BODY(classname,        \
                                                             __VA_ARGS__);

#define _REFLECTOR_ENUM_VER2(classname, var01, var02, ...)                     \
  enum _REFLECTOR_ENUM_CLASS_##var01 _REFLECTOR_ENUM_CLASS_##var02 classname   \
      _REFLECTOR_ENUM_SIZE_##var01 _REFLECTOR_ENUM_SIZE_##var02                \
          _REFLECTOR_ENUM_MAIN_BODY(classname, __VA_ARGS__);

#define _REFLECTOR_ENUM_VER3(classname, var01, var02, var03, ...)              \
  enum _REFLECTOR_ENUM_CLASS_##var01 _REFLECTOR_ENUM_CLASS_##var02             \
      _REFLECTOR_ENUM_CLASS_##var03 classname                                  \
          _REFLECTOR_ENUM_SIZE_##var01 _REFLECTOR_ENUM_SIZE_##var02            \
              _REFLECTOR_ENUM_SIZE_##var03 _REFLECTOR_ENUM_MAIN_BODY(          \
                  classname, __VA_ARGS__);

#define _REFLECTOR_START_VERENUM(classname, numFlags, ...)                     \
  VA_NARGS_EVAL(_REFLECTOR_ENUM_VER##numFlags(classname, __VA_ARGS__))

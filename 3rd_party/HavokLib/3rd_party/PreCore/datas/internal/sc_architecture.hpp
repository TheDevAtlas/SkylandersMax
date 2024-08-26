/*  Supercore architecture detectors/macros

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
#include "sc_type.hpp"
#include <type_traits>

#if defined(__GNUC__) || defined(__GNUG__)
#define ES_PRAGMA(command) _Pragma(#command)
#define ES_EXPORT __attribute__((visibility("default")))
#define ES_IMPORT
#define ES_EXPORT_FN(what) what ES_EXPORT
#define ES_IMPORT_FN(what) what ES_IMPORT
#elif defined(_MSC_VER)
#define ES_PRAGMA(command) __pragma(command)
#define ES_EXPORT __declspec(dllexport)
#define ES_IMPORT __declspec(dllimport)
#define ES_EXPORT_FN(what) ES_EXPORT what
#define ES_IMPORT_FN(what) ES_IMPORT what
#endif

#define ES_STATIC_ASSERT(what) static_assert(what, #what)

#if defined(__cplusplus) || defined(c_plusplus)

static inline bool LittleEndian() {
  static const union {
    const uint32 NUM;
    const uint8 ACT[4];
  } end_dec{1};

  return end_dec.ACT[0] == 1;
}

static constexpr bool ES_X64 = sizeof(void *) == 8;

constexpr bool ReusePadding() {
  struct Base_ {};
  struct Derived_ : Base_ {
    uint32 v1;
    uint16 v20;
  };
  struct Final_ : Derived_ {
    uint8 v21;
  };

  return sizeof(Final_) == 8;
}

static constexpr bool ES_REUSE_PADDING = ReusePadding();

typedef typename std::conditional<ES_X64, uint64, uint32>::type esIntPtr;

#else
static const int ES_X64 = sizeof(void *) == 8;
#endif

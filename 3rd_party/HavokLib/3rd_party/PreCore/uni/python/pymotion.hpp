/*  Python binding classes for uni::Motion
    part of uni module
    Copyright 2020 Lukas Cone

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
#include "uni/motion.hpp"
#include "datas/pythonex.hpp"

namespace UniPy {
struct MotionTrack {
  PyObject_HEAD;
  uni::Element<const uni::MotionTrack> item;

  static void Dealloc(MotionTrack *self);
  static PyObject *TrackType(MotionTrack *self);
  static PyObject *BoneIndex(MotionTrack *self);
  static PyObject *GetValues(MotionTrack *self, PyObject *time);

  static PyTypeObject *GetType();
};

struct Motion {
  PyObject_HEAD;
  union {
    uni::Element<const uni::Motion> item;
    uni::Element<uni::Motion> sitem;
  };

  static void Dealloc(Motion *self);
  static PyObject *Name(Motion *self);
  static PyObject *Duration(Motion *self);
  static PyObject *Tracks(Motion *self);
  static PyObject *MotionType(Motion *self);
  static PyObject *FrameRate(Motion *self);

  static int SetFrameRate(Motion *self, PyObject *var);

  static void InitType(PyObject *module);
  static PyTypeObject *GetType();
  static PyTypeObject *GetListType();
  static PyObject *Create(uni::MotionsConst &&tp);
  static Motion *Create(uni::Element<const uni::Motion> &&tp);
};
} // namespace UniPy
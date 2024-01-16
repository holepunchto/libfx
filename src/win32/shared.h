#pragma once

#include <windows.h>

template <typename T>
static inline RECT
fx__rect (T x, T y, T width, T height) {
  RECT rect;

  rect.top = LONG(x);
  rect.left = LONG(y);
  rect.right = LONG(x + width);
  rect.bottom = LONG(y + height);

  return rect;
}

template <typename T = LONG>
static inline T
fx__rect_x (RECT rect) {
  return T(rect.left);
}

template <typename T = LONG>
static inline LONG
fx__rect_y (RECT rect) {
  return T(rect.top);
}

template <typename T = LONG>
static inline T
fx__rect_width (RECT rect) {
  return T(rect.right - rect.left);
}

template <typename T = LONG>
static inline T
fx__rect_height (RECT rect) {
  return T(rect.bottom - rect.top);
}

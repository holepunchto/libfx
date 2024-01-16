#pragma once

#include <uv.h>

#include <windows.h> // Must be included after uv.h

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

static inline int
fx__to_wstring (const char *str, int str_len, PWCHAR wstr, int wstr_len) {
  wstr_len = MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstr, wstr_len);

  if (wstr_len == 0) return uv_translate_sys_error(GetLastError());

  if (str_len != -1) {
    wstr_len += 1; /* NULL */

    if (wstr != NULL) wstr[wstr_len - 1] = L'\0';
  }

  return wstr_len;
}

static inline int
fx__to_string (PCWCHAR wstr, int wstr_len, char *str, int str_len) {
  str_len = WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, str, str_len, NULL, NULL);

  if (str_len == 0) return uv_translate_sys_error(GetLastError());

  if (wstr_len != -1) {
    str_len += 1; /* NULL */

    if (str != NULL) str[str_len - 1] = '\0';
  }

  return str_len;
}

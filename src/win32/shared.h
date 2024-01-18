#pragma once

#include <uv.h>

#include <windows.h> // Must be included after uv.h

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

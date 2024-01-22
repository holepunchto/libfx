#pragma once

#include <uv.h>

#include <hstring.h> // Must be included after uv.h
#include <winstring.h>

#include "winui.h"

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
fx__from_wstring (PCWCHAR wstr, int wstr_len, char *str, int str_len) {
  str_len = WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, str, str_len, NULL, NULL);

  if (str_len == 0) return uv_translate_sys_error(GetLastError());

  if (wstr_len != -1) {
    str_len += 1; /* NULL */

    if (str != NULL) str[str_len - 1] = '\0';
  }

  return str_len;
}

static inline int
fx__to_hstring (const char *str, int str_len, hstring &hstring) {
  HRESULT res;

  int wstr_len = fx__to_wstring(str, str_len, NULL, 0);

  if (wstr_len < 0) return wstr_len;

  PWCHAR wstr;
  HSTRING_BUFFER buffer;

  res = WindowsPreallocateStringBuffer(wstr_len, &wstr, &buffer);

  if (FAILED(res)) return uv_translate_sys_error(GetLastError());

  fx__to_wstring(str, str_len, wstr, wstr_len);

  HSTRING handle;

  res = WindowsPromoteStringBuffer(buffer, &handle);

  if (FAILED(res)) {
    WindowsDeleteStringBuffer(buffer);

    return uv_translate_sys_error(GetLastError());
  }

  attach_abi(hstring, handle);

  return 0;
}

static inline int
fx__from_hstring (const hstring &hstring, char *str, int str_len) {
  return fx__from_wstring(hstring.data(), hstring.size(), str, str_len);
}

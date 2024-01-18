#include "text.h"
#include "../../include/fx.h"
#include "shared.h"
#include "winui.h"

extern "C" int
fx_text_init (fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  auto text = new fx_text_t();

  text->node.type = fx_text_node;

  *result = text;

  return 0;
}

extern "C" int
fx_text_destroy (fx_text_t *text) {
  delete text;

  return 0;
}

extern "C" int
fx_get_text_data (fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

extern "C" int
fx_set_text_data (fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

extern "C" int
fx_get_text_bounds (fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_get_text_bounds_used (fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_text_bounds (fx_text_t *text, float x, float y, float width, float height) {
  return 0;
}

extern "C" int
fx_append_text_span (fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  auto wstr_len = fx__to_wstring(value, len, NULL, 0);

  auto wstr = new wchar_t[wstr_len];

  fx__to_wstring(value, len, wstr, wstr_len);

  Run run;

  run.Text(wstr);

  delete[] wstr;

  text->handle.Inlines().Append(run);

  if (result) {
    auto span = new fx_text_span_t();

    span->start = 0;
    span->end = 0;

    *result = span;
  }

  return 0;
}

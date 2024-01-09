#include "text.h"
#include "../../include/fx.h"

static const char *fx_text_class = "EDIT";

extern "C" int
fx_text_init (fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  auto instance = GetModuleHandle(NULL);

  auto handle = CreateWindowEx(
    0,
    fx_text_class,
    NULL,
    WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE,
    (int) x,
    (int) y,
    (int) width,
    (int) height,
    HWND_MESSAGE,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  auto text = new fx_text_t();

  text->node.type = fx_text_node;

  text->handle = handle;

  *result = text;

  return 0;
}

extern "C" int
fx_text_destroy (fx_text_t *text) {
  DestroyWindow(text->handle);

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
  if (result) {
    auto span = new fx_text_span_t();

    span->start = 0;
    span->end = 0;

    *result = span;
  }

  return 0;
}

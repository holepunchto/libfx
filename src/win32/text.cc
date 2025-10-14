#include "text.h"

#include "../../include/fx.h"
#include "shared.h"
#include "winui.h"

extern "C" int
fx_text_init(fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  auto text = new fx_text_t();

  text->node.type = fx_text_node;

  text->handle.Width(width);
  text->handle.Height(height);

  text->handle.TextWrapping(TextWrapping::Wrap);

  text->bounds.x = x;
  text->bounds.y = y;
  text->bounds.width = width;
  text->bounds.height = height;

  *result = text;

  return 0;
}

extern "C" int
fx_text_destroy(fx_text_t *text) {
  delete text;

  return 0;
}

extern "C" int
fx_get_text_data(fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

extern "C" int
fx_set_text_data(fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

extern "C" int
fx_get_text_bounds(fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = text->bounds.x;
  if (y) *y = text->bounds.y;
  if (width) *width = text->bounds.width;
  if (height) *height = text->bounds.height;

  return 0;
}

template <typename T>
static inline T
fx_text_layout_dimension(T value) {
  return isnan(value) ? std::numeric_limits<T>::infinity() : value;
}

extern "C" int
fx_get_text_bounds_used(fx_text_t *text, float *x, float *y, float *width, float *height) {
  text->handle.Measure({
    fx_text_layout_dimension(text->bounds.width),
    fx_text_layout_dimension(text->bounds.height),
  });

  auto size = text->handle.DesiredSize();

  if (x) *x = text->bounds.x;
  if (y) *y = text->bounds.y;
  if (width) *width = size.Width;
  if (height) *height = size.Height;

  return 0;
}

extern "C" int
fx_set_text_bounds(fx_text_t *text, float x, float y, float width, float height) {
  text->handle.Width(width);
  text->handle.Height(width);

  text->bounds.x = x;
  text->bounds.y = y;
  text->bounds.width = width;
  text->bounds.height = height;

  return 0;
}

extern "C" int
fx_append_text_span(fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  int err;

  hstring hstr;
  err = fx__to_hstring(value, len, hstr);
  if (err < 0) return err;

  Run run;
  run.Text(hstr);

  text->handle.Inlines().Append(run);

  if (result) {
    auto span = new fx_text_span_t();

    span->start = 0;
    span->end = 0;

    *result = span;
  }

  return 0;
}

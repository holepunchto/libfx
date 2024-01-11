#include <gtk/gtk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "text.h"

int
fx_text_init (fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  GtkWidget *handle = gtk_label_new(NULL);

  if (handle == NULL) return -1;

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->handle = GTK_LABEL(handle);

  *result = text;

  gtk_widget_set_visible(handle, true);

  gtk_widget_set_size_request(handle, width, height);

  return 0;
}

int
fx_text_destroy (fx_text_t *text) {
  free(text);

  return 0;
}

int
fx_get_text_data (fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

int
fx_set_text_data (fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

int
fx_get_text_bounds (fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_get_text_bounds_used (fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_set_text_bounds (fx_text_t *text, float x, float y, float width, float height) {
  return 0;
}

int
fx_append_text_span (fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  gtk_label_set_text(text->handle, value);

  if (result) {
    fx_text_span_t *span = malloc(sizeof(fx_text_span_t));

    span->start = 0;
    span->end = 0;

    *result = span;
  }

  return 0;
}

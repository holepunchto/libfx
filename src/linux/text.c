#include "text.h"

#include "../../include/fx.h"

#include <gtk/gtk.h>
#include <stdlib.h>

int
fx_text_init(fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  GtkWidget *handle = gtk_label_new(NULL);

  if (handle == NULL) return -1;

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->handle = GTK_LABEL(handle);

  text->parent = NULL;

  text->bounds.x = x;
  text->bounds.y = y;
  text->bounds.width = width;
  text->bounds.height = height;

  *result = text;

  gtk_widget_set_visible(handle, true);

  gtk_widget_set_size_request(handle, width, height);

  return 0;
}

int
fx_text_destroy(fx_text_t *text) {
  free(text);

  return 0;
}

int
fx_get_text_data(fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

int
fx_set_text_data(fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

int
fx_get_text_bounds(fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = text->bounds.x;
  if (y) *y = text->bounds.y;
  if (width) *width = text->bounds.width;
  if (height) *height = text->bounds.height;

  return 0;
}

int
fx_get_text_bounds_used(fx_text_t *text, float *x, float *y, float *width, float *height) {
  if (x) *x = text->bounds.x;
  if (y) *y = text->bounds.y;
  if (width) *width = gtk_widget_get_allocated_width(GTK_WIDGET(text->handle));
  if (height) *height = gtk_widget_get_allocated_height(GTK_WIDGET(text->handle));

  return 0;
}

int
fx_set_text_bounds(fx_text_t *text, float x, float y, float width, float height) {
  text->bounds.x = x;
  text->bounds.y = y;
  text->bounds.width = width;
  text->bounds.height = height;

  return 0;
}

int
fx_append_text_span(fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  gtk_label_set_text(text->handle, value);

  if (result) {
    fx_text_span_t *span = malloc(sizeof(fx_text_span_t));

    span->start = 0;
    span->end = 0;

    *result = span;
  }

  return 0;
}

#include <stdlib.h>

#include "../../include/fx.h"
#include "text-input.h"

int
fx_text_input_init (fx_t *app, float x, float y, float width, float height, fx_text_input_t **result) {
  fx_text_input_t *text_input = malloc(sizeof(fx_text_input_t));

  text_input->node.type = fx_text_input_node;

  *result = text_input;

  return 0;
}

int
fx_text_input_destroy (fx_text_input_t *text_input) {
  free(text_input);

  return 0;
}

int
fx_on_text_input_change (fx_text_input_t *text_input, fx_text_input_change_cb cb) {
  text_input->on_change = cb;

  return 0;
}

int
fx_get_text_input_data (fx_text_input_t *text_input, void **result) {
  *result = text_input->data;

  return 0;
}

int
fx_set_text_input_data (fx_text_input_t *text_input, void *data) {
  text_input->data = data;

  return 0;
}

int
fx_get_text_input_bounds (fx_text_input_t *text_input, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

int
fx_set_text_input_bounds (fx_text_input_t *text_input, float x, float y, float width, float height) {
  return 0;
}

char *
fx_get_text_input_value (fx_text_input_t *text_input) {
  return NULL;
}

int
fx_set_text_input_value (fx_text_input_t *text_input, const char *value, size_t len) {
  return 0;
}

bool
fx_is_text_input_enabled (fx_text_input_t *text_input) {
  return false;
}

int
fx_set_text_input_enabled (fx_text_input_t *text_input, bool enabled) {
  return 0;
}

bool
fx_is_text_input_selectable (fx_text_input_t *text_input) {
  return false;
}

int
fx_set_text_input_selectable (fx_text_input_t *text_input, bool selectable) {
  return 0;
}

bool
fx_is_text_input_editable (fx_text_input_t *text_input) {
  return false;
}

int
fx_set_text_input_editable (fx_text_input_t *text_input, bool editable) {
  return 0;
}

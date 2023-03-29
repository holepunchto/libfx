#include "../../include/fx.h"
#include "image.h"
#include "scroll-view.h"
#include "text-input.h"
#include "text.h"
#include "video.h"
#include "view.h"
#include "web-view.h"

static inline int
fx_get_parent_window (fx_node_t *parent, HWND *result) {
  HWND parent_window;

  switch (parent->type) {
  case fx_view_node:
    parent_window = ((fx_view_t *) parent)->handle;
    break;
  default:
    return -1;
  }

  *result = parent_window;

  return 0;
}

static inline int
fx_get_child_window (fx_node_t *child, HWND *result) {
  HWND child_window;

  switch (child->type) {
  case fx_view_node:
    child_window = ((fx_view_t *) child)->handle;
    break;
  case fx_scroll_view_node:
    child_window = ((fx_scroll_view_t *) child)->handle;
    break;
  case fx_text_node:
    child_window = ((fx_text_t *) child)->handle;
    break;
  case fx_text_input_node:
    child_window = ((fx_text_input_t *) child)->handle;
    break;
  case fx_image_node:
    child_window = ((fx_image_t *) child)->handle;
    break;
  case fx_video_node:
    child_window = ((fx_video_t *) child)->handle;
    break;
  case fx_web_view_node:
    child_window = ((fx_web_view_t *) child)->handle;
    break;
  }

  *result = child_window;

  return 0;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  int err;

  HWND parent_window;

  err = fx_get_parent_window(parent, &parent_window);
  if (err < 0) return err;

  HWND child_window;

  err = fx_get_child_window(child, &child_window);
  if (err < 0) return err;

  if (SetParent(child_window, parent_window) == NULL) return -1;

  return 0;
}

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  HWND child_window;

  int err = fx_get_child_window(child, &child_window);
  if (err < 0) return err;

  if (SetParent(child_window, HWND_MESSAGE) == NULL) return -1;

  return 0;
}

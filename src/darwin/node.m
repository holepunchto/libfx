#import "../../include/fx.h"
#import "image.h"
#import "scroll-view.h"
#import "text-input.h"
#import "text.h"
#import "video.h"
#import "view.h"
#import "web-view.h"

#import <AppKit/AppKit.h>

static inline int
fx_get_parent_view (fx_node_t *parent, NSView **result) {
  NSView *parent_view;

  switch (parent->type) {
  case fx_view_node:
    parent_view = ((fx_view_t *) parent)->handle;
    break;
  default:
    return -1;
  }

  *result = parent_view;

  return 0;
}

static inline int
fx_get_child_view (fx_node_t *child, NSView **result) {
  NSView *child_view;

  switch (child->type) {
  case fx_view_node:
    child_view = ((fx_view_t *) child)->handle;
    break;
  case fx_scroll_view_node:
    child_view = ((fx_scroll_view_t *) child)->handle;
    break;
  case fx_text_node:
    child_view = ((fx_text_t *) child)->handle;
    break;
  case fx_text_input_node:
    child_view = ((fx_text_input_t *) child)->handle;
    break;
  case fx_image_node:
    child_view = ((fx_image_t *) child)->handle;
    break;
  case fx_video_node:
    child_view = ((fx_video_t *) child)->handle;
    break;
  case fx_web_view_node:
    child_view = ((fx_web_view_t *) child)->handle;
    break;
  }

  *result = child_view;

  return 0;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  int err;

  NSView *parent_view;
  err = fx_get_parent_view(parent, &parent_view);
  if (err < 0) return err;

  NSView *child_view;
  err = fx_get_child_view(child, &child_view);
  if (err < 0) return err;

  [parent_view addSubview:child_view];

  return 0;
}

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  int err;

  NSView *child_view;
  err = fx_get_child_view(child, &child_view);
  if (err < 0) return err;

  [child_view removeFromSuperview];

  return 0;
}

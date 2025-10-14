#import "../../include/fx.h"
#import "image.h"
#import "scroll-view.h"
#import "text-input.h"
#import "text.h"
#import "video.h"
#import "view.h"
#import "web-view.h"

#import <AppKit/AppKit.h>

static inline NSView *
fx_get_child_view(fx_node_t *child) {
  switch (child->type) {
  case fx_view_node:
    return ((fx_view_t *) child)->handle;

  case fx_scroll_view_node:
    return ((fx_scroll_view_t *) child)->handle;

  case fx_text_node:
    return ((fx_text_t *) child)->handle;

  case fx_text_input_node:
    return ((fx_text_input_t *) child)->handle;

  case fx_image_node:
    return ((fx_image_t *) child)->handle;

  case fx_video_node:
    return ((fx_video_t *) child)->handle;

  case fx_web_view_node:
    return ((fx_web_view_t *) child)->handle;
  }

  return NULL;
}

int
fx_set_child(fx_node_t *parent, fx_node_t *child, size_t index) {
  NSView *child_view = fx_get_child_view(child);

  switch (parent->type) {
  case fx_view_node: {
    [((fx_view_t *) parent)->handle addSubview:child_view];
    break;
  }

  default:
    return -1;
  }

  return 0;
}

int
fx_unset_child(fx_node_t *parent, fx_node_t *child, size_t index) {
  NSView *child_view = fx_get_child_view(child);

  [child_view removeFromSuperview];

  return 0;
}

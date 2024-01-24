#import "../../include/fx.h"
#import "image.h"
#import "scroll-view.h"
#import "text-input.h"
#import "text.h"
#import "video.h"
#import "view.h"
#import "web-view.h"

#import <UIKit/UIKit.h>

static inline UIView *
fx_get_child_view (fx_node_t *child) {
  switch (child->type) {
  case fx_view_node:
    return ((fx_view_t *) child)->native_view;

  case fx_scroll_view_node:
    return ((fx_scroll_view_t *) child)->native_scroll_view;

  case fx_text_node:
    return ((fx_text_t *) child)->native_text;

  case fx_text_input_node:
    return ((fx_text_input_t *) child)->native_text_input;

  case fx_image_node:
    return ((fx_image_t *) child)->native_image;

  case fx_video_node:
    return ((fx_video_t *) child)->native_video;

  case fx_web_view_node:
    return ((fx_web_view_t *) child)->native_web_view;
  }

  return NULL;
}

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  UIView *child_view = fx_get_child_view(child);

  switch (parent->type) {
  case fx_view_node:
    [((fx_view_t *) parent)->native_view addSubview:child_view];
    break;

  default:
    return -1;
  }

  return 0;
}

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  UIView *child_view = fx_get_child_view(child);

  [child_view removeFromSuperview];

  return 0;
}

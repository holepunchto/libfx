#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "image.h"
#import "scroll-view.h"
#import "text-input.h"
#import "text.h"
#import "video.h"
#import "view.h"
#import "web-view.h"

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  NSView *parent_view;

  switch (parent->type) {
  case fx_view_node:
    parent_view = ((fx_view_t *) parent)->native_view;
    break;
  default:
    return -1;
  }

  NSView *child_view;

  switch (child->type) {
  case fx_view_node:
    child_view = ((fx_view_t *) child)->native_view;
    break;
  case fx_scroll_view_node:
    child_view = ((fx_scroll_view_t *) child)->native_scroll_view;
    break;
  case fx_text_node:
    child_view = ((fx_text_t *) child)->native_text;
    break;
  case fx_text_input_node:
    child_view = ((fx_text_input_t *) child)->native_text_input;
    break;
  case fx_image_node:
    child_view = ((fx_image_t *) child)->native_image;
    break;
  case fx_video_node:
    child_view = ((fx_video_t *) child)->native_video;
    break;
  case fx_web_view_node:
    child_view = ((fx_web_view_t *) child)->native_web_view;
    break;
  }

  [parent_view addSubview:child_view];

  return 0;
}

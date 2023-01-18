#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "view.h"

@implementation FXView

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_view_init (fx_t *app, float x, float y, float width, float height, fx_view_t **result) {
  FXView *native_view = [[FXView alloc] initWithFrame:CGRectMake(x, y, width, height)];

  fx_view_t *view = malloc(sizeof(fx_view_t));

  view->node.type = fx_view_node;

  view->native_view = native_view;

  native_view.fxView = view;

  *result = view;

  return 0;
}

int
fx_view_destroy (fx_view_t *view) {
  [view->native_view release];

  free(view);

  return 0;
}

int
fx_get_view_data (fx_view_t *view, void **result) {
  *result = view->data;

  return 0;
}

int
fx_set_view_data (fx_view_t *view, void *data) {
  view->data = data;

  return 0;
}

int
fx_get_view_bounds (fx_view_t *view, float *x, float *y, float *width, float *height) {
  NSRect frame = view->native_view.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_view_bounds (fx_view_t *view, float x, float y, float width, float height) {
  view->native_view.frame = CGRectMake(x, y, width, height);

  return 0;
}

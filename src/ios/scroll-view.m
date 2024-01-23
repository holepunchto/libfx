#import "scroll-view.h"

#import "../../include/fx.h"
#import "view.h"

#import <UIKit/UIKit.h>

@implementation FXScrollView

@end

int
fx_scroll_view_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_scroll_view_t **result) {
  FXScrollView *native_scroll_view = [[FXScrollView alloc] initWithFrame:CGRectMake(x, y, width, height)];

  if (view) {
    [native_scroll_view addSubview:view->native_view];
  }

  fx_scroll_view_t *scroll_view = malloc(sizeof(fx_scroll_view_t));

  scroll_view->node.type = fx_scroll_view_node;

  scroll_view->native_scroll_view = native_scroll_view;

  native_scroll_view.fxScrollView = scroll_view;

  *result = scroll_view;

  return 0;
}

int
fx_scroll_view_destroy (fx_scroll_view_t *scroll_view) {
  [scroll_view->native_scroll_view release];

  free(scroll_view);

  return 0;
}

int
fx_get_scroll_view_data (fx_scroll_view_t *scroll_view, void **result) {
  *result = scroll_view->data;

  return 0;
}

int
fx_set_scroll_view_data (fx_scroll_view_t *scroll_view, void *data) {
  scroll_view->data = data;

  return 0;
}

int
fx_get_scroll_view_bounds (fx_scroll_view_t *scroll_view, float *x, float *y, float *width, float *height) {
  CGRect frame = scroll_view->native_scroll_view.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_scroll_view_bounds (fx_scroll_view_t *scroll_view, float x, float y, float width, float height) {
  scroll_view->native_scroll_view.frame = CGRectMake(x, y, width, height);

  return 0;
}

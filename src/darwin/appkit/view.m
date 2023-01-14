#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "view.h"

@implementation FXView

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_view_init (fx_t *app, double x, double y, double width, double height, fx_view_t **result) {
  FXView *native_view = [[FXView alloc] initWithFrame:CGRectMake(x, y, width, height)];

  fx_view_t *view = malloc(sizeof(fx_view_t));

  view->node.type = fx_view_node;

  view->native_view = native_view;

  native_view.fxView = view;

  *result = view;

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

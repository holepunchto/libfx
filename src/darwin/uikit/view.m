#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "view.h"

@implementation FXView

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

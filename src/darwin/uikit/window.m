#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "view.h"
#import "window.h"

@implementation FXWindowController

@end

@implementation FXWindow : UIWindow

@end

int
fx_window_init (fx_t *app, fx_view_t *view, double x, double y, double width, double height, fx_window_t **result) {
  FXWindow *native_window = [[FXWindow alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_window.rootViewController = [[FXWindowController alloc] init];

  [native_window makeKeyAndVisible];

  if (view) {
    [native_window addSubview:view->native_view];
  }

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->native_window = native_window;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;

  native_window.fxWindow = window;

  *result = window;

  return 0;
}

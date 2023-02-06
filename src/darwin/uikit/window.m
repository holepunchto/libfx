#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "view.h"
#import "window.h"

@implementation FXWindowController

@end

@implementation FXWindow : UIWindow

@end

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_window_t **result) {
  FXWindow *native_window = [[FXWindow alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_window.rootViewController = [[FXWindowController alloc] init];

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

bool
fx_is_window_visible (fx_window_t *window) {
  return !window->native_window.hidden;
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  window->native_window.hidden = !visible;

  return 0;
}

extern int
fx_show_window (fx_window_t *window);

extern int
fx_hide_window (fx_window_t *window);

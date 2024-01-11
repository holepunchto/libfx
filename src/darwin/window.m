#import <AppKit/AppKit.h>

#import "../../include/fx.h"
#import "view.h"
#import "window.h"

@implementation FXWindowDelegate

- (void)windowDidResize:(NSNotification *)notification {
  fx_window_t *window = ((FXWindow *) notification.object).fxWindow;

  if (window->on_resize != NULL) window->on_resize(window);
}

- (void)windowDidMove:(NSNotification *)notification {
  fx_window_t *window = ((FXWindow *) notification.object).fxWindow;

  if (window->on_move != NULL) window->on_move(window);
}

- (void)windowWillClose:(NSNotification *)notification {
  fx_window_t *window = ((FXWindow *) notification.object).fxWindow;

  if (window->on_close != NULL) window->on_close(window);
}

@end

@implementation FXWindow

@end

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_window_t **result) {
  FXWindow *native_window = [[FXWindow alloc]
    initWithContentRect:CGRectMake(x, y, width, height)
              styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
                backing:NSBackingStoreBuffered
                  defer:NO];

  native_window.delegate = [[FXWindowDelegate alloc] init];

  if (view) {
    native_window.contentView = view->handle;
  }

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->native_window = native_window;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  native_window.fxWindow = window;

  *result = window;

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  [window->native_window.delegate release];
  [window->native_window release];

  free(window);

  return 0;
}

int
fx_on_window_resize (fx_window_t *window, fx_window_resize_cb cb) {
  window->on_resize = cb;

  return 0;
}

int
fx_on_window_move (fx_window_t *window, fx_window_move_cb cb) {
  window->on_move = cb;

  return 0;
}

int
fx_on_window_minimize (fx_window_t *window, fx_window_minimize_cb cb) {
  window->on_minimize = cb;

  return 0;
}

int
fx_on_window_deminimize (fx_window_t *window, fx_window_deminimize_cb cb) {
  window->on_deminimize = cb;

  return 0;
}

int
fx_on_window_close (fx_window_t *window, fx_window_close_cb cb) {
  window->on_close = cb;

  return 0;
}

int
fx_get_window_data (fx_window_t *window, void **result) {
  *result = window->data;

  return 0;
}

int
fx_set_window_data (fx_window_t *window, void *data) {
  window->data = data;

  return 0;
}

int
fx_get_window_bounds (fx_window_t *window, float *x, float *y, float *width, float *height) {
  NSRect frame = window->native_window.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

bool
fx_is_window_visible (fx_window_t *window) {
  return window->native_window.visible;
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  [window->native_window setIsVisible:visible];

  return 0;
}

extern int
fx_show_window (fx_window_t *window);

extern int
fx_hide_window (fx_window_t *window);

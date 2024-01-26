#import "window.h"

#import "../../include/fx.h"
#import "shared.h"
#import "view.h"

#import <AppKit/AppKit.h>
#import <string.h>

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
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result) {
  NSWindowStyleMask style;

  if (flags & fx_window_no_frame) {
    style = NSWindowStyleMaskTitled | NSWindowStyleMaskFullSizeContentView;
  } else {
    style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
  }

  FXWindow *handle = [[FXWindow alloc]
    initWithContentRect:CGRectMake(x, y, width, height)
              styleMask:style
                backing:NSBackingStoreBuffered
                  defer:NO];

  handle.releasedWhenClosed = NO;

  if (flags & fx_window_no_frame) {
    handle.titleVisibility = NSWindowTitleHidden;
    handle.titlebarAppearsTransparent = YES;
  }

  handle.delegate = [[FXWindowDelegate alloc] init];

  if (view) handle.contentView = view->handle;

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->handle = handle;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  handle.fxWindow = window;

  *result = window;

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  [window->handle.delegate release];
  [window->handle release];

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
  NSRect frame = window->handle.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result) {
  const char *bytes = [window->handle.title UTF8String];

  if (title == NULL) {
    *result = strlen(bytes);
  } else if (len != 0) {
    size_t bytes_len = strlen(bytes);

    size_t written = len < bytes_len ? len : bytes_len;

    strncpy(title, bytes, written);

    if (written < len) title[written] = '\0';

    if (result) *result = written;
  } else if (result) *result = 0;

  return 0;
}

int
fx_set_window_title (fx_window_t *window, const char *title, size_t len) {
  window->handle.title = fx__string(title, len);

  return 0;
}

bool
fx_is_window_visible (fx_window_t *window) {
  return window->handle.visible;
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  [window->handle setIsVisible:visible];

  return 0;
}

bool
fx_is_window_resizable (fx_window_t *window) {
  return (window->handle.styleMask & NSWindowStyleMaskResizable) != 0;
}

int
fx_set_window_resizable (fx_window_t *window, bool resizable) {
  NSWindowStyleMask style = window->handle.styleMask;

  if (resizable) {
    style |= NSWindowStyleMaskResizable;
  } else {
    style &= ~NSWindowStyleMaskResizable;
  }

  [window->handle setStyleMask:style];

  return 0;
}

int
fx_activate_window (fx_window_t *window) {
  [window->handle makeKeyAndOrderFront:window->handle];

  return 0;
}

int
fx_close_window (fx_window_t *window) {
  [window->handle close];

  return 0;
}

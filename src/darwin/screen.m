#import <AppKit/AppKit.h>

#import "../../include/fx.h"
#import "screen.h"

int
fx_screen_destroy (fx_screen_t *screen) {
  [screen->native_screen release];

  free(screen);

  return 0;
}

int
fx_get_main_screen (fx_t *app, fx_screen_t **result) {
  fx_screen_t *screen = malloc(sizeof(fx_screen_t));

  screen->native_screen = [NSScreen mainScreen];

  [screen->native_screen retain];

  *result = screen;

  return 0;
}

int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  NSRect frame = screen->native_screen.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

#import "screen.h"

#import "../../include/fx.h"

#import <UIKit/UIKit.h>

int
fx_screen_release (fx_screen_t *screen) {
  [screen->native_screen release];

  free(screen);

  return 0;
}

int
fx_get_main_screen (fx_t *app, fx_screen_t **result) {
  fx_screen_t *screen = malloc(sizeof(fx_screen_t));

  screen->native_screen = [UIScreen mainScreen];

  [screen->native_screen retain];

  *result = screen;

  return 0;
}

int
fx_get_screen_bounds (fx_screen_t *screen, float *x, float *y, float *width, float *height) {
  CGRect bounds = screen->native_screen.bounds;

  if (x) *x = bounds.origin.x;
  if (y) *y = bounds.origin.y;
  if (width) *width = bounds.size.width;
  if (height) *height = bounds.size.height;

  return 0;
}

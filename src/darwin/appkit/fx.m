#import <assert.h>
#import <stdbool.h>
#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "../../shared/fx.h"
#import "fx.h"

@implementation FXDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  fx_t *app = ((FX *) notification.object).fxMainApp;

  if (app->platform->on_launch != NULL) app->platform->on_launch(app);
}

- (void)applicationWillTerminate:(NSNotification *)notification {
  fx_t *app = ((FX *) notification.object).fxMainApp;

  if (app->platform->on_terminate != NULL) app->platform->on_terminate(app);
}

@end

@implementation FX

@end

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  FX *native_app = [FX sharedApplication];

  if (fx_is_main(app)) {
    native_app.delegate = [[FXDelegate alloc] init];
    native_app.fxMainApp = app;
  }

  platform->native_app = native_app;

  *result = platform;

  return 0;
}

int
fx_platform_destroy (fx_platform_t *platform) {
  free(platform);

  return 0;
}

int
fx_platform_run (fx_platform_t *platform, fx_launch_cb cb) {
  platform->on_launch = cb;

  [platform->native_app run];

  return 0;
}

int
fx_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  platform->on_terminate = cb;

  [platform->native_app terminate:platform->native_app];

  return 0;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  dispatch_async(dispatch_get_main_queue(), ^{
    cb(fx_main_app, data);
  });

  return 0;
}

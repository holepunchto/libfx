#import <stdbool.h>
#import <uv.h>

#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "../../shared/fx.h"
#import "fx.h"

static fx_t *fx_main_app = NULL;

@implementation FXDelegate

- (BOOL)application:(FX *)native_app didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  fx_t *app = native_app.fxMainApp;

  if (app->platform->on_launch) app->platform->on_launch(app);

  return YES;
}

@end

@implementation FX

@end

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  FX *native_app = (FX *) [FX sharedApplication];

  if (fx_is_main(app)) {
    native_app.fxMainApp = app;
  }

  platform->native_app = native_app;

  platform->on_launch = NULL;
  platform->on_message = NULL;

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

  UIApplicationMain(0, (char *[]){}, @"FX", @"FXDelegate");

  return 0;
}

int
fx_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  return 0;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  dispatch_async(dispatch_get_main_queue(), ^{
    cb(fx_main_app, data);
  });

  return 0;
}

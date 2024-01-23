#import "platform.h"

#import "../../include/fx.h"
#import "../shared/fx.h"

#import <UIKit/UIKit.h>
#import <stdbool.h>
#import <uv.h>

@implementation FXDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  fx_t *app = fx_main_app;

  if (app->platform->on_launch) app->platform->on_launch(app);

  return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application {
  fx_t *app = fx_main_app;

  if (app->platform->on_terminate) app->platform->on_terminate(app);
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  fx_t *app = fx_main_app;

  if (app->platform->on_suspend) app->platform->on_suspend(app);
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  fx_t *app = fx_main_app;

  if (app->platform->on_resume) app->platform->on_resume(app);
}

@end

@implementation FX

@end

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  FX *native_app = (FX *) [FX sharedApplication];

  platform->native_app = native_app;

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

int
fx_platform_destroy (fx_platform_t *platform) {
  free(platform);

  return 0;
}

int
fx_on_platform_launch (fx_platform_t *platform, fx_launch_cb cb) {
  platform->on_launch = cb;

  return 0;
}

int
fx_on_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  platform->on_terminate = cb;

  return 0;
}

int
fx_on_platform_suspend (fx_platform_t *platform, fx_suspend_cb cb) {
  platform->on_suspend = cb;

  return 0;
}

int
fx_on_platform_resume (fx_platform_t *platform, fx_resume_cb cb) {
  platform->on_resume = cb;

  return 0;
}

int
fx_platform_run (fx_platform_t *platform) {
  UIApplicationMain(0, (char *[]){}, @"FX", @"FXDelegate");

  return 0;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  dispatch_async(dispatch_get_main_queue(), ^{
    cb(fx_main_app, data);
  });

  return 0;
}

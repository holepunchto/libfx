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

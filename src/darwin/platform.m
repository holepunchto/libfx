#import "platform.h"

#import "../../include/fx.h"
#import "../shared/fx.h"

#import <AppKit/AppKit.h>
#import <stdbool.h>
#import <uv.h>

@implementation FXDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  fx_t *app = fx_main_app;

  if (app->platform->on_launch) app->platform->on_launch(app);
}

- (void)applicationWillTerminate:(NSNotification *)notification {
  fx_t *app = fx_main_app;

  if (app->platform->on_terminate) app->platform->on_terminate(app);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
  return YES;
}

@end

@implementation FX

@end

int
fx_platform_init(fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  FX *native_app = [FX sharedApplication];

  native_app.delegate = [[FXDelegate alloc] init];

  platform->native_app = native_app;

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

int
fx_platform_destroy(fx_platform_t *platform) {
  [platform->native_app.delegate release];

  free(platform);

  return 0;
}

#import "../../include/fx.h"

#import "../shared/fx.h"
#import "platform.h"

#import <UIKit/UIKit.h>

int
fx_run (fx_t *app, fx_launch_cb on_launch, fx_terminate_cb on_terminate) {
  app->platform->on_launch = on_launch;
  app->platform->on_terminate = on_terminate;

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

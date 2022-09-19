#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXDelegate : UIResponder <UIApplicationDelegate>

@end

@interface FX : UIApplication

@property(assign) fx_t *fxApp;

@end

struct fx_s {
  FX *native_app;

  uv_loop_t *loop;

  void *data;

  fx_launch_cb on_launch;
  fx_message_cb on_message;
};

#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXDelegate : UIResponder <UIApplicationDelegate>

@end

@interface FX : UIApplication

@property(assign) fx_t *fxMainApp;

@end

struct fx_platform_s {
  FX *native_app;

  fx_launch_cb on_launch;
  fx_message_cb on_message;
};

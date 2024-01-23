#import "../../include/fx.h"

#import <UIKit/UIKit.h>

@interface FXDelegate : UIResponder <UIApplicationDelegate>

@end

@interface FX : UIApplication

@end

struct fx_platform_s {
  FX *native_app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};

#import <UIKit/UIKit.h>

#import "../../include/fx.h"

@interface FXDelegate : UIResponder <UIApplicationDelegate>

@end

@interface FX : UIApplication

@end

struct fx_platform_s {
  FX *native_app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
  fx_suspend_cb on_suspend;
  fx_resume_cb on_resume;
};

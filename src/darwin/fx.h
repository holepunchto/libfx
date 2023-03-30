#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../include/fx.h"
#import "../shared/fx.h"

@interface FXDelegate : NSObject <NSApplicationDelegate>

@end

@interface FX : NSApplication

@end

struct fx_platform_s {
  FX *native_app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};

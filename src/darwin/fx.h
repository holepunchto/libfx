#import "../../include/fx.h"
#import "../shared/fx.h"

#import <AppKit/AppKit.h>
#import <uv.h>

@interface FXDelegate : NSObject <NSApplicationDelegate>

@end

@interface FX : NSApplication

@end

struct fx_platform_s {
  __unsafe_unretained FX *native_app;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
};

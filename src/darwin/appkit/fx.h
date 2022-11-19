#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "../../shared/fx.h"

@interface FXDelegate : NSObject <NSApplicationDelegate>

@end

@interface FX : NSApplication

@property(assign) fx_t *fxMainApp;

@end

struct fx_platform_s {
  FX *native_app;
};

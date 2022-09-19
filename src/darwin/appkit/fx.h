#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"

@interface FXDelegate : NSObject <NSApplicationDelegate>

@end

@interface FX : NSApplication

@property(assign) fx_t *fxApp;

@end

struct fx_s {
  FX *native_app;

  uv_loop_t *loop;

  void *data;

  fx_launch_cb on_launch;
  fx_message_cb on_message;
};

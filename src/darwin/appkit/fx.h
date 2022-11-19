#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "../../channel.h"

@interface FXDelegate : NSObject <NSApplicationDelegate>

@end

@interface FX : NSApplication

@property(assign) fx_t *fxMainApp;

@end

struct fx_s {
  FX *native_app;

  uv_loop_t *loop;

  void *data;

  fx_launch_cb on_launch;
  fx_terminate_cb on_terminate;
  fx_message_cb on_message;

  fx_channel_t messages;
};

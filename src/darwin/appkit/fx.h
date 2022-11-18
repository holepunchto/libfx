#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "../../message-queue.h"

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
  fx_message_cb on_message;

  fx_message_queue_t messages;
};

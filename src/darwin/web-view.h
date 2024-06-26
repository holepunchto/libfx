#import "../../include/fx.h"

#import <AppKit/AppKit.h>
#import <WebKit/WebKit.h>

@interface FXWebViewDelegate : NSObject <WKUIDelegate, WKScriptMessageHandler>

@end

@interface FXWebView : WKWebView

@property(assign) fx_web_view_t *fxWebView;

@end

struct fx_web_view_s {
  fx_node_t node;

  FXWebView *handle;

  void *data;

  fx_web_view_message_cb on_message;
};

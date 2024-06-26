#import "../../include/fx.h"

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

@interface FXWebViewDelegate : NSObject <WKUIDelegate, WKScriptMessageHandler>

@end

@interface FXWebView : WKWebView

@property(assign) fx_web_view_t *fxWebView;

@end

struct fx_web_view_s {
  fx_node_t node;

  FXWebView *native_web_view;

  void *data;

  fx_web_view_message_cb on_message;
};

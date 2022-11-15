#import <AppKit/AppKit.h>
#import <WebKit/WebKit.h>

#import "../../../include/fx.h"

@interface FXWebView : WKWebView

@property(assign) fx_web_view_t *fxWebView;

@end

struct fx_web_view_s {
  fx_node_t node;

  FXWebView *native_web_view;
};

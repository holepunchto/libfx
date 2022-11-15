#import <AppKit/AppKit.h>
#import <WebKit/WebKit.h>

#import "../../../include/fx.h"
#import "web-view.h"

@implementation FXWebView

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_web_view_init (fx_t *app, double x, double y, double width, double height, fx_web_view_t **result) {
  WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];

  FXWebView *native_web_view = [[FXWebView alloc] initWithFrame:CGRectMake(x, y, width, height)
                                                  configuration:configuration];

  fx_web_view_t *web_view = malloc(sizeof(fx_web_view_t));

  web_view->node.type = fx_web_view_node;

  web_view->native_web_view = native_web_view;

  native_web_view.fxWebView = web_view;

  *result = web_view;

  return 0;
}

int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len) {
  [web_view->native_web_view loadRequest:[[NSURLRequest alloc] initWithURL:[[NSURL alloc] initWithString:[[NSString alloc] initWithBytes:url length:len encoding:NSUTF8StringEncoding]]]];

  return 0;
}

int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len) {
  [web_view->native_web_view loadHTMLString:[[NSString alloc] initWithBytes:html length:len encoding:NSUTF8StringEncoding] baseURL:NULL];

  return 0;
}

#import "web-view.h"

#import "../../include/fx.h"
#import "../shared/bridge/webkit/bridge.h"
#import "shared.h"

#import <AppKit/AppKit.h>
#import <WebKit/WebKit.h>

@implementation FXWebViewDelegate

- (void)userContentController:(WKUserContentController *)userContentController
      didReceiveScriptMessage:(WKScriptMessage *)message {
  fx_web_view_t *web_view = ((FXWebView *) message.webView).fxWebView;

  if (web_view->on_message != NULL) web_view->on_message(web_view, [message.body UTF8String]);
}

@end

@implementation FXWebView

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_web_view_init (fx_t *app, float x, float y, float width, float height, fx_web_view_t **result) {
  WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];

  FXWebViewDelegate *delegate = [[FXWebViewDelegate alloc] init];

  [configuration.userContentController addScriptMessageHandler:delegate
                                                          name:@"bridge"];

  NSString *source = [[NSString alloc] initWithBytes:webkit_bridge_js
                                              length:webkit_bridge_js_len
                                            encoding:NSUTF8StringEncoding];

  WKUserScript *script = [[WKUserScript alloc] initWithSource:source
                                                injectionTime:WKUserScriptInjectionTimeAtDocumentStart
                                             forMainFrameOnly:NO];

  [source release];

  [configuration.userContentController addUserScript:script];

  [configuration.preferences setValue:@YES forKey:@"developerExtrasEnabled"];

  FXWebView *native_web_view = [[FXWebView alloc] initWithFrame:CGRectMake(x, y, width, height)
                                                  configuration:configuration];

  native_web_view.UIDelegate = delegate;

  fx_web_view_t *web_view = malloc(sizeof(fx_web_view_t));

  web_view->node.type = fx_web_view_node;

  web_view->handle = native_web_view;

  web_view->data = NULL;

  web_view->on_message = NULL;

  native_web_view.fxWebView = web_view;

  *result = web_view;

  return 0;
}

int
fx_web_view_destroy (fx_web_view_t *web_view) {
  [web_view->handle release];

  free(web_view);

  return 0;
}

int
fx_on_web_view_message (fx_web_view_t *web_view, fx_web_view_message_cb cb) {
  web_view->on_message = cb;

  return 0;
}

int
fx_get_web_view_data (fx_web_view_t *web_view, void **result) {
  *result = web_view->data;

  return 0;
}

int
fx_set_web_view_data (fx_web_view_t *web_view, void *data) {
  web_view->data = data;

  return 0;
}

int
fx_get_web_view_bounds (fx_web_view_t *web_view, float *x, float *y, float *width, float *height) {
  NSRect frame = web_view->handle.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_web_view_bounds (fx_web_view_t *web_view, float x, float y, float width, float height) {
  web_view->handle.frame = CGRectMake(x, y, width, height);

  return 0;
}

int
fx_web_view_post_message (fx_web_view_t *web_view, const char *message) {
  NSString *js = [[NSString alloc] initWithFormat:@"globalThis.bridge.dispatchMessage(%s)", message];

  [web_view->handle evaluateJavaScript:js
                     completionHandler:nil];

  [js release];

  return 0;
}

int
fx_web_view_load_url (fx_web_view_t *web_view, const char *url, size_t len) {
  [web_view->handle loadRequest:[[NSURLRequest alloc] initWithURL:fx__url(url, len)]];

  return 0;
}

int
fx_web_view_load_html (fx_web_view_t *web_view, const char *html, size_t len) {
  [web_view->handle loadHTMLString:fx__string(html, len) baseURL:NULL];

  return 0;
}

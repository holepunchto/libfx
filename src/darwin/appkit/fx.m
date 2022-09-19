#import <stdbool.h>
#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "fx.h"

static fx_t *fx_main_app = NULL;

@implementation FXDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  fx_t *app = ((FX *) notification.object).fxApp;

  if (app->on_launch != NULL) app->on_launch(app);
}

@end

@implementation FX

@end

int
fx_init (uv_loop_t *loop, fx_t **result) {
  FX *native_app = [FX sharedApplication];

  native_app.delegate = [[FXDelegate alloc] init];

  fx_t *app = malloc(sizeof(fx_t));

  if (fx_main_app == NULL) fx_main_app = app;

  app->native_app = native_app;

  app->loop = loop;

  app->data = NULL;

  app->on_launch = NULL;
  app->on_message = NULL;

  native_app.fxApp = app;

  *result = app;

  return 0;
}

int
fx_destroy (fx_t *app) {
  if (fx_is_main(app)) fx_main_app = NULL;

  free(app);

  return 0;
}

int
fx_run (fx_t *app) {
  [app->native_app run];

  return 0;
}

int
fx_stop (fx_t *app) {
  [app->native_app stop:app->native_app];

  return 0;
}

int
fx_terminate (fx_t *app) {
  [app->native_app terminate:app->native_app];

  return 0;
}

bool
fx_is_main (fx_t *app) {
  return app == fx_main_app;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  dispatch_async(dispatch_get_main_queue(), ^{
    cb(fx_main_app, data);
  });

  return 0;
}

static void
on_message (fx_t *app, void *data) {
  fx_send_t *req = (fx_send_t *) data;

  if (app->on_message) app->on_message(app, req->message, req->app);

  uv_async_send(&req->async);
}

static void
on_message_async_closed (uv_handle_t *handle) {
  fx_send_t *req = (fx_send_t *) handle->data;

  if (req->cb) req->cb(req);
}

static void
on_message_delivered (uv_async_t *async) {
  uv_close((uv_handle_t *) async, on_message_async_closed);
}

int
fx_send (fx_t *app, fx_send_t *req, void *message, fx_delivered_cb cb) {
  req->app = app;
  req->cb = cb;
  req->message = message;
  req->async.data = (void *) req;

  int err = uv_async_init(app->loop, &req->async, on_message_delivered);
  if (err < 0) return err;

  fx_dispatch(on_message, (void *) req);

  return 0;
}

int
fx_on_launch (fx_t *app, fx_launch_cb cb) {
  app->on_launch = cb;

  return 0;
}

int
fx_on_message (fx_t *app, fx_message_cb cb) {
  app->on_message = cb;

  return 0;
}

int
fx_get_data (fx_t *app, void **result) {
  *result = app->data;

  return 0;
}

int
fx_set_data (fx_t *app, void *data) {
  app->data = data;

  return 0;
}

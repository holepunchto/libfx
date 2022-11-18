#import <assert.h>
#import <stdbool.h>
#import <uv.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "../../message-queue.h"
#import "fx.h"

static fx_t *fx_main_app = NULL;

@implementation FXDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  fx_t *app = ((FX *) notification.object).fxMainApp;

  if (app->on_launch != NULL) app->on_launch(app);
}

@end

@implementation FX

@end

static void
on_message (fx_message_queue_t *queue) {
  fx_t *app = queue->app;
  fx_message_t *message;

  while ((message = fx_message_queue_pop(queue))) {
    if (app->on_message) app->on_message(app, &message->buf, message->sender);

    free(message);
  }
}

int
fx_init (uv_loop_t *loop, fx_t **result) {
  FX *native_app = [FX sharedApplication];

  native_app.delegate = [[FXDelegate alloc] init];

  fx_t *app = malloc(sizeof(fx_t));

  app->native_app = native_app;

  app->loop = loop;

  app->data = NULL;

  app->on_launch = NULL;
  app->on_message = NULL;

  int err;

  err = fx_message_queue_init(loop, app, &app->messages, 1024, on_message);
  assert(err == 0);

  if (fx_main_app == NULL) {
    native_app.fxMainApp = fx_main_app = app;
  }

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

int
fx_on_launch (fx_t *app, fx_launch_cb cb) {
  app->on_launch = cb;

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

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"

int
fx_platform_init (fx_t *app, fx_platform_t **result) {
  fx_platform_t *platform = malloc(sizeof(fx_platform_t));

  platform->on_launch = NULL;
  platform->on_terminate = NULL;

  *result = platform;

  return 0;
}

int
fx_platform_destroy (fx_platform_t *platform) {
  free(platform);

  return 0;
}

int
fx_on_platform_launch (fx_platform_t *platform, fx_launch_cb cb) {
  platform->on_launch = cb;

  return 0;
}

int
fx_on_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb) {
  platform->on_terminate = cb;

  return 0;
}

int
fx_on_platform_suspend (fx_platform_t *platform, fx_suspend_cb cb) {
  return 0;
}

int
fx_on_platform_resume (fx_platform_t *platform, fx_resume_cb cb) {
  return 0;
}

int
fx_platform_run (fx_platform_t *platform) {
  return 0;
}

int
fx_platform_terminate (fx_platform_t *platform) {
  return 0;
}

int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  return 0;
}

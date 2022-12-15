#ifndef FX_PLATFORM_H
#define FX_PLATFORM_H

#include "../../include/fx.h"
#include "fx.h"

typedef struct fx_platform_s fx_platform_t;

int
fx_platform_init (fx_t *app, fx_platform_t **result);

int
fx_platform_destroy (fx_platform_t *platform);

int
fx_platform_run (fx_platform_t *platform, fx_launch_cb cb);

int
fx_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb);

#endif // FX_PLATFORM_H
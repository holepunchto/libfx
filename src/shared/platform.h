#ifndef FX_PLATFORM_H
#define FX_PLATFORM_H

#include "../../include/fx.h"

typedef struct fx_platform_s fx_platform_t;

int
fx_platform_init (fx_t *app, fx_platform_t **result);

int
fx_platform_destroy (fx_platform_t *platform);

int
fx_on_platform_launch (fx_platform_t *platform, fx_launch_cb cb);

int
fx_on_platform_terminate (fx_platform_t *platform, fx_terminate_cb cb);

int
fx_on_platform_suspend (fx_platform_t *platform, fx_suspend_cb cb);

int
fx_on_platform_resume (fx_platform_t *platform, fx_resume_cb cb);

int
fx_platform_run (fx_platform_t *platform);

int
fx_platform_terminate (fx_platform_t *platform);

#endif // FX_PLATFORM_H

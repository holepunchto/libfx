#ifndef FX_PLATFORM_H
#define FX_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../include/fx.h"

typedef struct fx_platform_s fx_platform_t;

int
fx_platform_init (fx_t *app, fx_platform_t **result);

int
fx_platform_destroy (fx_platform_t *platform);

#ifdef __cplusplus
}
#endif

#endif // FX_PLATFORM_H

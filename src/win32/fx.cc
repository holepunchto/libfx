#include "../../include/fx.h"

#include "../shared/fx.h"
#include "platform.h"
#include "winui.h"

extern "C" int
fx_run (fx_t *app, fx_launch_cb on_launch, fx_terminate_cb on_terminate) {
  app->platform->on_launch = on_launch;
  app->platform->on_terminate = on_terminate;

  Application::Start([=] (auto &&) { make<FX>(app->platform); });

  return 0;
}

extern "C" int
fx_dispatch (fx_dispatch_cb cb, void *data) {
  assert(fx_dispatcher);

  auto success = fx_dispatcher->TryEnqueue([=] () { cb(fx_main_app, data); });

  return success ? 0 : -1;
}

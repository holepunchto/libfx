#ifndef FX_LINUX_WINDOW_H
#define FX_LINUX_WINDOW_H

#include "../../include/fx.h"

#include <gtk/gtk.h>

struct fx_window_s {
  GtkWindow *handle;

  fx_view_t *view;

  void *data;

  fx_window_resize_cb on_resize;
  fx_window_move_cb on_move;
  fx_window_minimize_cb on_minimize;
  fx_window_deminimize_cb on_deminimize;
  fx_window_close_cb on_close;
};

#endif // FX_LINUX_WINDOW_H

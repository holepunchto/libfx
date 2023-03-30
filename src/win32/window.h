#include "../../include/fx.h"

struct fx_window_s {
  HWND handle;

  void *data;

  fx_window_resize_cb on_resize;
  fx_window_move_cb on_move;
  fx_window_minimize_cb on_minimize;
  fx_window_deminimize_cb on_deminimize;
  fx_window_close_cb on_close;
};
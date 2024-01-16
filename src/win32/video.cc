#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "video.h"

static uv_once_t fx_video_class_init = UV_ONCE_INIT;

static ATOM fx_video_class;

static LRESULT CALLBACK
on_video_message (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto video = reinterpret_cast<fx_video_t *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

  auto res = DefWindowProc(hwnd, uMsg, wParam, lParam);

  return res;
}

static void
on_video_class_init () {
  auto instance = GetModuleHandle(NULL);

  WNDCLASSEX video_class;

  ZeroMemory(&video_class, sizeof(WNDCLASSEX));

  video_class.cbSize = sizeof(WNDCLASSEX);
  video_class.lpfnWndProc = on_video_message;
  video_class.hInstance = instance;
  video_class.lpszClassName = "FX Video";

  fx_video_class = RegisterClassEx(&video_class);

  assert(fx_video_class);
}

extern "C" int
fx_video_init (fx_t *app, const char *url, size_t len, float x, float y, float width, float height, int flags, fx_video_t **result) {
  uv_once(&fx_video_class_init, on_video_class_init);

  auto instance = GetModuleHandle(NULL);

  auto handle = CreateWindowEx(
    0,
    MAKEINTATOM(fx_video_class),
    NULL,
    WS_VISIBLE | WS_CHILD,
    int(x),
    int(y),
    int(width),
    int(height),
    HWND_MESSAGE,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  auto video = new fx_video_t();

  video->node.type = fx_video_node;

  video->handle = handle;

  *result = video;

  SetWindowLongPtr(handle, GWLP_USERDATA, LONG_PTR(video));

  return 0;
}

extern "C" int
fx_video_destroy (fx_video_t *video) {
  delete video;

  return 0;
}

extern "C" int
fx_get_video_data (fx_video_t *video, void **result) {
  *result = video->data;

  return 0;
}

extern "C" int
fx_set_video_data (fx_video_t *video, void *data) {
  video->data = data;

  return 0;
}

extern "C" int
fx_get_video_bounds (fx_video_t *video, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_video_bounds (fx_video_t *video, float x, float y, float width, float height) {
  return 0;
}

bool
fx_is_video_loop (fx_video_t *video) {
  return false;
}

bool
fx_set_video_loop (fx_video_t *video, bool loop) {
  return 0;
}

extern "C" int
fx_play_video (fx_video_t *video) {
  return 0;
}

extern "C" int
fx_pause_video (fx_video_t *video) {
  return 0;
}

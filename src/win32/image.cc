#include <assert.h>
#include <uv.h>

#include "../../include/fx.h"
#include "image.h"

static uv_once_t fx_image_class_init = UV_ONCE_INIT;

static ATOM fx_image_class;

static LRESULT CALLBACK
on_image_message (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto image = reinterpret_cast<fx_image_t *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

  switch (uMsg) {
  case WM_PAINT: {
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(hwnd, &ps);

    if (image->bitmap) {
      HDC hdc_compatible = CreateCompatibleDC(hdc);

      SelectObject(hdc_compatible, image->bitmap);

      BITMAP bitmap;

      auto success = GetObject(image->bitmap, sizeof(BITMAP), &bitmap);

      if (success) {
        BitBlt(
          hdc,
          0,
          0,
          bitmap.bmWidth,
          bitmap.bmHeight,
          hdc_compatible,
          0,
          0,
          SRCCOPY
        );
      }

      DeleteDC(hdc_compatible);
    }

    EndPaint(hwnd, &ps);

    return 0;
  }
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

static void
on_image_class_init () {
  auto instance = GetModuleHandle(NULL);

  WNDCLASSEX image_class;

  ZeroMemory(&image_class, sizeof(WNDCLASSEX));

  image_class.cbSize = sizeof(WNDCLASSEX);
  image_class.lpfnWndProc = on_image_message;
  image_class.hInstance = instance;
  image_class.lpszClassName = "FX Image";

  fx_image_class = RegisterClassEx(&image_class);

  assert(fx_image_class);
}

extern "C" int
fx_image_init (fx_t *app, float x, float y, float width, float height, fx_image_t **result) {
  uv_once(&fx_image_class_init, on_image_class_init);

  auto instance = GetModuleHandle(NULL);

  auto handle = CreateWindowEx(
    0,
    MAKEINTATOM(fx_image_class),
    NULL,
    WS_VISIBLE | WS_CHILD,
    (int) x,
    (int) y,
    (int) width,
    (int) height,
    HWND_MESSAGE,
    NULL,
    instance,
    NULL
  );

  if (handle == NULL) return -1;

  auto image = new fx_image_t();

  image->node.type = fx_image_node;

  image->handle = handle;

  image->bitmap = NULL;

  *result = image;

  SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR) image);

  return 0;
}

extern "C" int
fx_image_destroy (fx_image_t *image) {
  DestroyWindow(image->handle);

  if (image->bitmap) DeleteObject(image->bitmap);

  delete image;

  return 0;
}

int
fx_image_load (fx_image_t *image, const uint8_t *pixels, int width, int height, int stride) {
  if (stride == -1) stride = width * 4;

  auto hdc_window = GetDC(image->handle);

  auto hdc = CreateCompatibleDC(hdc_window);

  BITMAPINFO bmi;

  ZeroMemory(&bmi, sizeof(BITMAPINFO));

  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = -height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  uint8_t *data;

  auto bitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&data), NULL, 0);

  if (bitmap == NULL) goto err;

  image->bitmap = bitmap;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width * 4; x += 4) {
      union {
        uint32_t u32;
        uint8_t u8[4];
      } pixel;

      pixel.u32 = (pixels[x + 3] << 24) | (pixels[x] << 16) | (pixels[x + 1] << 8) | pixels[x + 2];

      data[x] = pixel.u8[0];
      data[x + 1] = pixel.u8[1];
      data[x + 2] = pixel.u8[2];
      data[x + 3] = pixel.u8[3];
    }

    pixels += stride;
    data += width * 4;
  }

  DeleteDC(hdc);

  ReleaseDC(image->handle, hdc_window);

  return 0;

err:
  DeleteDC(hdc);

  ReleaseDC(image->handle, hdc_window);

  return -1;
}

extern "C" int
fx_get_image_data (fx_image_t *image, void **result) {
  *result = image->data;

  return 0;
}

extern "C" int
fx_set_image_data (fx_image_t *image, void *data) {
  image->data = data;

  return 0;
}

extern "C" int
fx_get_image_bounds (fx_image_t *image, float *x, float *y, float *width, float *height) {
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

  return 0;
}

extern "C" int
fx_set_image_bounds (fx_image_t *image, float x, float y, float width, float height) {
  return 0;
}

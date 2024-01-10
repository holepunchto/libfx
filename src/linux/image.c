#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "image.h"

int
fx_image_init (fx_t *app, float x, float y, float width, float height, fx_image_t **result) {
  GtkWidget *handle = gtk_picture_new();

  if (handle == NULL) return -1;

  fx_image_t *image = malloc(sizeof(fx_image_t));

  image->node.type = fx_image_node;

  image->handle = GTK_PICTURE(handle);

  image->parent = NULL;

  image->bounds.x = x;
  image->bounds.y = y;
  image->bounds.width = width;
  image->bounds.height = height;

  *result = image;

  gtk_widget_set_visible(handle, true);

  gtk_widget_set_size_request(handle, width, height);

  return 0;
}

int
fx_image_destroy (fx_image_t *image) {
  free(image);

  return 0;
}

int
fx_image_load (fx_image_t *image, const uint8_t *pixels, int width, int height, int stride) {
  if (stride == -1) stride = width * 4;

  GdkPixbuf *buffer = gdk_pixbuf_new_from_data(
    pixels,
    GDK_COLORSPACE_RGB,
    true,
    8,
    width,
    height,
    stride,
    NULL,
    NULL
  );

  GdkTexture *texture = gdk_texture_new_for_pixbuf(buffer);

  g_object_unref(buffer);

  gtk_picture_set_paintable(image->handle, GDK_PAINTABLE(texture));

  g_object_unref(texture);

  return 0;
}

int
fx_get_image_data (fx_image_t *image, void **result) {
  *result = image->data;

  return 0;
}

int
fx_set_image_data (fx_image_t *image, void *data) {
  image->data = data;

  return 0;
}

int
fx_get_image_bounds (fx_image_t *image, float *x, float *y, float *width, float *height) {
  if (x) *x = image->bounds.x;
  if (y) *y = image->bounds.y;
  if (width) *width = image->bounds.width;
  if (height) *height = image->bounds.height;

  return 0;
}

int
fx_set_image_bounds (fx_image_t *image, float x, float y, float width, float height) {
  image->bounds.x = x;
  image->bounds.y = y;
  image->bounds.width = width;
  image->bounds.height = height;

  return 0;
}

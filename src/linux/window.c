#include "window.h"

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "platform.h"
#include "view.h"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

static const char *fx_default_window_title = "";

static void
on_close (GtkWindow *self, void *data) {
  fx_window_t *window = (fx_window_t *) data;

  if (window->on_close) window->on_close(window);
}

static void
on_resize (GObject *object, GParamSpec *params, void *data) {
  fx_window_t *window = (fx_window_t *) data;

  int width, height;

  gtk_window_get_default_size(window->handle, &width, &height);

  window->bounds.width = (float) width;
  window->bounds.height = (float) height;

  if (window->on_resize) window->on_resize(window);
}

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, int flags, fx_window_t **result) {
  GtkWidget *handle = gtk_window_new();

  if (handle == NULL) return -1;

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->handle = GTK_WINDOW(handle);

  window->view = view;

  window->data = NULL;

  window->bounds.x = 0;
  window->bounds.y = 0;
  window->bounds.width = width;
  window->bounds.height = height;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  *result = window;

  gtk_window_set_title(window->handle, fx_default_window_title);

  gtk_window_set_default_size(window->handle, width, height);

  if (flags & fx_window_no_frame) {
    GtkWidget *title = gtk_center_box_new();

    gtk_window_set_titlebar(window->handle, title);

    gtk_window_set_resizable(window->handle, false);
  }

  g_signal_connect(G_OBJECT(handle), "close-request", G_CALLBACK(on_close), window);

  g_signal_connect(G_OBJECT(handle), "notify::default-width", G_CALLBACK(on_resize), window);

  g_signal_connect(G_OBJECT(handle), "notify::default-height", G_CALLBACK(on_resize), window);

  gtk_application_add_window(app->platform->app, window->handle);

  if (view) gtk_window_set_child(window->handle, GTK_WIDGET(view->handle));

  return 0;
}

int
fx_window_destroy (fx_window_t *window) {
  gtk_window_destroy(window->handle);

  free(window);

  return 0;
}

int
fx_on_window_resize (fx_window_t *window, fx_window_resize_cb cb) {
  window->on_resize = cb;

  return 0;
}

int
fx_on_window_move (fx_window_t *window, fx_window_move_cb cb) {
  window->on_move = cb;

  return 0;
}

int
fx_on_window_minimize (fx_window_t *window, fx_window_minimize_cb cb) {
  window->on_minimize = cb;

  return 0;
}

int
fx_on_window_deminimize (fx_window_t *window, fx_window_deminimize_cb cb) {
  window->on_deminimize = cb;

  return 0;
}

int
fx_on_window_close (fx_window_t *window, fx_window_close_cb cb) {
  window->on_close = cb;

  return 0;
}

int
fx_get_window_data (fx_window_t *window, void **result) {
  *result = window->data;

  return 0;
}

int
fx_set_window_data (fx_window_t *window, void *data) {
  window->data = data;

  return 0;
}

int
fx_get_window_bounds (fx_window_t *window, float *x, float *y, float *width, float *height) {
  if (x) *x = window->bounds.x;
  if (y) *y = window->bounds.y;
  if (width) *width = window->bounds.width;
  if (height) *height = window->bounds.height;

  return 0;
}

int
fx_get_window_title (fx_window_t *window, char *title, size_t len, size_t *result) {
  const char *bytes = gtk_window_get_title(window->handle);

  if (title == NULL) {
    *result = strlen(bytes);
  } else if (len != 0) {
    size_t bytes_len = strlen(bytes);

    size_t written = len < bytes_len ? len : bytes_len;

    strncpy(title, bytes, written);

    if (written < len) title[written] = '\0';

    if (result) *result = written;
  } else if (result) *result = 0;

  return 0;
}

int
fx_set_window_title (fx_window_t *window, const char *title, size_t len) {
  gtk_window_set_title(window->handle, title);

  return 0;
}

bool
fx_is_window_visible (fx_window_t *window) {
  return gtk_widget_get_visible(GTK_WIDGET(window->handle));
}

int
fx_set_window_visible (fx_window_t *window, bool visible) {
  gtk_widget_set_visible(GTK_WIDGET(window->handle), visible);

  return 0;
}

bool
fx_is_window_resizable (fx_window_t *window) {
  return gtk_window_get_resizable(window->handle);
}

int
fx_set_window_resizable (fx_window_t *window, bool resizable) {
  gtk_window_set_resizable(window->handle, resizable);

  return 0;
}

int
fx_activate_window (fx_window_t *window) {
  return fx_show_window(window);
}

int
fx_close_window (fx_window_t *window) {
  gtk_window_close(window->handle);

  return 0;
}

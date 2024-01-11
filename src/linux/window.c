#include <gtk/gtk.h>
#include <stdlib.h>

#include "../../include/fx.h"
#include "../shared/fx.h"
#include "fx.h"
#include "view.h"
#include "window.h"

static void
on_resize (GObject *object, GParamSpec *params, void *data) {
  fx_window_t *window = (fx_window_t *) data;

  if (window->on_resize) window->on_resize(window);
}

int
fx_window_init (fx_t *app, fx_view_t *view, float x, float y, float width, float height, fx_window_t **result) {
  GtkWidget *handle = gtk_window_new();

  if (handle == NULL) return -1;

  fx_window_t *window = malloc(sizeof(fx_window_t));

  window->handle = GTK_WINDOW(handle);

  window->view = view;

  window->data = NULL;

  window->on_resize = NULL;
  window->on_move = NULL;
  window->on_minimize = NULL;
  window->on_deminimize = NULL;
  window->on_close = NULL;

  *result = window;

  gtk_application_add_window(app->platform->app, window->handle);

  g_signal_connect(G_OBJECT(handle), "notify::default-width", G_CALLBACK(on_resize), window);

  g_signal_connect(G_OBJECT(handle), "notify::default-height", G_CALLBACK(on_resize), window);

  if (view) {
    gtk_window_set_child(window->handle, GTK_WIDGET(view->handle));
  }

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
  if (x) *x = 0;
  if (y) *y = 0;
  if (width) *width = 0;
  if (height) *height = 0;

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

extern int
fx_show_window (fx_window_t *window);

extern int
fx_hide_window (fx_window_t *window);

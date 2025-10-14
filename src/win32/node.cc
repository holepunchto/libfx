#include "../../include/fx.h"
#include "image.h"
#include "scroll-view.h"
#include "text-input.h"
#include "text.h"
#include "video.h"
#include "view.h"
#include "web-view.h"
#include "winui.h"

static inline UIElement
fx_get_child_element(fx_node_t *child, float *x, float *y) {
  switch (child->type) {
  case fx_view_node: {
    auto view = reinterpret_cast<fx_view_t *>(child);

    *x = view->bounds.x;
    *y = view->bounds.y;

    return view->handle;
  }

  case fx_scroll_view_node: {
    auto scroll_view = reinterpret_cast<fx_scroll_view_t *>(child);

    *x = scroll_view->bounds.x;
    *y = scroll_view->bounds.y;

    return scroll_view->handle;
  }

  case fx_text_node: {
    auto text = reinterpret_cast<fx_text_t *>(child);

    *x = text->bounds.x;
    *y = text->bounds.y;

    return text->handle;
  }

  case fx_text_input_node: {
    auto text_input = reinterpret_cast<fx_text_input_t *>(child);

    *x = text_input->bounds.x;
    *y = text_input->bounds.y;

    return text_input->handle;
  }

  case fx_image_node: {
    auto image = reinterpret_cast<fx_image_t *>(child);

    *x = image->bounds.x;
    *y = image->bounds.y;

    return image->handle;
  }

  case fx_video_node: {
    auto video = reinterpret_cast<fx_video_t *>(child);

    *x = video->bounds.x;
    *y = video->bounds.y;

    return video->handle;
  }

  case fx_web_view_node: {
    auto web_view = reinterpret_cast<fx_web_view_t *>(child);

    *x = web_view->bounds.x;
    *y = web_view->bounds.y;

    return web_view->handle;
  }
  }

  return nullptr;
}

extern "C" int
fx_set_child(fx_node_t *parent, fx_node_t *child, size_t index) {
  float x, y;

  auto child_element = fx_get_child_element(child, &x, &y);

  switch (parent->type) {
  case fx_view_node: {
    auto view = reinterpret_cast<fx_view_t *>(parent);

    view->handle.Children().Append(child_element);

    view->handle.SetLeft(child_element, x);
    view->handle.SetTop(child_element, y);
    break;
  }

  default:
    return -1;
  }

  return 0;
}

extern "C" int
fx_unset_child(fx_node_t *parent, fx_node_t *child, size_t index) {
  switch (parent->type) {
  case fx_view_node: {
    auto view = reinterpret_cast<fx_view_t *>(parent);

    view->handle.Children().RemoveAt(uint32_t(index));
    break;
  }

  default:
    return -1;
  }

  return 0;
}

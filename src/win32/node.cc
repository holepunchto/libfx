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
fx_get_child_element (fx_node_t *child) {
  switch (child->type) {
  case fx_view_node:
    return reinterpret_cast<fx_view_t *>(child)->handle;
  case fx_scroll_view_node:
    // child_element = &((fx_scroll_view_t *) child)->handle;
    break;
  case fx_text_node:
    return reinterpret_cast<fx_text_t *>(child)->handle;
  case fx_text_input_node:
    // child_element = &((fx_text_input_t *) child)->handle;
    break;
  case fx_image_node:
    // child_element = &((fx_image_t *) child)->handle;
    break;
  case fx_video_node:
    // child_element = &((fx_video_t *) child)->handle;
    break;
  case fx_web_view_node:
    // child_element = &((fx_web_view_t *) child)->handle;
    break;
  }

  return nullptr;
}

extern "C" int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  auto child_element = fx_get_child_element(child);

  switch (parent->type) {
  case fx_view_node:
    reinterpret_cast<fx_view_t *>(parent)->handle.Children().InsertAt(uint32_t(index), child_element);
    break;
  default:
    return -1;
  }

  return 0;
}

extern "C" int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index) {
  switch (parent->type) {
  case fx_view_node:
    reinterpret_cast<fx_view_t *>(parent)->handle.Children().RemoveAt(uint32_t(index));
    break;
  default:
    return -1;
  }

  return 0;
}

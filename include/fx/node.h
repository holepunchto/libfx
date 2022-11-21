#ifndef FX_NODE_H
#define FX_NODE_H

#include <stddef.h>

#include "../fx.h"

typedef struct fx_node_s fx_node_t;

typedef enum {
  fx_view_node,
  fx_text_node,
  fx_text_input_node,
  fx_image_node,
  fx_video_node,
  fx_web_view_node,
} fx_node_type_t;

struct fx_node_s {
  fx_node_type_t type;
};

int
fx_set_child (fx_node_t *parent, fx_node_t *child, size_t index);

int
fx_unset_child (fx_node_t *parent, fx_node_t *child, size_t index);

#endif // FX_NODE_H

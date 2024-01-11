#import <stdint.h>

#import <AppKit/AppKit.h>

#import "../../include/fx.h"

@interface FXText : NSTextView

@property(assign) fx_text_t *fxText;

@end

struct fx_text_s {
  fx_node_t node;

  __unsafe_unretained FXText *handle;

  void *data;
};

struct fx_text_span_s {
  uint32_t start;
  uint32_t end;
};

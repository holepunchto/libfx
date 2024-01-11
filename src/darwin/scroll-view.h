#import <AppKit/AppKit.h>

#import "../../include/fx.h"

@interface FXScrollView : NSScrollView

@property(assign) fx_scroll_view_t *fxScrollView;

@end

struct fx_scroll_view_s {
  fx_node_t node;

  FXScrollView *handle;

  void *data;
};

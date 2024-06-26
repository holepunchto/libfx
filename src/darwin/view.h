#import "../../include/fx.h"

#import <AppKit/AppKit.h>

@interface FXView : NSView

@property(assign) fx_view_t *fxView;

@end

struct fx_view_s {
  fx_node_t node;

  __unsafe_unretained FXView *handle;

  void *data;
};

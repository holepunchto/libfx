#import "../../include/fx.h"

#import <UIKit/UIKit.h>

@interface FXScrollView : UIScrollView

@property(assign) fx_scroll_view_t *fxScrollView;

@end

struct fx_scroll_view_s {
  fx_node_t node;

  FXScrollView *native_scroll_view;

  void *data;
};

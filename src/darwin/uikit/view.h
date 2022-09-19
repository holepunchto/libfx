#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXView : UIView

@property(assign) fx_view_t *fxView;

@end

struct fx_view_s {
  fx_node_t node;

  FXView *native_view;
};

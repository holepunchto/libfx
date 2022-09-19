#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXText : UITextField

@property(assign) fx_text_t *fxText;

@end

struct fx_text_s {
  fx_node_t node;

  FXText *native_text;
};

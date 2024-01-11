#import <AppKit/AppKit.h>

#import "../../include/fx.h"

@interface FXTextInputDelegate : NSObject <NSTextFieldDelegate>

@end

@interface FXTextInput : NSTextField

@property(assign) fx_text_input_t *fxTextInput;

@end

struct fx_text_input_s {
  fx_node_t node;

  FXTextInput *handle;

  void *data;

  fx_text_input_change_cb on_change;
};

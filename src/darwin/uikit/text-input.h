#import <UIKit/UIKit.h>

#import "../../../include/fx.h"

@interface FXTextFieldDelegate : UIResponder <UITextFieldDelegate>

@end

@interface FXTextField : UITextField

@property(assign) fx_text_input_t *fxTextInput;

@end

struct fx_text_input_s {
  fx_node_t node;

  FXTextField *native_text_input;

  fx_text_input_change_cb on_change;
};

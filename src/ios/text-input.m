#import "text-input.h"

#import "../../include/fx.h"

#import <UIKit/UIKit.h>

@implementation FXTextFieldDelegate

- (instancetype)init {
  if (self = [super init]) {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(textDidChange)
                                                 name:UITextFieldTextDidChangeNotification
                                               object:self];
  }

  return self;
}

- (void)textDidChange:(NSNotification *)notification {
  fx_text_input_t *text_input = ((FXTextField *) notification.object).fxTextInput;

  if (text_input->on_change != NULL) {
    text_input->on_change(text_input);
  }
}

@end

@implementation FXTextField : UITextField

@end

int
fx_text_input_init(fx_t *app, float x, float y, float width, float height, fx_text_input_t **result) {
  FXTextField *native_text_input = [[FXTextField alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_text_input.delegate = [[FXTextFieldDelegate alloc] init];

  fx_text_input_t *text_input = malloc(sizeof(fx_text_input_t));

  text_input->node.type = fx_text_input_node;

  text_input->native_text_input = native_text_input;

  native_text_input.fxTextInput = text_input;

  *result = text_input;

  return 0;
}

int
fx_on_text_input_change(fx_text_input_t *text_input, fx_text_input_change_cb cb) {
  text_input->on_change = cb;

  return 0;
}

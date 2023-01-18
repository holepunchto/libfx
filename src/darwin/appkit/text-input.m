#import <stdbool.h>
#import <string.h>

#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "text-input.h"

@implementation FXTextInputDelegate

- (void)textDidChange:(NSNotification *)notification {
  fx_text_input_t *text_input = ((FXTextInput *) notification.object).fxTextInput;

  if (text_input->on_change != NULL) {
    text_input->on_change(text_input);
  }
}

@end

@implementation FXTextInput

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_text_input_init (fx_t *app, float x, float y, float width, float height, fx_text_input_t **result) {
  FXTextInput *native_text_input = [[FXTextInput alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_text_input.delegate = [[FXTextInputDelegate alloc] init];

  fx_text_input_t *text_input = malloc(sizeof(fx_text_input_t));

  text_input->node.type = fx_text_input_node;

  text_input->native_text_input = native_text_input;

  native_text_input.fxTextInput = text_input;

  *result = text_input;

  return 0;
}

int
fx_text_input_destroy (fx_text_input_t *text_input) {
  [text_input->native_text_input release];

  free(text_input);

  return 0;
}

int
fx_on_text_input_change (fx_text_input_t *text_input, fx_text_input_change_cb cb) {
  text_input->on_change = cb;

  return 0;
}

int
fx_get_text_input_data (fx_text_input_t *text_input, void **result) {
  *result = text_input->data;

  return 0;
}

int
fx_set_text_input_data (fx_text_input_t *text_input, void *data) {
  text_input->data = data;

  return 0;
}

int
fx_get_text_input_bounds (fx_text_input_t *text_input, float *x, float *y, float *width, float *height) {
  NSRect frame = text_input->native_text_input.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_set_text_input_bounds (fx_text_input_t *text_input, float x, float y, float width, float height) {
  text_input->native_text_input.frame = CGRectMake(x, y, width, height);

  return 0;
}

char *
fx_get_text_input_value (fx_text_input_t *text_input) {
  const char *value = [text_input->native_text_input.stringValue cStringUsingEncoding:NSUTF8StringEncoding];

  return strdup(value);
}

int
fx_set_text_input_value (fx_text_input_t *text_input, const char *value, size_t len) {
  [text_input->native_text_input setStringValue:[[NSString alloc] initWithBytes:value length:len encoding:NSUTF8StringEncoding]];

  return 0;
}

bool
fx_is_text_input_enabled (fx_text_input_t *text_input) {
  return text_input->native_text_input.enabled;
}

int
fx_set_text_input_enabled (fx_text_input_t *text_input, bool enabled) {
  text_input->native_text_input.enabled = enabled;

  return 0;
}

bool
fx_is_text_input_selectable (fx_text_input_t *text_input) {
  return text_input->native_text_input.selectable;
}

int
fx_set_text_input_selectable (fx_text_input_t *text_input, bool selectable) {
  text_input->native_text_input.selectable = selectable;

  return 0;
}

bool
fx_is_text_input_editable (fx_text_input_t *text_input) {
  return text_input->native_text_input.editable;
}

int
fx_set_text_input_editable (fx_text_input_t *text_input, bool editable) {
  text_input->native_text_input.editable = editable;

  return 0;
}

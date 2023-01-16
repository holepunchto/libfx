#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "text.h"

@implementation FXText

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_text_init (fx_t *app, double x, double y, double width, double height, fx_text_t **result) {
  FXText *native_text = [[FXText alloc] initWithFrame:CGRectMake(x, y, width, height)];

  [native_text setBezeled:NO];
  [native_text setDrawsBackground:NO];
  [native_text setEditable:NO];

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->native_text = native_text;

  text->value = [[NSMutableAttributedString alloc] init];

  native_text.fxText = text;

  *result = text;

  return 0;
}

int
fx_get_text_data (fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

int
fx_set_text_data (fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

int
fx_append_text_span (fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  NSUInteger start = [text->value length];
  NSUInteger end = start + len;

  [text->value appendAttributedString:[[NSAttributedString alloc] initWithString:[[NSString alloc] initWithBytes:value length:len encoding:NSUTF8StringEncoding]]];

  [text->native_text setAttributedStringValue:text->value];

  if (result) {
    fx_text_span_t *span = malloc(sizeof(fx_text_span_t));

    span->start = start;
    span->end = end;

    *result = span;
  }

  return 0;
}

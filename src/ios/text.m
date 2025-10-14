#import "text.h"

#import "../../include/fx.h"

#import <UIKit/UIKit.h>
#import <math.h>

@implementation FXText

@end

int
fx_text_init(fx_t *app, float x, float y, float width, float height, fx_text_t **result) {
  if (isnan(width)) width = INFINITY;
  if (isnan(height)) height = INFINITY;

  FXText *native_text = [[FXText alloc] initWithFrame:CGRectMake(x, y, width, height)];

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->native_text = native_text;

  native_text.fxText = text;

  *result = text;

  return 0;
}

int
fx_text_destroy(fx_text_t *text) {
  [text->native_text release];

  free(text);

  return 0;
}

int
fx_get_text_data(fx_text_t *text, void **result) {
  *result = text->data;

  return 0;
}

int
fx_set_text_data(fx_text_t *text, void *data) {
  text->data = data;

  return 0;
}

int
fx_get_text_bounds(fx_text_t *text, float *x, float *y, float *width, float *height) {
  CGRect frame = text->native_text.frame;

  if (x) *x = frame.origin.x;
  if (y) *y = frame.origin.y;
  if (width) *width = frame.size.width;
  if (height) *height = frame.size.height;

  return 0;
}

int
fx_get_text_bounds_used(fx_text_t *text, float *x, float *y, float *width, float *height) {
  NSLayoutManager *layout = [text->native_text layoutManager];
  NSTextContainer *container = [text->native_text textContainer];

  [layout ensureLayoutForTextContainer:container];

  CGRect bounds = [layout usedRectForTextContainer:container];

  if (x) *x = bounds.origin.x;
  if (y) *y = bounds.origin.y;
  if (width) *width = bounds.size.width;
  if (height) *height = bounds.size.height;

  return 0;
}

int
fx_set_text_bounds(fx_text_t *text, float x, float y, float width, float height) {
  text->native_text.frame = CGRectMake(x, y, width, height);

  return 0;
}

int
fx_append_text_span(fx_text_t *text, const char *value, size_t len, fx_text_span_t **result) {
  NSUInteger start = [text->native_text.textStorage length];
  NSUInteger end = start + len;

  [text->native_text.textStorage appendAttributedString:[[NSAttributedString alloc] initWithString:[[NSString alloc] initWithBytes:value length:len encoding:NSUTF8StringEncoding]]];

  if (result) {
    fx_text_span_t *span = malloc(sizeof(fx_text_span_t));

    span->start = start;
    span->end = end;

    *result = span;
  }

  return 0;
}

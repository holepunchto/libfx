#import <AppKit/AppKit.h>

#import "../../../include/fx.h"
#import "text.h"

@implementation FXText

- (BOOL)isFlipped {
  return YES;
}

@end

int
fx_text_init (fx_t *app, const char *value, size_t len, double x, double y, double width, double height, fx_text_t **result) {
  FXText *native_text = [[FXText alloc] initWithFrame:CGRectMake(x, y, width, height)];

  [native_text setStringValue:[[NSString alloc] initWithBytes:value length:len encoding:NSUTF8StringEncoding]];

  [native_text setBezeled:NO];
  [native_text setDrawsBackground:NO];
  [native_text setEditable:NO];

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->native_text = native_text;

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

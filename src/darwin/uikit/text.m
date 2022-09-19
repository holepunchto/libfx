#import <UIKit/UIKit.h>

#import "../../../include/fx.h"
#import "text.h"

@implementation FXText

@end

int
fx_text_init (fx_t *app, const char *value, size_t len, double x, double y, double width, double height, fx_text_t **result) {
  FXText *native_text = [[FXText alloc] initWithFrame:CGRectMake(x, y, width, height)];

  native_text.text = [[NSString alloc] initWithBytes:value length:len encoding:NSUTF8StringEncoding];

  fx_text_t *text = malloc(sizeof(fx_text_t));

  text->node.type = fx_text_node;

  text->native_text = native_text;

  *result = text;

  return 0;
}

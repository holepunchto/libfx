#import <Foundation/Foundation.h>
#import <string.h>

static inline NSString *
fx__string (const char *str, size_t len) {
  if (len == (size_t) -1) len = strlen(str);

  return [[NSString alloc] initWithBytes:str length:len encoding:NSUTF8StringEncoding];
}

static inline NSURL *
fx__url (const char *url, size_t len) {
  return [[NSURL alloc] initWithString:fx__string(url, len) relativeToURL:[[NSURL alloc] initFileURLWithPath:[[NSFileManager defaultManager] currentDirectoryPath] isDirectory:YES]];
}

static inline NSURL *
fx__url_with_base (const char *url, size_t len, const char *base, size_t base_len) {
  return [[NSURL alloc] initWithString:fx__string(url, len) relativeToURL:fx__url(base, base_len)];
}

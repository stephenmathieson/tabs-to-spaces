
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/tabs-to-spaces.h"

#define equal(a, b) ({                                \
  if (0 != strcmp(a, b)) {                            \
    fprintf(stderr                                    \
      , "Assertion error: \"%s\" == \"%s\" (%s:%d)\n" \
      , a                                             \
      , b                                             \
      , __FILE__                                      \
      , __LINE__);                                    \
    exit(1);                                          \
  }                                                   \
});

int
main(void) {
  equal("hello world",      tabs_to_spaces("hello\tworld", 1));
  equal("hello  world",     tabs_to_spaces("hello\tworld", 2));
  equal("  hello world",    tabs_to_spaces("\thello world", 2));
  equal("  hello  world  ", tabs_to_spaces("\thello\tworld\t", 2));
  equal("hello world  ",    tabs_to_spaces("hello world\t", 2));
  equal("          ",       tabs_to_spaces("\t", 10));
  return 0;
}

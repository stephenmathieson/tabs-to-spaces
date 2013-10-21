
#include <string.h>
#include <assert.h>
#include "src/tabs-to-spaces.h"

int main(int argc, char **argv) {
  assert(0 == strcmp("hello world", tabs_to_spaces("hello\tworld", 1)));
  assert(0 == strcmp("hello  world", tabs_to_spaces("hello\tworld", 2)));
  assert(0 == strcmp("  hello world", tabs_to_spaces("\thello world", 2)));
  assert(0 == strcmp("  hello  world  ", tabs_to_spaces("\thello\tworld\t", 2)));
  assert(0 == strcmp("hello world  ", tabs_to_spaces("hello world\t", 2)));
  assert(0 == strcmp("          ", tabs_to_spaces("\t", 10)));
  return 0;
}

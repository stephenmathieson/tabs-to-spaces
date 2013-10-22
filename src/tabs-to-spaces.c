
//
// tabs-to-spaces.c
//
// Copyright (c) 2013 Stephen Mathieson
// MIT licensed
//

#include <stdlib.h>
#include "str-replace.h"
#include "tabs-to-spaces.h"

char *tabs_to_spaces(char *str, int count) {
  char *spaces = (char *) malloc((sizeof(char) * count) + 1);
  if (NULL == spaces) return NULL;
  for (int i = 0; i < count; i++) {
    spaces[i] = ' ';
  }
  char *result = str_replace(str, "\t", spaces);
  free(spaces);
  return result;
}



//
// main.c
//
// Copyright (c) 2013 Stephen Mathieson
// MIT licensed
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "commander.h"
#include "tabs-to-spaces.h"

// global options
struct options {
  bool verbose;
  int spaces;
};

static struct options opts;

/*
 * Activate verbose output
 */

static void set_verbose(command_t *self) {
  opts.verbose = true;
}

/*
 * Set number of spaces
 */

static void set_spaces(command_t *self) {
  opts.spaces = atoi(self->arg);
}

/*
 * Convert the file at `path` to spaces
 */

static int convert_file(char *path) {
  if (opts.verbose) printf("converting %s\n", path);

  FILE *fp = fopen(path, "r");
  if (!fp) return -1;

  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  rewind(fp);

  char *data = (char *) malloc(size + 1);
  if (NULL == data) return -1;

  if (1 != fread(data, size, 1, fp)) {
    fclose(fp);
    free(data);
    return -1;
  }

  char *spaces = tabs_to_spaces(data, opts.spaces);
  if (NULL == spaces) return -1;

  fclose(fp);
  free(data);

  fp = fopen(path, "w");
  if (!fp) return -1;

  size_t len = strlen(spaces);
  if (len != fwrite(spaces, 1, len, fp)) {
    return -1;
  }

  fclose(fp);
  free(spaces);

  return 0;
}

/*
 * Entry point
 */

int main(int argc, char **argv){
  opts.spaces = 2;
  command_t cmd;
  command_init(&cmd, argv[0], "0.0.1");
  command_option(&cmd, "-v", "--verbose", "enable verbose stuff", set_verbose);
  command_option(&cmd, "-s", "--spaces [count]", "optional number of spaces (defaults to 2)", set_spaces);
  command_parse(&cmd, argc, argv);

  for (int i = 0; i < cmd.argc; ++i) {
    char *file = cmd.argv[i];
    if (-1 == convert_file(file)) {
      return -1;
    }
  }

  command_free(&cmd);

  return 0;
}

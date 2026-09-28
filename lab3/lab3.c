#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Please enter some text: ");

  char *line = NULL;
  size_t len = 0;

  if (getline(&line, &len, stdin) != -1) {

  free(line);
  return 0;
}

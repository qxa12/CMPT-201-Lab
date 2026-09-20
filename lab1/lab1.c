#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Please enter some text: ");

  char *line = NULL;
  size_t len = 0;

  if (getline(&line, &len, stdin) != -1) {
    char *input = line;
    char *elim = " \n";
    char *token = NULL;
    char *currptr = NULL;

    printf("Tokens: \n");

    while ((token = strtok_r(input, elim, &currptr))) {
      printf("%s\n", token);
      input = NULL;
    }
  } else {
    printf("failed");
  }

  free(line);
  return 0;
}

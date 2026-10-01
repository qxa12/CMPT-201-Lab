#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *history[5] = {NULL};
  int i = 0;
  while (1) {
    printf("Enter input: ");

    char *line = NULL;
    size_t len = 0;
    ssize_t n = getline(&line, &len, stdin);
    if (n != -1) {
      if (n > 0 && line[n - 1] == '\n') {
        line[n - 1] = '\0';
        if (strcmp(line, "print") != 0 && i < 5) {
          history[i] = line;
          i += 1;
        } else if (strcmp(line, "print") == 0 && i >= 5) {
          free(history[0]);
          for (int j = 1; j < 5; j++) {
            history[j - 1] = history[j];
          }
          history[4] = line;
          for (int k = 0; k < 5; k++) {
            printf("%s\n", history[k]);
          }
        } else if (strcmp(line, "print") == 0 && i < 5) {
          history[i] = line;
          for (int j = 0; j <= i; j++) {
            printf("%s\n", history[j]);
          }
          i += 1;
        } else if (strcmp(line, "print") != 0 && i >= 5) {
          free(history[0]);
          for (int j = 1; j < 5; j++) {
            history[j - 1] = history[j];
          }
          history[4] = line;
        }
      }
    } else {
      free(line);
      break;
    }
  }
  free(history[0]);
  free(history[1]);
  free(history[2]);
  free(history[3]);
  free(history[4]);
  return 0;
}

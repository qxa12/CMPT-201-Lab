#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (true) {
    printf("Enter programs to run.\n");
    char *line = NULL;
    size_t size = 0;
    ssize_t len = getline(&line, &size, stdin);
    if (len != -1) {
      if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
      }
    } else {
      printf("getline failed!");
      break;
    }
    pid_t pid = fork();
    if (pid == 0) {
      execlp(line, line, (char *)NULL);

      perror("execlp");
      exit(EXIT_FAILURE);
    } else if (pid > 0) {
      waitpid(pid, NULL, 0);
    } else {
      printf("fork failed!");
      free(line);
      break;
    }
    free(line);
  }
}

#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    if (execl("/usr/bin/ls", "ls", "-a", "-l", NULL) == -1) {
      perror("execl");
      exit(EXIT_FAILURE);
    }
  } else if (pid == -1) {
    perror("fork failed");
    exit(EXIT_FAILURE);
  } else {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
      printf("Child done with exit status: %d\n", WEXITSTATUS(wstatus));
    } else {
      printf("Child did not exxeit normaly.\n");
    }
  }
  return 0;
}

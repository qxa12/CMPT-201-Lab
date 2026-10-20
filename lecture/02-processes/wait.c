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

int main() {
  pid_t pid = fork();
  if (pid) {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
      printf("Child exited with exit status: %d\n", WEXITSTATUS(wstatus));
    } else {
      printf("Child did not exit normally");
    }
  } else {
    if (execl("/usr/bin/ls", "/usr/bin/ls", "-a", "-l", NULL) == -1) {
      perror("execl");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}

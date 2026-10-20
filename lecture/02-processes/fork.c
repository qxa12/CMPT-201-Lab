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
  printf("Start PID=%d, parent PID =%d\n", getpid(), getppid());
  pid_t pid = fork();
  if (pid == 0) {
    printf("CHILD: PID=%d, parent: PID=%d\n", getpid(), getppid());
  } else if (pid == -1) {
    perror("fork failed");
    exit(EXIT_FAILURE);
  } else {
    printf("PARENT: PID=%d, child: PID=%d\n", getpid(), pid);
  }
  return 0;
}

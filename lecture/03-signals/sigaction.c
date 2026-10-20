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

static char *message = "CTRL-C Pressed.\n";
void signal_handler(int signum) { write(STDOUT_FILENO, message, strlen(message)); }

int main() {
  struct sigaction act;
  act.sa_handler = signal_handler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  if (sigaction(SIGINT, &act, NULL) == -1) {
    perror("sigaction() failed");
    exit(EXIT_FAILURE);
  }

  printf("sigaction set, pid = %d, waiting for ctrl-c.\n", getpid());

  while (true) {
    sleep(1);
  }

  return 0;
}

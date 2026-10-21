#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
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
  for (int i = 0; i <= 100; i++) {
    printf("\rLoading: %d%%", i);
    fflush(stdout);
    usleep(50000);
  }
  return 0;
}

#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BLOCK_SIZE 128
#define HEAP_SIZE 256
#define BUF_SIZE 64

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block(char *start) {
  for (size_t i = sizeof(struct header); i < BLOCK_SIZE; i++) {
    uint64_t value = (unsigned char)start[i];
    print_out("%lu\n", &value, sizeof(value));
  }
}

void initialize_block(struct header *block, uint64_t size, struct header *next, int fill_value) {
  block->size = size;
  block->next = next;
  memset(block + 1, fill_value, size - sizeof(struct header));
}

int main() {
  char *heap_start = sbrk(0);
  if (sbrk(HEAP_SIZE) == (void *)-1) {
    handle_error("sbrk");
  }
  struct header *block1 = (struct header *)heap_start;
  struct header *block2 = (struct header *)(heap_start + BLOCK_SIZE);

  initialize_block(block1, BLOCK_SIZE, NULL, 0);
  initialize_block(block2, BLOCK_SIZE, block1, 1);

  print_out("first block: %p\n", &block1, sizeof(block1));
  print_out("second block: %p\n", &block2, sizeof(block2));
  print_out("first block size: %lu\n", &block1->size, sizeof(block1->size));
  print_out("first block next: %p\n", &block1->next, sizeof(block1->next));
  print_out("second block size: %lu\n", &block2->size, sizeof(block2->size));
  print_out("second block next: %p\n", &block2->next, sizeof(block2->next));

  print_block((char *)block1);
  print_block((char *)block2);

  return 0;
}

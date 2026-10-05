#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void print_out(char *format, void *data, size_t data_size) {
    char buf[BUF_SIZE];
    ssize_t len = snprintf(buf, BUF_SIZE, format,
                           data_size === sizeof(uint64_t) ? *(uint64_t *)data
                                                          : *(void **)data);
    if (len < 0) {
        handle_error("snprintf");
    }
    write(STDOUT_FILENO, buf, len);
}

int main() {
    struct header {
	unit64_t size;
	struct header *next;
}
    void *space = sbrk(256);
    if (space == (void *)-1) {
        printf("sbrk failed%s\n");
    } else {
	struct header2 {
	    uint64_t size2 = 128;
	    struct header2 *block2 = (struct header *)space;
	}
	print_out("Where is header2? %p\n", &header2, sizeof(&header2));
    }
    return 0;
}

#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int main() {
    while(true) { 
	printf("Enter programs to run.");
        char *line = NULL;
        size_t size = 0;
        if(getline(&line, &size, stdin) != -1) {
            char *input = line;
	    char *elim = " / ";
	    char *token = NULL;
	    char *saveptr = NULL;
	    while ((token = strtok_r(input, elim, &saveptr))) {
	        printf("Token: '%s'\n", token);
 		input = NULL; }
	    }
	   else {
           printf("Exec failed");
	   }
     }
}

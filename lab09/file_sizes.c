#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {	
	if (argc <= 1) {
        printf("Usage: <filenames>\n");
        return 1;
    }
    long total = 0;
    for (int i = 1; i < argc; i++) {
        struct stat s;
        if (stat(argv[i], &s) != 0) {
            perror(argv[i]);
            exit(1);
        }
        // bubblesort.c: 667 bytes
        printf("%s: %ld bytes\n", argv[i], (long)s.st_size);
        total = total + s.st_size;
    }
    printf("Total: %ld bytes\n", total);
    return 0;
}
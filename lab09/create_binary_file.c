#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {	
	if (argc <= 2) {
        printf("Usage: <filename> <numbers>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        printf("cannot create file");
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        int c = atoi(argv[i]);
        if (c <= 255 && c >= 0) {
            fputc(c, f);
        }
        
    }
    fclose(f);
    return 0;
}
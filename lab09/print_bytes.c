#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {	
	if (argc != 2) {
        printf("Usage: <filename> \n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("cannot read file");
        return 1;
    }
    int c;
    long i = 0;
    while ((c = fgetc(f)) != EOF) {
        // byte    0:  72 0x48 'H'
        printf("byte %4ld: %3d 0x%02x", i, c, c);
        int p = isprint(c);
        if (p != 0) {
            printf(" '%c'\n", c);
        } else {
            printf("\n");
        }  
        i++;
    }

    
    fclose(f);
    return 0;
}
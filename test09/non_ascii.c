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
    int i = 0;
    while ((c = fgetc(f)) != EOF) {
        fseek(f, 0, SEEK_CUR);
        if (c >= 128 && c <= 255 && i == 0) {
            // file2: byte 5 is non-ASCII
            fseek(f, -1, SEEK_CUR);
            printf("%s: byte %ld is non-ASCII\n", argv[1], ftell(f));
            i = 1;
        }
        
    }
    if (i == 0) {
        printf("%s is all ASCII\n", argv[1]);
    }
    fclose(f);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {	
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    int c1;
    int c2;
    int i = 0;
    while (((c1 = fgetc(f1)) != EOF) && ((c2 = fgetc(f2)) != EOF)) {
        fseek(f1, 0, SEEK_CUR);
        if (c1 != c2 && i == 0) {
            fseek(f1, -1, SEEK_CUR);
            printf("Files differ at byte %ld\n", ftell(f1));
            i = 1;
        }
    }

    
    if (((c1 = fgetc(f1)) != EOF) && i == 0) {
        printf("EOF on %s\n", argv[2]);
    } else if (((c2 = fgetc(f2)) != EOF) && i == 0) {
        printf("EOF on %s\n", argv[1]);
    } else if (i == 0) {
        printf("Files are identical\n");
    }

    
    fclose(f1);
    fclose(f2);
    return 0;
}
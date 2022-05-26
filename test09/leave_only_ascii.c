#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[]) {	
    FILE *fr = fopen(argv[1], "r+");
    FILE *fw = fopen("store.txt", "w");
    int c;
    while ((c = fgetc(fr)) != EOF) {
        if (c < 128 || c > 255) {
            // ASCII
            fputc(c, fw);
        }
    }
    fclose(fr);
    fclose(fw);

    FILE *fpr = fopen("store.txt", "r+");
    FILE *fpw = fopen(argv[1], "w");
    while ((c = fgetc(fpr)) != EOF) { 
        fputc(c, fpw);
    }
    fclose(fpr);
    fclose(fpw);

    return 0;
}
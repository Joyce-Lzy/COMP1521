// COMP1521 20T3 final exam Q5 sample solution

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int n = atoi(argv[1]);
    struct stat s;
    assert(stat(argv[2], &s) == 0);
    int desired_size = s.st_size - n;
    
    FILE *fr = fopen(argv[2], "r");
    FILE *fw = fopen(argv[3], "w");
    int c;
    n = 0;
    while ((c = fgetc(fr)) != EOF && n < desired_size) {
        fputc(c, fw);
        n++;
    }
    fclose(fr);
    fclose(fw);
}
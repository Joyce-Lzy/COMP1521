#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    struct stat statbuf;
    if (stat(argv[1], &statbuf) != 0) {
        printf("0\n");
        return 0;
    } else {
        printf("%d\n", S_ISDIR(statbuf.st_mode));
        //printf("1\n");
    }
    
    return 0;
}

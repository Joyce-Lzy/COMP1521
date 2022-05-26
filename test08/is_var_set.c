#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {	
	if (argc != 2) {
        printf("Usage: <env name>\n");
        return 1;
    }
    char *env = getenv(argv[1]);
    if (env == NULL) {
        printf("0\n");
    } else if (strlen(env) == 0) {
        printf("0\n"); 
    } else {
        printf("1\n");
    }
    return 0;
}
//z5271698
#include <stdio.h>
#include <string.h>
#define MAX 1024

int main(void) {
	while(1)
    {
        char array[MAX];
        if( !fgets(array, MAX, stdin) || feof(stdin) )
        {
            break;
        }
        if (strlen(array) % 2 == 0) {
            fputs(array, stdout);
        }
    }
    return 0;
}

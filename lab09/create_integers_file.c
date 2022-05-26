#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {	
	if (argc != 4) {
        printf("Usage: <filename> <number> <number>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        printf("cannot create file");
        return 1;
    }
    int first =  atoi(argv[2]);
    int last = atoi(argv[3]);
    if (first > last) {
        printf("wrong number");
    }

    for (int i = first; i <= last; i++) {
	    char text[5]; 
        sprintf(text, "%d", i);
        strcat(text, "\n");
        //printf("String value = %s", text);
        fprintf(f, "%s", text);
        
    }
    
    fclose(f);
    return 0;
}
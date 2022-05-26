#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage: <text> \n");
        return 1;
    }

    char *home_name = getenv("HOME");
    char *his_file = {"/.diary"};
    strcat(home_name, his_file);
    FILE *f;
    if ((f = fopen(home_name, "a+")) == NULL) {
        perror(home_name);
    } else {
        int i = 1;
        while (i < argc) {
            fprintf(f, "%s ", argv[i]);
            i++;
        }
        fprintf(f, "\n"); 
        fclose(f);
    }

    return 0;
}
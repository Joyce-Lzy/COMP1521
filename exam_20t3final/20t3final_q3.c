// COMP1521 20T3 final exam Q3 sample solution

// Test whether the value of two environment are the same
// if so print 1, else print 0

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int intenv(char *name) {
    char *value = getenv(name);
    return value ? atoi(value) : 42;
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    int delta = intenv(argv[1]) - intenv(argv[2]);
    if (delta > -10 && delta < 10) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}
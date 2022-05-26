// COMP1521 20T3 final exam Q6

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>

int bit_set(uint8_t byte);

int main(int argc, char *argv[]) {   
    FILE *fr = fopen(argv[1], "r");
    int c;
    int n = 0;
    while ((c = fgetc(fr)) != EOF) { 
        n += bit_set(c);
    }
    fclose(fr);
    printf("%s has %d bits set\n", argv[1], n);
}

int bit_set(uint8_t byte) {
    int count = 0;
    for(int i = 0; i < 8; i++)
        count += (byte >> i) & 0x01; // Shift bit[i] to the first position, and mask off the remaining bits.
    return count;
}
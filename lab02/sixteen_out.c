// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);
int get_nth_bit(int16_t value, int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
    char *a = malloc(sizeof(char) * (N_BITS+1));
    
    for (int i = N_BITS - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        a[N_BITS-i-1] = bit +'0';
    }
    
    a[N_BITS] = '\0';
    return a;
}

int get_nth_bit(int16_t value, int n) {
    // shift the bit right n bits
    // this leaves the n-th bit as the least significant bit
    int16_t shifted_value = value >> n;
    // zero all bits except the the least significant bit
    int bit = shifted_value & 1;
    return bit;
}


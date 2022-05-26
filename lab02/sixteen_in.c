// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    
    int16_t sum = 0;
    for (int i = 0; i < N_BITS; i++) {
        if (bits[N_BITS-i-1] == '1') {
            if (i == 0) {
                sum = 1;
            } else {
                sum = sum + (2 << (i-1));
            }
        }
    }
    return sum;
}


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);
int int_to_hex(int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int hex = int_to_hex(bcd_value);
    //printf("hex = %d\n", hex);
    int one = hex % 10;
    int hund = hex / 100;
    int ten = hund * 10;
    return ten+one;
}

int int_to_hex(int n) {
    // sizeof returns number of bytes in n's representation
    // each byte is 2 hexadecimal digits

    int n_hex_digits = 2 * (sizeof n);

    // allocate memory to hold the hex digits + a terminating 0
    char *string = malloc(n_hex_digits + 1);

    // print hex digits from most significant to least significant

    for (int which_digit = 0; which_digit < n_hex_digits; which_digit++) {
        // shift value across so hex digit we want
        // is in bottom 4 bits

        int bit_shift = 4 * (n_hex_digits - which_digit - 1);
        int shifted_value = n >> bit_shift;

        // mask off (zero) all bits but the bottom 4 bites

        int hex_digit = shifted_value & 0xF;

        // hex digit will be a value 0..15
        // obtain the corresponding ASCII value
        // "0123456789ABCDEF" is a char array
        // containing the appropriate ASCII values

        int hex_digit_ascii = "0123456789ABCDEF"[hex_digit];

        string[which_digit] = hex_digit_ascii;
    }

    // 0 terminate the array
    string[n_hex_digits] = 0;
    int x = atoi(string);
    free(string);
    return x;
}
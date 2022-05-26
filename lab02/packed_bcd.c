#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);
uint32_t int_to_hex(uint32_t n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    uint32_t hex = int_to_hex(packed_bcd_value);
    return hex;
}

uint32_t int_to_hex(uint32_t n) {
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
        uint32_t shifted_value = n >> bit_shift;

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
    uint32_t x = atoi(string);
    free(string);
    return x;
}

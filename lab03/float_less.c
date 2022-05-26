// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"
#define N_BITS             32
#define SIGN_BIT           31
#define EXPONENT_HIGH_BIT  30
#define EXPONENT_LOW_BIT   23
#define FRACTION_HIGH_BIT  22
#define FRACTION_LOW_BIT    0
#define EXPONENT_INF_NAN  255

uint32_t extract_bit_range(uint32_t value, int high, int low);

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    // PUT YOUR CODE HERE
    float_components_t b1;
    b1.sign = extract_bit_range(bits1, SIGN_BIT, SIGN_BIT);
    b1.fraction = extract_bit_range(bits1, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    b1.exponent = extract_bit_range(bits1, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);
    
    float_components_t b2;
    b2.sign = extract_bit_range(bits2, SIGN_BIT, SIGN_BIT);
    b2.fraction = extract_bit_range(bits2, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    b2.exponent = extract_bit_range(bits2, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);
    if (b1.exponent == EXPONENT_INF_NAN && b1.fraction != 0) {
        // 0 is return if bits1 is Nan
        return 0;
    } else if (b2.exponent == EXPONENT_INF_NAN && b2.fraction != 0) {
        // 0 is return if bits2 is Nan
        return 0;
    }

    if (b1.sign == 1 && b2.sign == 0) {
        // b1 is negative and b2 is positive
        if (b1.exponent == 0 && b1.fraction == 0 && b2.exponent == 0 && b2.fraction == 0) {
            // +0 = -0 = 0
            return 0;
        }
        return 1;
    } else if (b1.sign == 0 && b2.sign == 1) {
        // b1 is positive, b2 is negative
        return 0;
    } else if (b1.sign == 0 && b2.sign == 0) {
        // both positive
        if (b1.exponent < b2.exponent) {
            return 1;
        } else if (b1.exponent == b2.exponent && b1.fraction < b2.fraction) {
            return 1;
        } else {
            return 0;
        }
    } else {
        // both negative
        if (b1.exponent > b2.exponent) {
            return 1;
        } else if (b1.exponent == b2.exponent && b1.fraction > b2.fraction) {
            return 1;
        } else {
            return 0;
        } 
    }
}

// extract a range of bits from a value
uint32_t extract_bit_range(uint32_t value, int high, int low) {
    uint32_t mask = (((uint32_t)1) << (high - low + 1)) - 1;
    return (value >> low) & mask;
}
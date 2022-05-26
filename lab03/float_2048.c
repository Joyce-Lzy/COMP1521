// Multiply a float by 2048 using bit operations only

#include <stdio.h>
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

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//

uint32_t extract_bit_range(uint32_t value, int high, int low);

uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t c;
    c.sign = extract_bit_range(f, SIGN_BIT, SIGN_BIT);
    c.fraction = extract_bit_range(f, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    c.exponent = extract_bit_range(f, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);
    if (c.exponent == EXPONENT_INF_NAN) {
        // if +inf or -inf, or Nan it is returned unchanged
        return f;
    } else if (c.exponent == 0 && c.fraction == 0) {
        // if 0 it is returned unchanged
        return f;
    }
    // 2048 = 2^11
    c.exponent += 11;
    if (c.exponent >= EXPONENT_INF_NAN) {
        c.exponent = EXPONENT_INF_NAN;
        c.fraction = 0;
    }
    
    return (c.sign << SIGN_BIT) | (c.exponent << EXPONENT_LOW_BIT) | c.fraction;
}

// extract a range of bits from a value
uint32_t extract_bit_range(uint32_t value, int high, int low) {
    uint32_t mask = (((uint32_t)1) << (high - low + 1)) - 1;
    return (value >> low) & mask;
}

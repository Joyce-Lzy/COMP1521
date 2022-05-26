// Extract the 3 parts of a float using bit operations only

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

#define EXPONENT_OFFSET   127
#define EXPONENT_INF_NAN  255

uint32_t extract_bit_range(uint32_t value, int high, int low);

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t c;
    c.sign = extract_bit_range(f, SIGN_BIT, SIGN_BIT);
    c.fraction = extract_bit_range(f, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    c.exponent = extract_bit_range(f, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);
    return c;
}

// extract a range of bits from a value
uint32_t extract_bit_range(uint32_t value, int high, int low) {
    uint32_t mask = (((uint32_t)1) << (high - low + 1)) - 1;
    return (value >> low) & mask;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == EXPONENT_INF_NAN && f.fraction != 0) {
        return 1; 
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == EXPONENT_INF_NAN && f.sign == 0 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }  
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == EXPONENT_INF_NAN && f.sign == 1 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE
    if (f.exponent == 0 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

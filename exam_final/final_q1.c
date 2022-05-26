// COMP1521 21T2 ... final exam, question 1

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 8

void
and (bool x[BITS], bool y[BITS], bool result[BITS])
{
	for (int i = 0; i < BITS; i++) {
		result[i] = x[i] & y[i];
	}
}

void
or (bool x[BITS], bool y[BITS], bool result[BITS])
{
	for (int i = 0; i < BITS; i++) {
		result[i] = x[i] | y[i];
	}
}

void
xor (bool x[BITS], bool y[BITS], bool result[BITS])
{
	for (int i = 0; i < BITS; i++) {
		result[i] = x[i] ^ y[i];
	}
}

void
not (bool x[BITS], bool result[BITS])
{
	for (int i = 0; i < BITS; i++) {
		result[i] = ! x[i];
	}	
}

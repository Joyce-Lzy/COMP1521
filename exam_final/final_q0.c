// COMP1521 21T2 ... final exam, question 0

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int
count_leading_zeroes (uint32_t x)
{
	int count = sizeof(int) * 8;
	x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

	x -= x >> 1 & 0x55555555;
    x = (x >> 2 & 0x33333333) + (x & 0x33333333);
    x = ((x >> 4) + x)& 0x0f0f0f0f;
    x += x >> 8;
    x += x >> 16;
	return count - (x & 0x0000003f); 
}


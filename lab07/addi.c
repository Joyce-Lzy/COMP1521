// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    uint32_t res = 0;
    res = (res | 0b001000) << 26;
    res = res | ((s & 0b11111) << 21);
    res = res | ((t & 0b11111) << 16);
    res = res | (i & 0b1111111111111111);
    return res;

}

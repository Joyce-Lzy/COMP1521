#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t make_add(uint32_t d, uint32_t s, uint32_t t) {
    // 0000 00ss ssst tttt dddd d000 0010 0000
    uint32_t res = 0;
    res = res | ((s & 0b11111) << 21);
    res = res | ((t & 0b11111) << 16);
    res = res | ((d & 0b11111) << 11);
    res = res | 0b100000;
    return res;

}

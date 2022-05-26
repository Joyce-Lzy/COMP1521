// COMP1521 21T2 ... final exam, question 9

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "final_q8.h"
#include "final_q8_opcodes.h"

Instruction
decode_instruction (Word insn_word)
{
	Instruction i;
	uint32_t sepcial = insn_word >> 26;
	if (sepcial == OP_SPECIAL) {
		// add
		uint32_t least = insn_word & 0b111111;
		if (least == OP_SPECIAL_ADD) {
			//i.op = "add";
			strcpy (i.op,"add");
		} else if (least == OP_SPECIAL_ADDU) {
			//i.op = "addu";
			strcpy (i.op,"addu");
		} else if (least == OP_SPECIAL_SUB) {
			//i.op = "sub";
			strcpy (i.op,"sub");
		} else if (least == OP_SPECIAL_SUBU) {
			//i.op = "subu";
			strcpy (i.op,"subu");
		}
		i.uses_rs = 1;
		i.uses_rt = 1;
		i.uses_rd = 1; 
		i.uses_base = 0;
		i.uses_imm = 0;
		i.imm = 0;

		uint32_t rs = (insn_word >>21) & 0b11111;
		uint32_t rt = (insn_word >>16) & 0b11111;
		uint32_t rd = (insn_word >>11) & 0b11111;
		i.rs = rs;
		i.rt = rt;
		i.rd = rd;

	} else {
		// addi
		if (sepcial == OP_ADDI) {
			//i.op = "addi";
			strcpy (i.op,"addi");
			i.uses_base = 0;
			i.uses_rs = 1;
			uint32_t rs = (insn_word >>21) & 0b11111;
			i.rs = rs;
		} else if (sepcial == OP_ADDIU) {
			//i.op = "addiu";
			strcpy (i.op,"addiu");
			i.uses_base = 0;
			i.uses_rs = 1;
			uint32_t rs = (insn_word >>21) & 0b11111;
			i.rs = rs;
		} else if (sepcial == OP_LB) {
			//i.op = "lb";
			strcpy (i.op,"lb");
			i.uses_base = 1;
			i.uses_rs = 0;
			uint32_t base = (insn_word >>21) & 0b11111;
			i.base = base;
		} else if (sepcial == OP_LW) {
			//i.op = "lw";
			strcpy (i.op,"lw");
			i.uses_base = 1;
			i.uses_rs = 0;
			uint32_t base = (insn_word >>21) & 0b11111;
			i.base = base;
		}
		i.uses_rt = 1;
		i.uses_rd = 0; 
		i.uses_imm = 1;
		i.imm = insn_word & 0xffff;
		uint32_t rt = (insn_word >>16) & 0b11111;
		i.rt = rt;
	}
	

	return i;
}

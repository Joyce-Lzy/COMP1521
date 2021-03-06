// A table of MIPS32 r5.04 instruction opcodes.
// last updated 2021-06-16 11:31:30
//
// Adapted to C for COMP1521 21T2 final exam question 8;
// reserved, beta-, epsilon-, delta-, and theta- opcodes removed.

#ifndef FINAL_Q8_OPCODES_H_
#define FINAL_Q8_OPCODES_H_

#define OP_SPECIAL     0b000000
#define OP_REGIMM      0b000001
#define OP_J           0b000010
#define OP_JAL         0b000011
#define OP_BEQ         0b000100
#define OP_BNE         0b000101
#define OP_BLEZ        0b000110
#define OP_BGTZ        0b000111
#define OP_ADDI        0b001000
#define OP_ADDIU       0b001001
#define OP_SLTI        0b001010
#define OP_SLTIU       0b001011
#define OP_ANDI        0b001100
#define OP_ORI         0b001101
#define OP_XORI        0b001110
#define OP_LUI         0b001111
#define OP_COP0        0b010000
#define OP_COP1        0b010001
#define OP_COP2        0b010010
#define OP_COP1X       0b010011
#define OP_BEQL        0b010100
#define OP_BNEL        0b010101
#define OP_BLEZL       0b010110
#define OP_BGTZL       0b010111
#define OP_SPECIAL2    0b011100
#define OP_JALX        0b011101
#define OP_MSA         0b011110
#define OP_SPECIAL3    0b011111
#define OP_LB          0b100000
#define OP_LH          0b100001
#define OP_LWL         0b100010
#define OP_LW          0b100011
#define OP_LBU         0b100100
#define OP_LHU         0b100101
#define OP_LWR         0b100110
#define OP_SB          0b101000
#define OP_SH          0b101001
#define OP_SWL         0b101010
#define OP_SW          0b101011
#define OP_SWR         0b101110
#define OP_CACHE       0b101111
#define OP_LL          0b110000
#define OP_LWC1        0b110001
#define OP_LWC2        0b110010
#define OP_PREF        0b110011
#define OP_LDC1        0b110101
#define OP_LDC2        0b110110
#define OP_SC          0b111000
#define OP_SWC1        0b111001
#define OP_SWC2        0b111010
#define OP_SDC1        0b111101
#define OP_SDC2        0b111110

#define OP_SPECIAL_SLL      0b000000
#define OP_SPECIAL_MOVCI    0b000001
#define OP_SPECIAL_SRL      0b000010
#define OP_SPECIAL_SRA      0b000011
#define OP_SPECIAL_SLLV     0b000100
#define OP_SPECIAL_LSA      0b000101
#define OP_SPECIAL_SRLV     0b000110
#define OP_SPECIAL_SRAV     0b000111
#define OP_SPECIAL_JR       0b001000
#define OP_SPECIAL_JALR     0b001001
#define OP_SPECIAL_MOVZ     0b001010
#define OP_SPECIAL_MOVN     0b001011
#define OP_SPECIAL_SYSCALL  0b001100
#define OP_SPECIAL_BREAK    0b001101
#define OP_SPECIAL_SYNC     0b001111
#define OP_SPECIAL_MFHI     0b010000
#define OP_SPECIAL_MTHI     0b010001
#define OP_SPECIAL_MFLO     0b010010
#define OP_SPECIAL_MTLO     0b010011
#define OP_SPECIAL_MULT     0b011000
#define OP_SPECIAL_MULTU    0b011001
#define OP_SPECIAL_DIV      0b011010
#define OP_SPECIAL_DIVU     0b011011
#define OP_SPECIAL_ADD      0b100000
#define OP_SPECIAL_ADDU     0b100001
#define OP_SPECIAL_SUB      0b100010
#define OP_SPECIAL_SUBU     0b100011
#define OP_SPECIAL_AND      0b100100
#define OP_SPECIAL_OR       0b100101
#define OP_SPECIAL_XOR      0b100110
#define OP_SPECIAL_NOR      0b100111
#define OP_SPECIAL_SLT      0b101010
#define OP_SPECIAL_SLTU     0b101011
#define OP_SPECIAL_TGE      0b110000
#define OP_SPECIAL_TGEU     0b110001
#define OP_SPECIAL_TLT      0b110010
#define OP_SPECIAL_TLTU     0b110011
#define OP_SPECIAL_TEQ      0b110100
#define OP_SPECIAL_TNE      0b110110

#define OP_REGIMM_BLTZ      0b00000
#define OP_REGIMM_BGEZ      0b00001
#define OP_REGIMM_BLTZL     0b00010
#define OP_REGIMM_BGEZL     0b00011
#define OP_REGIMM_TGEI      0b01000
#define OP_REGIMM_TGEIU     0b01001
#define OP_REGIMM_TLTI      0b01010
#define OP_REGIMM_TLTIU     0b01011
#define OP_REGIMM_TEQI      0b01100
#define OP_REGIMM_TNEI      0b01110
#define OP_REGIMM_BLTZAL    0b10000
#define OP_REGIMM_BGEZAL    0b10001
#define OP_REGIMM_BLTZALL   0b10010
#define OP_REGIMM_BGEZALL   0b10011
#define OP_REGIMM_SYNCI     0b11111

#define OP_SPECIAL2_MADD    0b000000
#define OP_SPECIAL2_MADDU   0b000001
#define OP_SPECIAL2_MUL     0b000010
#define OP_SPECIAL2_MSUB    0b000100
#define OP_SPECIAL2_MSUBU   0b000101
#define OP_SPECIAL2_CLZ     0b100000
#define OP_SPECIAL2_CLO     0b100001
#define OP_SPECIAL2_SDBBP   0b111111

#define OP_SPECIAL3_EXT     0b000000
#define OP_SPECIAL3_INS     0b000100
#define OP_SPECIAL3_LWLE    0b011001
#define OP_SPECIAL3_LWRE    0b011010
#define OP_SPECIAL3_CACHEE  0b011011
#define OP_SPECIAL3_SBE     0b011100
#define OP_SPECIAL3_SHE     0b011101
#define OP_SPECIAL3_SCE     0b011110
#define OP_SPECIAL3_SWE     0b011111
#define OP_SPECIAL3_BSHFL   0b100000
#define OP_SPECIAL3_SWLE    0b100001
#define OP_SPECIAL3_SWRE    0b100010
#define OP_SPECIAL3_PREFE   0b100011
#define OP_SPECIAL3_LBUE    0b101000
#define OP_SPECIAL3_LHUE    0b101001
#define OP_SPECIAL3_LBE     0b101100
#define OP_SPECIAL3_LHE     0b101101
#define OP_SPECIAL3_LLE     0b101110
#define OP_SPECIAL3_LWE     0b101111
#define OP_SPECIAL3_RDHWR   0b111011

#define OP_MOVCI_TF_MOVF    0b0
#define OP_MOVCI_TF_MOVT    0b1

#define OP_SRL_R_SRL        0b0
#define OP_SRL_R_ROTR       0b1

#define OP_SRLV_R_SRLV      0b0
#define OP_SRLV_R_ROTRV     0b1

#define OP_BSHFL_SA_WSBH    0b00010
#define OP_BSHFL_SA_SEB     0b10000
#define OP_BSHFL_SA_SEH     0b11000

#define OP_COP0_RS_MFC0     0b00000
#define OP_COP0_RS_MTC0     0b00100
#define OP_COP0_RS_RDPGPR   0b01010
#define OP_COP0_RS_MFMC0    0b01011
#define OP_COP0_RS_WRPGPR   0b01110

#define OP_COP0_F_TLBR      0b000001
#define OP_COP0_F_TLBWI     0b000010
#define OP_COP0_F_TLBINV    0b000011
#define OP_COP0_F_TLBINVF   0b000100
#define OP_COP0_F_TLBWR     0b000110
#define OP_COP0_F_TLBP      0b001000
#define OP_COP0_F_ERET      0b010000
#define OP_COP0_F_DERET     0b011111
#define OP_COP0_F_WAIT      0b100000

#define OP_COP1_RS_MFC1     0b00000
#define OP_COP1_RS_CFC1     0b00010
#define OP_COP1_RS_MFHC1    0b00011
#define OP_COP1_RS_MTC1     0b00100
#define OP_COP1_RS_CTC1     0b00110
#define OP_COP1_RS_MTHC1    0b00111
#define OP_COP1_RS_BC1      0b01000
#define OP_COP1_RS_BC1ANY2  0b01001
#define OP_COP1_RS_BC1ANY4  0b01010
#define OP_COP1_RS_BZ_V     0b01011
#define OP_COP1_RS_BNZ_V    0b01111
#define OP_COP1_RS_S        0b10000
#define OP_COP1_RS_D        0b10001
#define OP_COP1_RS_W        0b10100
#define OP_COP1_RS_L        0b10101
#define OP_COP1_RS_PS       0b10110
#define OP_COP1_RS_BZ_B     0b11000
#define OP_COP1_RS_BZ_H     0b11001
#define OP_COP1_RS_BZ_W     0b11010
#define OP_COP1_RS_BZ_D     0b11011
#define OP_COP1_RS_BNZ_B    0b11100
#define OP_COP1_RS_BNZ_H    0b11101
#define OP_COP1_RS_BNZ_W    0b11110
#define OP_COP1_RS_BNZ_D    0b11111

#define OP_COP1_S_ADD       0b000000
#define OP_COP1_S_SUB       0b000001
#define OP_COP1_S_MUL       0b000010
#define OP_COP1_S_DIV       0b000011
#define OP_COP1_S_SQRT      0b000100
#define OP_COP1_S_ABS       0b000101
#define OP_COP1_S_MOV       0b000110
#define OP_COP1_S_NEG       0b000111
#define OP_COP1_S_ROUND_L   0b001000
#define OP_COP1_S_TRUNC_L   0b001001
#define OP_COP1_S_CEIL_L    0b001010
#define OP_COP1_S_FLOOR_L   0b001011
#define OP_COP1_S_ROUND_W   0b001100
#define OP_COP1_S_TRUNC_W   0b001101
#define OP_COP1_S_CEIL_W    0b001110
#define OP_COP1_S_FLOOR_W   0b001111
#define OP_COP1_S_MOVCF     0b010001
#define OP_COP1_S_MOVZ      0b010010
#define OP_COP1_S_MOVN      0b010011
#define OP_COP1_S_RECIP     0b010101
#define OP_COP1_S_RSQRT     0b010110
#define OP_COP1_S_RECIP2    0b011100
#define OP_COP1_S_RECIP1    0b011101
#define OP_COP1_S_RSQRT1    0b011110
#define OP_COP1_S_RSQRT2    0b011111
#define OP_COP1_S_CVT_D     0b100001
#define OP_COP1_S_CVT_W     0b100100
#define OP_COP1_S_CVT_L     0b100101
#define OP_COP1_S_CVT_PS    0b100110
#define OP_COP1_S_C_F       0b110000
#define OP_COP1_S_C_UN      0b110001
#define OP_COP1_S_C_EQ      0b110010
#define OP_COP1_S_C_UEQ     0b110011
#define OP_COP1_S_C_OLT     0b110100
#define OP_COP1_S_C_ULT     0b110101
#define OP_COP1_S_C_OLE     0b110110
#define OP_COP1_S_C_ULE     0b110111
#define OP_COP1_S_C_SF      0b111000
#define OP_COP1_S_C_NGLE    0b111001
#define OP_COP1_S_C_SEQ     0b111010
#define OP_COP1_S_C_NGL     0b111011
#define OP_COP1_S_C_LT      0b111100
#define OP_COP1_S_C_NGE     0b111101
#define OP_COP1_S_C_LE      0b111110
#define OP_COP1_S_C_NGT     0b111111

#define OP_COP1_MOVCF_TF_MOVF  0b0
#define OP_COP1_MOVCF_TF_MOVT  0b1

#define OP_COP2_RS_MFC2     0b00000
#define OP_COP2_RS_B0       0b00001
#define OP_COP2_RS_CFC2     0b00010
#define OP_COP2_RS_MFHC2    0b00011
#define OP_COP2_RS_MTC2     0b00100
#define OP_COP2_RS_B1       0b00101
#define OP_COP2_RS_CTC2     0b00110
#define OP_COP2_RS_MTHC2    0b00111
#define OP_COP2_RS_BC2      0b01000

#define OP_COP1X_F_LWXC1    0b000000
#define OP_COP1X_F_LDXC1    0b000001
#define OP_COP1X_F_LUXC1    0b000101
#define OP_COP1X_F_SWXC1    0b001000
#define OP_COP1X_F_SDXC1    0b001001
#define OP_COP1X_F_SUXC1    0b001101
#define OP_COP1X_F_PREFX    0b001111
#define OP_COP1X_F_ALNV_PS  0b011110
#define OP_COP1X_F_MADD_S   0b100000
#define OP_COP1X_F_MADD_D   0b100001
#define OP_COP1X_F_MADD_PS  0b100110
#define OP_COP1X_F_MSUB_S   0b101000
#define OP_COP1X_F_MSUB_D   0b101001
#define OP_COP1X_F_MSUB_PS  0b101110
#define OP_COP1X_F_NMADD_S  0b110000
#define OP_COP1X_F_NMADD_D  0b110001
#define OP_COP1X_F_NMADD_PS 0b110110
#define OP_COP1X_F_NMSUB_S  0b111000
#define OP_COP1X_F_NMSUB_D  0b111001
#define OP_COP1X_F_NMSUB_PS 0b111110

#endif /* !defined(FINAL_Q8_OPCODES_H_) */

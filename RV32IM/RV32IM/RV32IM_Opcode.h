
/*---------------------------------------------------------------------------*\
 RV32_Opcode.h	: This file provides the method for a five-stage pipeline CPU
 Written By		: Mong Tee Sim
 Version		: 2018 (C) Copyright 2018
 Dated			: 22nd September 2018
 ==============================================================================
 History
 -------
 Author	Date		Desciption
 ------------------------------------------------------------------------------
 Mong	09/22/2018	Initial Version

\*---------------------------------------------------------------------------*/

// page 116

#define			RV32I_NOP			0x00		//  0
#define			RV32I_NOPF			0xFF		//  0
#define			RV32I_LUI			0x37		//	1
#define			RV32I_AUIPC			0x17		//	2
#define			RV32I_JAL			0x6F		//	3
#define			RV32I_JALR			0x67		//	4

#define			RV32I_BRANCH        0x63
	#define		RV32I_BEQ			0x00		//	5
	#define		RV32I_BNE			0x01		//	6
	#define		RV32I_BLT			0x04		//	7
	#define		RV32I_BGE			0x05		//	8
	#define		RV32I_BLTU			0x06		//	9
	#define		RV32I_BGEU			0x07		//	10

#define			RV32I_LOAD			0x03
	#define		RV32I_LB			0x00 		//	11
	#define		RV32I_LH			0x01 		//	12
	#define		RV32I_LW			0x02 		//	13
	#define		RV32I_LBU			0x04 		//	14
	#define		RV32I_LHU			0x05 		//	15

#define			RV32I_STORE			0x23
	#define		RV32I_SB			0x00		//	16
	#define		RV32I_SH			0x01		//	17
	#define		RV32I_SW			0x02		//	18

#define			RV32I_MATHI			0x13
	#define		RV32I_ADDI			0x00 		//	19
	#define		RV32I_SLTI			0x02 		//	20
	#define		RV32I_SLTIU			0x03 		//	21
	#define		RV32I_XORI			0x04 		//	22
	#define		RV32I_ORI			0x06 		//	23
	#define		RV32I_ANDI			0x07 		//	24
	#define		RV32I_SLLI			0x01 		//	25

#define			RV32I_SHIFT			0x05
	#define		RV32I_SRLI			0x00 		//	26
	#define		RV32I_SRAI			0x20 		//	27

#define			RV32I_MATH			0x33
	#define		ADD_SUB				0x00
		#define		RV32I_ADD		0x00		//	28
		#define		RV32I_SUB		0x20		//	29

	#define		RV32I_SLL			0x01		//	30
	#define		RV32I_SLT			0x02		//	31
	#define		RV32I_SLTU			0x03		//	32 
	#define		RV32I_XOR			0x04		//	33

	#define		RV32I_SRL_SRA		0x05
		#define		RV32I_SRL		0x00		//	34 
		#define		RV32I_SRA		0x20		//	35 

	#define		RV32I_OR			0x06		//	36 
	#define		RV32I_AND			0x07		//	37

#define			RV32I_FINSTR		0x0F
	#define			RV32I_FENCE		0x00		//	38 
	#define			RV32I_FENCE_I	0x01		//	39

#define			RV32I_SPECIAL		0x73
	#define     RV32I_ECOMMAND		0x00
		#define		RV32I_ECALL		0x00		//	40 
		#define		RV32I_EBREAK	0x01		//	41 

	#define			RV32I_CSRRW		0x01		//	42 
	#define			RV32I_CSRRS		0x02		//	43 
		#define     RV32I_CCL		0xC00
		#define     RV32I_CCH       0xC80
		#define     RV32I_TML		0xC01
		#define     RV32I_TMH       0xC81
		#define     RV32I_INSTL		0xC02
		#define     RV32I_INSTH     0xC82

	#define			RV32I_CSRRC		0x03		//	44 
	#define			RV32I_CSRRWI	0x04		//	45 
	#define			RV32I_CSRRSI	0x05		//	46 
	#define			RV32I_CSRRCI	0x07		//	47 

// RV32M Standard Extension
//
	#define			RV32M_MUL 		0x00 
	#define			RV32M_MULH 		0x01 
	#define			RV32M_MULHSU	0x02 
	#define			RV32M_MULHU		0x03 

	#define			RV32M_DIV 		0x04 
	#define			RV32M_DIVU 		0x05 
	#define			RV32M_REM 		0x06 
	#define			RV32M_REMU 		0x07 

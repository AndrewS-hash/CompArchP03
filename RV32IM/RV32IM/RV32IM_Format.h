
/*---------------------------------------------------------------------------*\
 RV32_Format.h	: This file provides the method for a five-stage pipeline CPU
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


//-----------------------------------------------------------------------------
// Type of immediate extension
//
typedef struct R_TYPE {
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t rs2		: 5;
	uint32_t funct7		: 7;

} R_TYPE;

typedef struct R_TYPE1 {
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t shamt		: 5;
	uint32_t funct7		: 7;

} R_TYPE1;

typedef struct I_TYPE {
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t imm10_0	: 11;
	uint32_t imm11		: 1;

} I_TYPE;

typedef struct S_TYPE {
	uint32_t opcode		: 7;
	uint32_t imm4_0		: 5;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t rs2		: 5;
	uint32_t imm10_5	: 6;
	uint32_t imm11 		: 1;

} S_TYPE;

typedef struct B_TYPE {
	uint32_t opcode		: 7;
	uint32_t imm11		: 1;
	uint32_t imm4_1		: 4;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t rs2		: 5;
	uint32_t imm10_5	: 6;
	uint32_t imm12		: 1;

} B_TYPE;

typedef struct U_TYPE {
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t imm30_12	: 19;
	uint32_t imm31		: 1;

} U_TYPE;

typedef struct J_TYPE {
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t imm19_12	: 8;
	uint32_t imm11		: 1;
	uint32_t imm10_1	: 10;
	uint32_t imm20		: 1;

} J_TYPE;

typedef struct TC_TYPE
{
	uint32_t opcode		: 7;
	uint32_t rd			: 5;
	uint32_t funct3		: 3;
	uint32_t rs1		: 5;
	uint32_t csr    	: 12;
} TC_TYPE;

//-----------------------------------------------------------------------------
// CPU Stages
typedef struct PROGRAM_COUNTER_VAL
{
	uint32_t	oPC;
	uint32_t    oPCPlus4;
	uint32_t	iPC;
	uint32_t    iPCPlus4;

} PROGRAM_COUNTER_VAL;

typedef struct IF_STAGE_VAL
{
	uint32_t iPC;
	uint32_t oHit;
	uint32_t oIinstr;

} IF_STAGE_VAL;

typedef struct ID_STAGE_VAL
{
	uint32_t extSel;
	uint32_t extType;
	uint32_t extData;
	uint32_t rs1Data;
	uint32_t rs2Data;
	uint32_t wbSel;
	uint32_t oExtData;

	uint32_t Rs1;	
	uint32_t Rs2;	
	uint32_t PCPlus4;
	uint32_t WbReg;

	uint32_t CEX;
	uint32_t CMEM;
	uint32_t CWB;
	uint32_t Branch;

} ID_STAGE_VAL;

typedef struct EX_STAGE_VAL
{
	uint32_t Sum;
	uint32_t Branch;
	uint32_t Rs1;		
	uint32_t Rs2;		
	uint32_t PCPlus4;

} EX_STAGE_VAL;

typedef struct MEM_STAGE_VAL
{
	uint32_t Sum;
	uint32_t Branch;
	uint32_t Addr;
	uint32_t mdata;

} MEM_STAGE_VAL;

typedef struct WB_STAGE_VAL
{
	uint32_t wbOut;
	uint32_t Branch;
	uint32_t Addr;

} WB_STAGE_VAL;


//-----------------------------------------------------------------------------
// CPU Pipeline Registers
//
typedef struct IFID_PIPELINE_REGISTER_VAL
{
	uint32_t iPCPlus4;
	uint32_t iInstr;
	uint32_t oPCPlus4;
	uint32_t oInstr;
	 
} IFID_PIPELINE_REGISTER_VAL;


typedef struct IDEX_PIPELINE_REGISTER_VAL
{
	uint32_t iInstr;	
	uint32_t oInstr;
	uint32_t iPCPlus4;
	uint32_t oPCPlus4;

	uint32_t iCEX;
	uint32_t oCEX;
	uint32_t iCMEM;
	uint32_t oCMEM;
	uint32_t iCWB;
	uint32_t oCWB;
	uint32_t iBranch;
	uint32_t oBranch;
	uint32_t iExtData;
	uint32_t oExtData;
	uint32_t iWbReg;
	uint32_t oWbReg;
	uint32_t iRs1;
	uint32_t oRs1;
	uint32_t iRs2;
	uint32_t oRs2;
	uint32_t iRd;
	uint32_t oRd;
	uint32_t iRs1Data;
	uint32_t iRs2Data;
	uint32_t oRs1Data;
	uint32_t oRs2Data;
	 
} IDEX_PIPELINE_REGISTER_VAL;

typedef struct EXMEM_PIPELINE_REGISTER_VAL
{
	uint32_t iPCPlus4;
	uint32_t oPCPlus4;

	uint32_t iCMEM;
	uint32_t oCMEM;
	uint32_t iCWB;
	uint32_t oCWB;
	uint32_t iBranch;
	uint32_t oBranch;

	uint32_t iWbReg;
	uint32_t oWbReg;
	uint32_t iRs1;
	uint32_t oRs1;
	uint32_t iRs2;
	uint32_t oRs2;
	uint32_t iRd;
	uint32_t oRd;

	uint32_t iALUout;
	uint32_t oALUout;

	uint32_t iRegData;
	uint32_t oRegData;
	 
} EXMEM_PIPELINE_REGISTER_VAL;

typedef struct MEMWB_PIPELINE_REGISTER_VAL
{
	uint32_t iPCPlus4;
	uint32_t oPCPlus4;

	uint32_t iCWB;
	uint32_t oCWB;
	uint32_t iWbReg;
	uint32_t oWbReg;
	uint32_t iRs1;
	uint32_t oRs1;
	uint32_t iRs2;
	uint32_t oRs2;
	uint32_t iRd;
	uint32_t oRd;

	uint32_t iMdata;
	uint32_t oMdata;
	uint32_t iALUout;
	uint32_t oALUout;
	 
} MEMWB_PIPELINE_REGISTER_VAL;


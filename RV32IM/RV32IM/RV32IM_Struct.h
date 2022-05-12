
/*---------------------------------------------------------------------------*\
 SPLP		 : Software PipeLined Processor
 Composed By : Sim, Mong Tee
 Dated		 : 26th September 2018
 Copyright   : (C) 2018, Mong
 ==============================================================================
 History
 =======

 Author Date       Description
 ------ ---------- ------------------------------------------------------------
  Mong  09/26/2018 Initial 

\*---------------------------------------------------------------------------*/

#ifndef __SPLP_Struct_H__
#define __SPLP_Struct_H__

typedef struct PROGRAM_COUNTER
{
	uint32_t	pc;
	uint32_t	pcPlus4;	

} PROGRAM_COUNTER;

typedef struct IF_STAGE_REGISTER
{
	uint32_t	instr; 
	uint32_t	pc;
	uint32_t	pcPlus4;

} IF_STAGE_REGISTER;

typedef struct ID_STAGE_REGISTER
{
	uint32_t	instr;
	uint32_t	pc;
	uint32_t	pcPlus4;
	uint32_t	rd;
	uint32_t	rs1;
	uint32_t	rs2;
	uint32_t	rs1Data;
	uint32_t	rs2Data;
	uint32_t	branch;
	uint32_t    brnInstr;
	uint32_t	CEX;
	uint32_t	CMEM;
	uint32_t	CWB;
	uint32_t	write;
	uint32_t	extData;
	uint32_t	formatType;
	uint32_t    signExt;
	uint32_t    rdFlag;
	uint32_t    ebreak;

} ID_STAGE_REGISTER;

typedef struct EX_STAGE_REGISTER
{
	uint32_t	instr;
	uint32_t	pc;
	uint32_t	pcPlus4;
	uint32_t	branch;
	uint32_t	aluOut;	
	uint32_t	rd;
	uint32_t    rs2Data;
	uint32_t    mData;
	uint32_t	CEX;
	uint32_t	CMEM;
	uint32_t	CWB;
	uint32_t    ebreak;


} EX_STAGE_REGISTER;

typedef struct MEM_STAGE_REGISTER
{
	uint32_t	instr;
	uint32_t	rd;
	uint32_t	pcPlus4;
	uint32_t	mData; 
	uint32_t	aluOut;
	uint32_t	CWB;
	
} MEM_STAGE_REGISTER;

typedef struct WB_STAGE_REGISTER
{
	uint32_t	instr;
	uint32_t	pcPlus4;
	uint32_t	wbData; 
	uint32_t	write;	
	uint32_t    wbReg;
	uint32_t	CWB;

} WB_STAGE_REGISTER;

//=============================================================================


//---User defined
//
typedef struct PERFORMANCE_COUNTER
{
	uint64_t dataHazardCnt;
	uint64_t jalCnt;
	uint64_t jalrCnt;
	uint64_t brnTaken;
	uint64_t brnNotTaken;
	uint64_t instrCnt;

	uint64_t rdCycle;
	uint64_t rdTime;
	uint64_t rdInstret;

} PERFORMANCE_COUNTER;

//---User defined
//
typedef struct B2BDATAHAZARD_PIPELINE_REGISTER
{
	uint32_t rd;
	uint32_t data;
	uint32_t rdFlag;

} B2BDATAHAZARD_PIPELINE_REGISTER;


#endif

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


#ifndef __SPLP_Def_H__
#define __SPLP_Def_H__

//--- Memory Mapping

#define MAINMEM			(512*1024)
#define DMEM_START		0x00000
#define DMEM_END		MAINMEM
#define MASK128K		0x1FFFF
#define MASK4K			0x00FFF
#define MASK1K          0x03FF
#define MASK256			0x0FF

#define PERIPHERAL		0xC0000000
#define DEVICE_BSIZE	0x0100

#define UART0_START		PERIPHERAL 
#define UART0_DATA		(PERIPHERAL + 0)
#define UART0_TXRDY		(PERIPHERAL + 4)
#define UART0_RXRDY		(PERIPHERAL + 8)
#define UART0_END		(PERIPHERAL + (1 * DEVICE_BSIZE))

#define NORMAL			0
#define DISABLE			0
#define HALT			1
#define ENABLE			1
#define RESET			1
#define STALL			2
#define HIT				3
#define WRITE			4
#define READ			5
#define EXTEN			6

#define RFORMAT			0
#define SFORMAT			1
#define IFORMAT			2
#define BFORMAT			3
#define UFORMAT			4
#define JFORMAT			5

//-----------------------------------------------------------------------------
// ID Stage
//
#define	PCPLUS4			1
#define RS2REG			2
#define RDREG			3
#define REG31			4
#define SHIFT12			5


//-----------------------------------------------------------------------------
// EX Stage
//
#define	ALU_BEQ			1
#define ALU_BNE			2
#define ALU_BLT			3
#define ALU_BGE			4
#define ALU_BLTU		5
#define ALU_BGEU		6

#define ALU_ADDI		7
#define ALU_SLTI		8
#define ALU_SLTIU		9
#define ALU_XORI		10
#define ALU_ORI			11
#define ALU_ANDI		12
#define ALU_SLLI		13
#define ALU_SRLI		14
#define ALU_SRAI		15
#define ALU_ADD			16
#define ALU_SUB			17
#define ALU_SLL			18
#define ALU_SLT         19 
#define ALU_SLTU		20 
#define ALU_XOR			21 
#define ALU_SRL			22 
#define ALU_SRA			23 
#define ALU_OR			24 
#define ALU_AND			25 
#define ALU_AUI			26 
#define ALU_AUIPC		27
#define ALU_JAL			28
#define ALU_JALR		29
#define ALU_SBR			30
#define ALU_UBR			31

#define ALU_MUL 		32
#define ALU_MULH 		33
#define ALU_MULHSU		34
#define ALU_MULHU		35
#define ALU_DIV 		36
#define ALU_DIVU 		37
#define ALU_REM 		38
#define ALU_REMU 		39

#define ALU_CCL			40
#define ALU_CCH			41
#define ALU_TML			42
#define ALU_TMH			43
#define ALU_INSTL		44
#define ALU_INSTH		45

#define ALU_WMEM		46
#define ALU_RMEM		47
#define ALU_SW			48



//-----------------------------------------------------------------------------
// MEM Stage
//
#define MEM_LB			1
#define MEM_LH			2
#define MEM_LW			3
#define MEM_LBU			4
#define MEM_LHU			5
#define MEM_SB			6
#define MEM_SH			7
#define MEM_SW			8

// Jump or Branch
#define MEM_JMP_BR		1



//-----------------------------------------------------------------------------
// WB Stage
//
#define WB_ALUOUT		1
#define WB_MDATA		2
#define WB_PCPLUS4		3


#endif
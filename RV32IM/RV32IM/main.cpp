
/*---------------------------------------------------------------------------*\
 SPLP		 : Software PipeLined Processor
 Composed By : Sim, Mong Tee
 Dated		 : 26th September 2018
 Copyright   : (C) 2018--2022, Mong
 ==============================================================================
 History
 =======

 Author Date       Description
 ------ ---------- ------------------------------------------------------------
  Mong  09/26/2018 Initial
  Mong  10/10/2018 Add all logical and boolean operation
  Mong  01/09/2022 Change pipelined CPU to single cycle CPU (RV32IM)

\*---------------------------------------------------------------------------*/

#include "stdafx.h"

SPLP CPU0;

int main(int argc, char* argv[])
{
	printf("\n\nRISC-V RV32IM Single Cycle CPU, (C) Copyright 2018-2022, Mong\n\n");
	CPU0.PrintDateTime();

	if (argc < 2 || argc > 3)
	{
		printf(" Usage: RV32IM <file nme> <1: Disassemble 0: Normal> \n");
	}

	if (argc > 2)
		CPU0.Dissembler_flag = atoi(argv[2]);
	CPU0.LoadInstr(argv[1]);
	CPU0.Core(RESET);
	return 0;
}


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

#include "stdafx.h"

#ifndef __SPLP_H__
#define __SPLP_H__

class SPLP  
{
	private:

	public:

		uint32_t mainMemory[(MAINMEM/4)];

		//--- CPU Variables
		//
		uint32_t						pgmBREAK;
		PROGRAM_COUNTER					PC_Val;
		uint32_t						X[32];
		PERFORMANCE_COUNTER				PF_Cnt;

		//--- CPU Stage Registers
		//
		IF_STAGE_REGISTER				IF_StageVal;
		ID_STAGE_REGISTER				ID_StageVal;
		EX_STAGE_REGISTER				EX_StageVal;
		MEM_STAGE_REGISTER				MEM_StageVal;
		WB_STAGE_REGISTER				WB_StageVal;

		SPLP();
	   ~SPLP();

		//--- The Core
		//
		uint32_t	Core				(uint32_t rst);
		uint32_t    Dissembler_flag;

		//--- CPU Stages
		//
	    void	    ProgramCounter		(uint32_t rst);
		void		IF_Stage			(void);
		void		ID_Stage			(void);
		void		EX_Stage			(void);
		void		MEM_Stage			(void);
		void		WB_Stage			(void);
 
		//--- CPU Function Methods
		//
		void		ImmediateExt		(void);
		uint32_t	SystemRegister		(void); 
		void    	Control				(void);
		void		LoadInstr			(char* fname);

		void		DataBus				(uint32_t dataIn, uint32_t* dataOut, uint32_t addr, uint32_t ctrl);
		void		DCacheMemory        (uint32_t addr, uint32_t ctrl);
		void		Dissembler			(uint32_t pc, uint32_t instr);
		void		UART0    			(uint8_t *byte, uint32_t address);
		int32_t		ImmSignExt			(uint32_t signBit, uint32_t immExt, uint32_t pc);
		void		ClearFlag			(void);
		void		PrintDateTime		(void);


		char* GetRegisterName(int reg);
};

#endif
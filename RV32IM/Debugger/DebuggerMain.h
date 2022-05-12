#ifndef DebuggerMain_H
#define DebuggerMain_H

#include <cstdint>


uint32_t debugMain(uint32_t PC, uint32_t debugInstr, uint32_t* mainMemory, uint32_t* reg);
void ss();
void sbp(uint32_t, uint32_t* );
void cbp();
void pbp();
void run();

void Dissembler(uint32_t pc, uint32_t instr);
char* GetRegisterName(int reg);


#endif

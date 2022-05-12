#include <stdint.h>
#include <stdio.h>

class brakeTable
{
public:
	int counter;
	uint32_t instr;
	uint32_t PC;

	brakeTable()
	{
		counter = 0;
		instr = 0;
		PC = 0;
	}

	brakeTable(int counter, uint32_t instr, uint32_t PC)
	{
		this->counter = counter;
		this->instr = instr;
		this->PC = PC;
	}
};
#include <stdint.h>
#include <stdio.h>
#include <iostream>

#include "..\\Debugger\\brakeTable.cpp"
#include "..\\RV32IM\\stdafx.h"

// ---------------------------------------------------------------------------
// Name			Date			Discription
// ---------------------------------------------------------------------------
// Andrew S.	04/13/2022		Written to include the following Commands
//								ss (Single Step)
//								sbp <addr> (Set break point at a given addr)
//								cbp <1,2,all> (Clear break point)
//								pbp (Print break points)
//								run (run the program as normal)
// ---------------------------------------------------------------------------
// Andrew S.	04/19/2022		DebugMain should retrun the correct instr
//								which will be set to the IF_StageVal.instr
//								so ID and on execute the correct instr instead
//								of using the EBREAK that is set in the code
// ---------------------------------------------------------------------------

using namespace std;

uint32_t debugMain(uint32_t PC, uint32_t debugInstr, uint32_t * mainMemory, uint32_t * reg)
{
	// ask for command in, loop until ss or run is called and act accordingly
	bool stop = true;
	static bool ssFlag = 0;
	string userCommand = "";
	uint32_t userAddress = 0;
	uint32_t actualInstr = debugInstr;
	int tableLocation = -1;

	// Use static to have the array of break points saved between function calls :)
	static int counter = 1;
	static brakeTable EBrakes[64];
	if (counter == 1)
	{
		EBrakes[0].counter = counter;
		EBrakes[0].instr = debugInstr;
		EBrakes[0].PC = PC;
		counter++;
	}


	//Printing PC_address, System Registers, C code, Assembly Code
	printf("Break Point Reached\n");
	printf("----------------------------------------------------\n");
	printf("PC_address: %u\n", PC);
	printf("----------------------------------------------------\n");
	printf("System Registers:\n");
	printf("-----------------\n");
	printf("Zero: %08x,\t ra: %08x,\t sp: %08x,\t gp: %08x\n", reg[0], reg[1], reg[2], reg[3]);
	printf("tp: %08x,\t t0: %08x,\t t1: %08x,\t t2: %08x\n", reg[4], reg[5], reg[6], reg[7]);
	printf("fp: %08x,\t s1: %08x,\t a0: %08x,\t a1: %08x\n", reg[8], reg[9], reg[10], reg[11]);
	printf("a2: %08x,\t a3: %08x,\t a4: %08x,\t a5: %08x\n", reg[12], reg[13], reg[14], reg[15]);
	printf("a6: %08x,\t a7: %08x,\t s2: %08x,\t s3: %08x\n", reg[16], reg[17], reg[18], reg[19]);
	printf("s4: %08x,\t s5: %08x,\t s6: %08x,\t s7: %08x\n", reg[20], reg[21], reg[22], reg[23]);
	printf("s8: %08x,\t s9: %08x,\t s10: %08x,\t s11: %08x\n", reg[24], reg[25], reg[26], reg[27]);
	printf("t3: %08x,\t t4: %08x,\t t5: %08x,\t t6: %08x\n", reg[28], reg[29], reg[30], reg[31]);
	printf("----------------------------------------------------\n");
	printf("C Code:\n");
	printf("-------\n");
	// AHHH, This sounds like a lot :0  Come back if I have time
	printf("\n");
	printf("----------------------------------------------------\n");
	printf("Assembly Code:\n");
	printf("--------------\n");
	// FOR dissembler, find the PC address in the table, if present, start with that instr, otherwise
	// Print the debugInstr, which will be an ebreak.
	for (int i = 0; i < 64; i++)
	{
		if (PC == EBrakes[i].PC)
		{
			actualInstr = EBrakes[i].instr;
			tableLocation = i;
			i = 64;
		}
	}
	Dissembler(PC, actualInstr);
	printf("----------------------------------------------------\n");
	printf("\n\n");


	if (ssFlag == 1)
	{
		for (int i = 1; i < 64; i++)
		{
			if (EBrakes[i].counter == 0)
			{
				mainMemory[EBrakes[(i - 1)].PC / 4] = EBrakes[(i - 1)].instr;

				EBrakes[(i - 1)].instr = 0;
				EBrakes[(i - 1)].counter = 0;
				EBrakes[(i - 1)].PC = 0;
				counter--;
			}
		}
		ssFlag = 0;
	}
	


	while (stop)
	{
		printf("Enter a command : ");

		//cin.getline(userCommand, 10);
		std::cin >> userCommand;
		if (userCommand == "sbp")
		{
			std::cin >> userAddress;
			if (userAddress % 4 == 0)
			{
				EBrakes[counter].instr = mainMemory[userAddress / 4];
				EBrakes[counter].counter = counter;
				EBrakes[counter].PC = userAddress;
				counter++;

				mainMemory[userAddress / 4] = 0x00100073;
			}
			else
			{
				printf("Error, %x is not a vaild address", userAddress);
			}
		}


		else if (userCommand == "cbp")
		{
			// For now I am assuming all to be cleared
			for (counter; counter > 1; counter--)
			{
				EBrakes[counter].instr = 0;
				EBrakes[counter].counter = 0;
				EBrakes[counter].PC = 0;
			}
		}


		else if (userCommand == "ss")
		{
			ssFlag = 1;
			EBrakes[counter].instr = mainMemory[(PC+4) / 4];
			EBrakes[counter].counter = counter;
			EBrakes[counter].PC = (PC + 4);
			counter++;

			mainMemory[userAddress / 4] = 0x00100073;

			stop = false;
		}


		else if (userCommand == "pbp")
		{
			printf("Num\tPC\tinstr\n");
			printf("---------------------------------------\n");
			for (int i = 0; i < 64; i++)
			{
				if (EBrakes[i].counter != 0)
				{
					printf("%d\t%x\t%08x\n", EBrakes[i].counter, EBrakes[i].PC, EBrakes[i].instr);
				}
			}
			printf("---------------------------------------\n");
		}


		else if (userCommand == "run")
		{
			stop = false;
		}


		else
		{
			std::cout << "Error, " << userCommand << " isn't a valid command. Try one of the following:" << std::endl;
			printf("ss (Single Step)\n");
			printf("sbp <addr> (Set Break point)\n");
			printf("cbp (Clear all break points)\n");
			printf("pbp (Print break Points)\n");
			printf("run (run Program)\n\n");
		}



	}
	
	// Return the correct instr
	if (tableLocation == -1)
	{
		//This means an Ebreak instr was hit, just return that
		return mainMemory[(PC / 4)];
	}
	else 
	{
		//This means one of our EBrakes was hit, and the correct instr needs to be passed back
		return EBrakes[tableLocation].instr;
	}
}

// Single Step through the program to the next instruction and break again
void ss() 
{
	//place ebreak at next instr temp, and run
}


// Set break point at a given address. Store the normal instruction in a table and
// replace that spot with an ebreak instruction
void sbp(uint32_t addr, uint32_t* mainMemory)
{
	
	
}


// Clear break point based on table value given, or all for all values
void cbp(string bpValue) //berak point Value
{

}


// Print out a table of all the break points and their number assigned to them
void pbp()
{

}


// Set the program back to running normally
void run()
{
	// Set IF_Stage instr back to correct values based on my table, then exit my code
}


//-----------------------------------------------------------------------------
// Dissembler
//-----------------------------------------------------------------------------
void Dissembler(uint32_t pc, uint32_t instr)
{
	// These were from the RISC-V Card provided on canvas

	const int RType = 51;	// 0110011
	const int IType1 = 19;	// 0010011
	const int IType2 = 3;	// 0000011
	const int IType3 = 115;	// 1110011
	const int IType4 = 103;	// 1100111
	const int SType = 35;	// 0100011
	const int BType = 99;	// 1100011
	const int UType = 55;	// 0110111
	const int UType2 = 23;	// 0010111
	const int JType = 111;	// 1101111


	// Print out the location address and instruction. 
	printf_s("\t%x:\t%08x\t", pc, instr);

	int Opcode = (instr & 127); // opcode last 7 digits   *No check for compressed data*
	int rd;
	int funct3;
	int rs1;
	int rs2;
	int funct7;
	int imm;

	switch (Opcode)
	{
	case RType:
		//printf_s("R Type\t%07d", (Opcode));
		rd = ((instr >> 7) & 0b11111);
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		rs2 = ((instr >> 20) & 0b11111);
		funct7 = ((instr >> 25) & 0b1111111);

		switch (funct3)
		{
		case 0x0:
			if (funct7 == 0x00) {
				//ADD rd = rs1 + rs2
				printf("add\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else if (funct7 == 0x20) {
				//SUB rd = rs1 - rs2
				printf("sub\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else if (funct7 == 0x01) {
				// mul rd = rs1 * rs2
				printf("mul\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x4:
			// XOR rd = rs1 ^ rs2
			if (funct7 == 0x00) {
				printf("xor\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else if (funct7 == 0x01) {
				// div rd = rs1 / rs2
				printf("div\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x6:
			// OR rd = rs1 | rs2
			if (funct7 == 0x00) {
				printf("or\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else if (funct7 == 0x01) {
				// rem rd = rs1 / rs2
				printf("rem\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x7:
			// AND rd = rs1 & rs2
			if (funct7 == 0x00) {
				printf("and\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x1:
			// SHIFT LEFT Logical rd = rs1 << rs2
			if (funct7 == 0x00) {
				printf("sll\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x5:
			if (funct7 == 0x00) {
				// SHIFT RIGHT LOGICAL rd = rs1 >> rs2
				printf("srl\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else if (funct7 == 0x20) {
				// SHIFT RIGHT ARITH rd = rs1 >> rs2   *msb-extends
				printf("sra\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x2:
			//Set less than  rd = (rs1 < rs2)?1:0
			if (funct7 == 0x00) {
				printf("slt\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x3:
			//Set less than (u)    rd = (rs1 < rs2)?1:0    *Zero-extends
			if (funct7 == 0x00) {
				printf("sltu\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName(rs2));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		default:
			printf("ERROR: Opcode is RType, but couldnt match a funct3\n\tOpcode: %b\tfunct3: %b\tfunct7: %b", Opcode, funct3, funct7);
			std::cin.get();
		}
		break;


	case IType1:
		rd = ((instr >> 7) & 0b11111);
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		imm = ((instr >> 20) & 0b111111111111);
		// Correcting for negative numbers
		if ((imm >> 11) == 1)
		{
			imm = ((imm ^ 0b111111111111) + 1) * -1;
		}
		switch (funct3)
		{
		case 0x0:
			//addi rd = rs1 + imm
			printf("addi\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		case 0x4:
			//xori rd = rs1 ^ imm
			printf("xori\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		case 0x6:
			//ori  rd = rs1 | imm
			printf("ori\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		case 0x7:
			//andi rd = rs1 & imm
			printf("andi\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		case 0x1:
			//slli rd = rs1 << imm[0:4]
			if ((imm & 0b111111100000) == 0x00) {
				printf("slli\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName((imm & 0b11111)));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x5:
			if ((imm & 0b111111100000) == 0x00) {
				//srli rd = rs1 >> imm[0:4]
				printf("srli\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName((imm & 0b11111)));
			}
			else if ((imm & 0b111111100000) == 0x20) {
				//rsai rd = rs1 >> imm[0:4]
				printf("rsai\t%s,%s,%s", GetRegisterName(rd), GetRegisterName(rs1), GetRegisterName((imm & 0b11111)));
			}
			else {
				printf("Error: Unknown");
				std::cin.get();
			}
			break;
		case 0x2:
			//slti rd = (rs1 < imm)?1:0
			printf("slti\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		case 0x3:
			//sltiu rd = (rs1 < imm)?1:0
			printf("sltiu\t%s,%s,%d", GetRegisterName(rd), GetRegisterName(rs1), imm);
			break;
		default:
			printf("ERROR: Opcode is IType1, but couldnt match a funct3\n\tOpcode: %b\tra1: %b\timm: %b", Opcode, rs1, imm);
			std::cin.get();
		}

		break;


	case IType2:
		rd = ((instr >> 7) & 0b11111);
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		imm = ((instr >> 20) & 0b111111111111);

		switch (funct3)
		{
		case 0x0:
			// lb rd = M[rs1+imm][0:7]
			printf("lb\t%s,%d(%s)", GetRegisterName(rd), imm, GetRegisterName(rs1));
			break;
		case 0x1:
			// lh rd = M[rs1+imm][0:15]
			printf("lh\t%s,%d(%s)", GetRegisterName(rd), imm, GetRegisterName(rs1));
			break;
		case 0x2:
			// lw rd = M[rs1+imm][0:31]
			printf("lw\t%s,%d(%s)", GetRegisterName(rd), imm, GetRegisterName(rs1));
			break;
		case 0x4:
			// lbu rd = M[rs1+imm][0:7]
			printf("lbu\t%s,%d(%s)", GetRegisterName(rd), imm, GetRegisterName(rs1));
			break;
		case 0x5:
			// lhu rd = M[rs1+imm][0:15]
			printf("lhu\t%s,%d(%s)", GetRegisterName(rd), imm, GetRegisterName(rs1));
			break;
		default:
			printf("ERROR: Opcode is IType2, but couldnt match a funct3\n\tOpcode: %b\trs1: %b\timm: %b", Opcode, rs1, imm);
			std::cin.get();
		}
		break;


	case IType3:
		rd = ((instr >> 7) & 0b11111);
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		imm = ((instr >> 20) & 0b111111111111);

		if ((funct3 == 0x0) && (imm == 0x0)) {
			// ecall (Transfer control to OS
			printf("ecall");
		}
		else if ((funct3 == 0x0) && (imm == 0x1)) {
			// ebreak Transfer conrol to debugger
			printf("ebreak");
		}
		else if ((funct3 == 0x2) && (imm == 0xc00)) {
			// rdcycle rd
			printf("rdcycle\t%s", GetRegisterName(rd));
		}
		else if ((funct3 == 0x2) && (imm == 0xc02)) {
			// rdinstret rd
			printf("rdinstret\t%s", GetRegisterName(rd));
		}
		else {
			printf("ERROR: Opcode is IType3, but couldnt match a funct3\n\tOpcode: %b\trs1: %b\timm: %b", Opcode, rs1, imm);
			std::cin.get();
		}
		break;


	case IType4:
		rd = ((instr >> 7) & 0b11111);
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		imm = ((instr >> 20) & 0b111111111111);

		if (funct3 == 0x0) {
			// jalr rd = PC+4; PC = rs1 + imm
			printf("jalr\t%s,%d", GetRegisterName(rd), (rs1 + imm + 4));
		}
		else {
			printf("ERROR: Opcode is IType4, but couldnt match a funct3\n\tOpcode: %b\trs1: %b\timm: %b", Opcode, rs1, imm);
			std::cin.get();
		}
		break;


	case SType:
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		rs2 = ((instr >> 20) & 0b11111);
		imm = ((instr >> 7) & 0b11111) + (((instr >> 25) & 0b1111111) << 5);

		switch (funct3)
		{
		case 0x0:
			//sb M[rs1+imm][0:7] = rs2[0:7]
			printf("sb\t%s,%d(%s)", GetRegisterName(rs2), imm, GetRegisterName(rs1));
			break;
		case 0x1:
			//sh M[rs1+imm][0:15] = rs2[0:15]
			printf("sh\t%s,%d(%s)", GetRegisterName(rs2), imm, GetRegisterName(rs1));
			break;
		case 0x2:
			//sw M[rs1+imm][0:31] = rs2[0:31]
			printf("sw\t%s,%d(%s)", GetRegisterName(rs2), imm, GetRegisterName(rs1));
			break;
		default:
			printf("ERROR: Opcode is SType, but couldnt match a funct3\n\tOpcode: %b\trs1: %b\timm: %b", Opcode, rs1, imm);
			std::cin.get();
		}
		break;


	case BType:
		funct3 = ((instr >> 12) & 0b111);
		rs1 = ((instr >> 15) & 0b11111);
		rs2 = ((instr >> 20) & 0b11111);
		imm = ((((instr >> 7) & 0b1) << 11) | (((instr >> 8) & 0b1111) << 1) | (((instr >> 25) & 0b111111) << 5) | (((instr >> 31) & 0b1) << 12));

		// Since imm is signed, check first bit, if 1 then make a negitive
		if (imm >> 12 == 1) {
			imm = ((imm ^ 0b1111111111111) + 1) * -1;
		}
		switch (funct3)
		{
		case 0x0:
			// beq if (rs1 == rs2) PC+=imm
			printf("sw\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		case 0x1:
			//bne if (rs1 != rs2) PC+=imm
			printf("bne\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		case 0x4:
			//blt iff (rs1 < rs2) PC+=imm
			printf("blt\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		case 0x5:
			//brt if (rs1 >= rs2) PC +=imm
			printf("brt\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		case 0x6:
			//bltu if (rs1 < rs2) PC+=imm    *Zero extends
			printf("bltu\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		case 0x7:
			//bgue if (rs1 >= rs2) PC+=imm   *Zero extends
			printf("bgeu\t%s,%s,%x", GetRegisterName(rs1), GetRegisterName(rs2), (imm + pc));
			break;
		default:
			printf("ERROR: Opcode is BType, but couldnt match a funct3\n\tfunct3: %x", funct3);
			std::cin.get();
		}
		break;


	case UType:
		rd = ((instr >> 7) & 0b11111);
		imm = ((instr >> 12));
		// lui rd = imm << 12
		printf("lui\t%s,%x", GetRegisterName(rd), imm);
		break;


	case UType2:
		rd = ((instr >> 7) & 0b11111);
		imm = ((instr >> 12));
		// auipc rd = pc + imm<<12
		printf("auipc\t%s,%x", GetRegisterName(rd), (imm + pc));
		break;


	case JType:
		rd = ((instr >> 7) & 0b11111);
		imm = ((((instr >> 31) & 0b1) << 20) | (((instr >> 12) & 0b11111111) << 19) | (((instr >> 20) & 0b1) << 11) | (((instr >> 21) & 0b1111111111) << 1));
		printf("j\t%x", (imm + pc));
		break;


	default:
		printf_s("ERROR: Oppcode dosn't fit a preset type\t%07d", (Opcode));
		std::cin.get();
	}

	printf("\n");
}

//-----------------------------------------------------------------------------
// Get Register Name
// -------------------
// Given a register number (int), return the register name as a string
// 
// ** I added a prototype for this function at the top of the file **
//-----------------------------------------------------------------------------
char* GetRegisterName(int reg)
{
	switch (reg)
	{
	case 0:
		return "zero";
	case 1:
		return "ra";
	case 2:
		return "sp";
	case 3:
		return "gp";
	case 4:
		return "tp";
	case 5:
		return "t0";
	case 6:
		return "t1";
	case 7:
		return "t2";
	case 8:
		return "s0"; // or fp (frame pointer)
	case 9:
		return "s1";
	case 10:
		return "a0";
	case 11:
		return "a1";
	case 12:
		return "a2";
	case 13:
		return "a3";
	case 14:
		return "a4";
	case 15:
		return "a5";
	case 16:
		return "a6";
	case 17:
		return "a7";
	case 18:
		return "s2";
	case 19:
		return "s3";
	case 20:
		return "s4";
	case 21:
		return "s5";
	case 22:
		return "s6";
	case 23:
		return "s7";
	case 24:
		return "s8";
	case 25:
		return "s9";
	case 26:
		return "s10";
	case 27:
		return "s11";
	case 28:
		return "t3";
	case 29:
		return "t4";
	case 30:
		return "t5";
	case 31:
		return "t6";
	default:
		printf("\n\nERROR: %d not found in the register function\n\n", reg);
		std::cin.get();
		return "ERROR";
	}
}
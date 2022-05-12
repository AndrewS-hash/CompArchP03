
/*---------------------------------------------------------------------------*\
 boot.asm		: boot core for RISC-V  
 Composed by	: Sim, Mong Tee
 Dated			: 23rd October 2018 
 Version 		: 0.0 (C) 2018 
  
 History 
 ======= 
 Author Date     Descriptions
 ------ -------- --------------------------------------------------------------
 Mong   10232018 Initial release

\*---------------------------------------------------------------------------*/


ENTRY(boot)


/* Memory Section
 *
 * Configuration for 64KB of memory:
 * 
 * Instruction Memory starts at address 0.
 *
 * Data Memory ends 64KB later, at address 0x00010000 (the last
 * usable word address is 0x0000fffc).
 *
 *   Instructions :    0x00000000 -> 0x0003FFFF    ( 256KB)
 *   Data / BSS   :    0x00040000 -> 0x00077FFF    ( 224KB)
 *   Stack / Heap :    0x00078000 -> 0x0007FFFF    ( 32KB)
 * 
 *
 */

/* Sections
 *
 */

OUTPUT_FORMAT("elf32-littleriscv", 
              "elf32-littleriscv",
	          "elf32-littleriscv")
			  
OUTPUT_ARCH(riscv) 

_sp 	= 0x0007FFFC;
_start	= 0x00000000;
 

 
SECTIONS
{

	. = _start;
    . = ALIGN(16);
    
    .text :
	{
        *(.vectors)
        *(.boot)
		*(.*text*)
	}

/*	. = 0x00003800 ; */

    . = ALIGN(4);
	.data :
	{
		*(.rodata*)
		*(.data*)
	}

/*	_gp = ALIGN(16) + 0x5000;*/

	.got :
	{
		*(.got)
	}

	.sdata :
	{
		*(.*sdata*)
	}

	_bss_start = . ;

	.sbss :
	{
		*(.*sbss)
	}

	.bss :
	{
		*(.*bss)
	}

	_bss_end = . ;

/*    . = 0x10000 ;*/
}

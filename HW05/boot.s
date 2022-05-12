
#------------------------------------------------------------------------------
# boot.asm		: boot code for RISC-V  
# Composed by	: Sim, Mong Tee
# Dated			: 23rd October 2018 
# Version 		: 0.0 (C) 2018 
#  
# History 
# ======= 
# Author Date     Descriptions
# ------ -------- -------------------------------------------------------------
# Mong   10232018 Initial release
#
#------------------------------------------------------------------------------

	.text
	.balign	4
	.global	boot
	.set	noreorder,0
	
boot:
	la	    x4, _bss_start		    # Defined in linker script
	la	    x5, _bss_end   
	la      sp, _sp

$bss_clear:
	sw	    x0,  0(x4)
	addi 	x4, x4, 4
    bleu    x4, x5, $bss_clear		# Loop until BSS is cleared
$run:
	jal	    main
	nop
    nop
    nop
	ebreak    
    nop
    nop
    nop

$done:
	j	    $done
	nop
    nop
    nop
	.end    boot


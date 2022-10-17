#include "arm/sysregs.h"

#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF	// Check processor id
	cbz	x0, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	ldr x0, =SCTLR1_VALUE_MMU_DISABLED
	msr sctlr_el1, x0		// set EL1 control register
	
	ldr x0, =CPACR_VALUE
	msr cpacr_el1, x0		// Enable FP/SIMD
	
	ldr	x0, =SCTLR2_VALUE_MMU_DISABLED
	msr	sctlr_el2, x0		// set EL2 control register

	ldr	x0, =HCR_VALUE
	msr	hcr_el2, x0

	ldr	x0, =SCR_VALUE
	msr	scr_el3, x0

	ldr x0, =SPSR2_VALUE	// Load processor state
	msr spsr_el2, x0		// spsr_el2 restored on exit EL2

	ldr	x0, =SPSR3_VALUE	// Load processor state
	msr	spsr_el3, x0		// spsr_el3 restored on exit EL3

	adr x0, el1_entry		// Get Address of el1_entry
	msr elr_el2, x0			// Set Return address of EL2

	adr	x0, el2_entry		// Get Address of el2_entry
	msr	elr_el3, x0			// Set Return address of EL3

	eret					// Exit EL3 to address in link register

el2_entry:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY
	bl	kernel_main_el2		// jump to kernel_main_el2 in kernel.c

	eret					//Exit EL2 to address in link register

el1_entry:
	mov	sp, #LOW_MEMORY
	bl	kernel_main_el1		// jump to kernel_main_el1 in kernel.c
	b 	proc_hang		// should never come here
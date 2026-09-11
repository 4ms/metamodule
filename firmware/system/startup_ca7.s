.syntax unified
.cpu cortex-a7

.equ MODE_FIQ, 0x11
.equ MODE_IRQ, 0x12
.equ MODE_SVC, 0x13
.equ MODE_ABT, 0x17
.equ MODE_UND, 0x1B
.equ MODE_SYS, 0x1F

.equ GICC_BASE, 0xA0022000

.section .vector_table, "x"
.global _Reset
_Reset:
    b Reset_Handler
    b Undef_Handler 								// 0x4  Undefined Instruction 
    b SVC_Handler 									// Software Interrupt 
    b PAbt_Handler  								// 0xC  Prefetch Abort
    b DAbt_Handler 									// 0x10 Data Abort
    b . 											// 0x14 Reserved 
    b IRQ_Handler 									// 0x18 IRQ 
    b FIQ_Handler 									// 0x1C FIQ/

.section .resethandler
Reset_Handler:
	cpsid   if 										// Mask Interrupts

	mrc     p15, 0, r0, c1, c0, 0					// Read CP15 System Control register
	bic     r0, r0, #(0x1 << 12) 					// Clear I bit 12 to disable I Cache
	bic     r0, r0, #(0x1 <<  2) 					// Clear C bit  2 to disable D Cache
	bic     r0, r0, #0x1 							// Clear M bit  0 to disable MMU
	bic     r0, r0, #(0x1 << 11) 					// Clear Z bit 11 to disable branch prediction
	bic     r0, r0, #(0x1 << 13) 					// Clear V bit 13 to disable hivecs
	mcr     p15, 0, r0, c1, c0, 0 					// Write value back to CP15 System Control register
	isb
													// Configure ACTLR
	mrc     p15, 0, r0, c1, c0, 1 					// Read CP15 Auxiliary Control Register
	orr     r0, r0, #(1 <<  6) 						// Enable SMP
	mcr     p15, 0, r0, c1, c0, 1 					// Write CP15 Auxiliary Control Register

													// Set Vector Base Address Register (VBAR) to point to this application's vector table
	ldr    r0, =_Reset
	mcr    p15, 0, r0, c12, c0, 0

	ldr r4, =GICC_BASE 								// Clear all bits in GICC (disables GROUP0 and GROUP1), 
	mov r0, #0 										// this prevents jumping to non-existant vector table when we switch to FIQ mode
	str r0, [r4]

    												// FIQ stack
    msr cpsr_c, MODE_FIQ
    ldr r1, =_fiq_stack_start
    ldr sp, =_fiq_stack_end
    movw r0, #0xFEFF
    movt r0, #0xFEFF
fiq_loop:
    cmp r1, sp
    strlt r0, [r1], #4
    blt fiq_loop

   													// IRQ stack
    msr cpsr_c, MODE_IRQ
    ldr r1, =_irq_stack_start
    ldr sp, =_irq_stack_end
    movw r0, #0xF1F1
    movt r0, #0xF1F1
irq_loop:
    cmp r1, sp
    strlt r0, [r1], #4
    blt irq_loop

   													// Supervisor (SVC) stack
    msr cpsr_c, MODE_SVC
    ldr r1, =_svc_stack_start
    ldr sp, =_svc_stack_end
    movw r0, #0xF5F5
    movt r0, #0xF5F5
svc_loop:
    cmp r1, sp
    strlt r0, [r1], #4
    blt svc_loop

													// Abort-mode stack (holds the DAbt/PAbt handlers' register snapshot)
	msr cpsr_c, MODE_ABT
	ldr sp, =_abt_stack0_end

													// Undef-mode stack (holds the Undef_Handler register snapshot)
	msr cpsr_c, MODE_UND
	ldr sp, =_und_stack0_end

													// USER and SYS mode stack
	msr cpsr_c, MODE_SYS
    ldr r1, =_user_stack_start
	ldr sp, =_user_stack_end
    movw r0, #0xF0F0
    movt r0, #0xF0F0
usrsys_loop:
    cmp r1, sp
    strlt r0, [r1], #4
    blt usrsys_loop
 
    												// Initialize .bss
    mov r0, #0
    ldr r1, =_bss_start
    ldr r2, =_bss_end

bss_loop:
    cmp r1, r2
    strlt r0, [r1], #4
    blt bss_loop

	bl SystemInit 									// System and libc/cpp init
    bl __libc_init_array

	cpsie  i 										// enable irq interrupts

    bl main
    b Abort_Exception


.global aux_core_start
aux_core_start:
	cpsid   if 										// Disable Interrupts

													// Set Vector Base Address Register (VBAR) to point to this application's vector table
	ldr    r0, =_Reset
	mcr    p15, 0, r0, c12, c0, 0

	msr cpsr_c, MODE_ABT 							// Abort-mode stack (holds the DAbt/PAbt handlers' register snapshot)
	ldr sp, =_abt_stack1_end

	msr cpsr_c, MODE_UND 							// Undef-mode stack (holds the Undef_Handler register snapshot)
	ldr sp, =_und_stack1_end

	msr cpsr_c, MODE_SYS 							// Setup secondary core user/sys mode stack
	ldr r1, =_auxcore_user_stack_start
	ldr sp, =_auxcore_user_stack_end
    movw r0, #0xF2F2
    movt r0, #0xF2F2
auxcore_usrsys_loop:
    cmp r1, sp
    strlt r0, [r1], #4
    blt auxcore_usrsys_loop

	bl SystemInitAuxCore 							// System and libc/cpp init

	cpsie   i 										// Enable interrupts
	bl aux_core_main 								// Go to secondary core main code


//The CP15 SCTLR.TE bit is used to specify whether exception handlers will use ARM or Thumb.

Abort_Exception:
	b .

// Data/prefetch aborts in SYS mode are routed to mm_abort_reroute (abort_rescue.cc).
// Uses a private stack (per core). Stores crash details in mm_abort_fault_info 
// (8 words per core: addr, pc, fsr, type, spsr, count)

Undef_Handler:
	push {r0-r4}
	mrs r0, spsr
	and r0, r0, #0x1F
	cmp r0, #MODE_SYS
	bne Undef_Spin									// Spin if we crash in IRQ/FIQ/SVC mode

	mrc p15, 0, r0, c0, c0, 5						// Per-core re-entry guard
	and r0, r0, #3
	ldr r1, =mm_abort_reroute_active
	ldr r2, [r1, r0, lsl #2]
	cmp r2, #0
	bne Undef_Spin									// Spin if we fault from our fault handler
	mov r2, #1
	str r2, [r1, r0, lsl #2]

	mrs r2, spsr 									// arg1: faulting instruction: lr - 4, or lr - 2 in Thumb
	tst r2, #(1 << 5)
	subeq r1, r14, #4
	subne r1, r14, #2
	mov r0, r1 										// arg0: undef has no fault-address register: use the pc
	mov r2, #0 										// arg2: undef has no fault-status register
	mov r3, #2 										// arg3: 2 = undefined instruction
	b Abort_Reroute

Undef_Spin:
	pop {r0-r4}
	b .

PAbt_Handler:
	push {r0-r4}
	mrs r0, spsr
	and r0, r0, #0x1F
	cmp r0, #MODE_SYS
	bne PAbt_Spin									// Spin if we crash in IRQ/FIQ/SVC mode

	mrc p15, 0, r0, c0, c0, 5						// Per-core re-entry guard
	and r0, r0, #3
	ldr r1, =mm_abort_reroute_active
	ldr r2, [r1, r0, lsl #2]
	cmp r2, #0
	bne PAbt_Spin									// Spin if we fault from our fault handler
	mov r2, #1
	str r2, [r1, r0, lsl #2]

	mrc p15, 0, r0, c6, c0, 2						// arg0: IFAR (faulting address)
	sub r1, r14, #4 								// arg1: faulting instruction
	mrc p15, 0, r2, c5, c0, 1						// arg2: IFSR
	mov r3, #1 										// arg3: 1 = prefetch abort
	b Abort_Reroute

PAbt_Spin:
	pop {r0-r4}
	subs pc, r14, #4

DAbt_Handler:
	push {r0-r4}
	mrs r0, spsr
	and r0, r0, #0x1F
	cmp r0, #MODE_SYS
	bne DAbt_Spin

	mrc p15, 0, r0, c0, c0, 5						// Per-core re-entry guard
	and r0, r0, #3
	ldr r1, =mm_abort_reroute_active
	ldr r2, [r1, r0, lsl #2]
	cmp r2, #0
	bne DAbt_Spin
	mov r2, #1
	str r2, [r1, r0, lsl #2]

	mrc p15, 0, r0, c6, c0, 0						// arg0: DFAR (address whose access faulted)
	sub r1, r14, #8 								// arg1: faulting instruction
	mrc p15, 0, r2, c5, c0, 0						// arg2: DFSR
	mov r3, #0 										// arg3: 0 = data abort
	b Abort_Reroute

DAbt_Spin:
	pop {r0-r4}
	subs pc, r14, #8

Abort_Reroute:
	add sp, sp, #20 								// Drop the r0-r4 snapshot: this context is abandoned

	mrc p15, 0, r5, c0, c0, 5						// Record fault info where a debugger can always find it
	and r5, r5, #3
	ldr r4, =mm_abort_fault_info
	add r4, r4, r5, lsl #5 							// 8 words per core
	stmia r4, {r0-r3}								// [0]=addr [1]=pc [2]=fsr [3]=type
	mrs r5, spsr
	str r5, [r4, #16]								// [4]=spsr of the faulted context
	ldr r5, [r4, #20]
	add r5, r5, #1
	str r5, [r4, #20]								// [5]=count of re-routed aborts

	ldr lr, =mm_abort_reroute_entry
	mrs r4, spsr
	tst lr, #1 										// Match SPSR.T to the target's instruction set,
	biceq r4, r4, #(1 << 5)							// and clear any Thumb IT-block state
	orrne r4, r4, #(1 << 5)
	bic r4, r4, #(0x3 << 25)
	bic r4, r4, #(0x3F << 10)
	msr spsr_cxsf, r4
	bic lr, lr, #1
	subs pc, lr, #0 								// Exception-return into mm_abort_reroute_entry
													// (r0-r3 carry mm_abort_reroute's args)

mm_abort_reroute_entry: 							// Now in SYS mode. Run the rescue on a private
	mrc p15, 0, r4, c0, c0, 5						// per-core stack: the faulted thread's SP may be
	ands r4, r4, #3 								// unusable (and is abandoned regardless)
	ldr sp, =_abort_rescue_stack0_end
	ldrne sp, =_abort_rescue_stack1_end
	b mm_abort_reroute


// Useful macros for flipping pin PG9 to debug:
.equ GPIOG_MODER, 0x50008000
.equ GPIOG_BSRR, 0x50008018

DebugPinInit:
	ldr r4, =GPIOG_MODER							// Read, Modify, Write GPIO G MODE register
	ldr r0, [r4]
	bic r0, r0, #(1 << 19)							// Set/clr bits for Pin 9 to 01 (output mode) 
	orr r0, r0, #(1 << 18)
	str r0, [r4]
	bx lr

DebugPinHigh:
	ldr r4, =GPIOG_BSRR								// Output two pulses on pin PG9, then hold high during stack init
	mov r5, #(1 << 9)
	str r5, [r4] 									// Pin high
	bx lr

DebugPinLow:
	ldr r4, =GPIOG_BSRR								// Output two pulses on pin PG9, then hold high during stack init
	mov r6, #(1 << 25)
	str r6, [r4] 									// Pin low
	bx lr

// Per-core stacks for the abort handlers: a few words for the ABT-mode
// register snapshot, and a working stack for mm_abort_reroute (SafeLog +
// rescue), used instead of the faulted thread's stack.
.section .bss.abort_stacks, "aw", %nobits
.align 3
_abt_stack0_start:
	.space 256
_abt_stack0_end:
_abt_stack1_start:
	.space 256
_abt_stack1_end:
_und_stack0_start:
	.space 256
_und_stack0_end:
_und_stack1_start:
	.space 256
_und_stack1_end:
_abort_rescue_stack0_start:
	.space 2048
_abort_rescue_stack0_end:
_abort_rescue_stack1_start:
	.space 2048
_abort_rescue_stack1_end:

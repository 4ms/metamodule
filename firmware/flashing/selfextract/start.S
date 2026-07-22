// Entry point of the self-extract stub. MP1-Boot jumps here (ARM state,
// interrupts masked, MMU off) exactly as it would jump into the application.
.section .start, "ax"
.arm
.global _start
_start:
	cpsid	if
	ldr		sp, =_stack_top
	bl		stub_main
1:	b		1b

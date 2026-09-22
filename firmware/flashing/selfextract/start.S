// Entry point and CP15/MMU helpers for the self-extract stub.
// MP1-Boot jumps to _start (ARM state, interrupts masked, MMU off) exactly
// as it would jump into the application.
.section .start, "ax"
.arm
.global _start
_start:
	cpsid	if
	ldr		sp, =_stack_top
	bl		stub_main
1:	b		1b


// void mmu_on(uint32_t ttb_addr)
// Enables the MMU (flat table prepared by the C code) and the data cache so
// the extraction runs at cached-DDR speed. I-cache is already on.
.section .text
.global mmu_on
mmu_on:
	dsb
	mrc		p15, 0, r1, c1, c0, 1		// ACTLR: SMP bit must be set before the
	orr		r1, r1, #(1 << 6)			// D-cache works on Cortex-A7 (the app's
	mcr		p15, 0, r1, c1, c0, 1		// own startup also sets it)
	isb

	mov		r1, #0
	mcr		p15, 0, r1, c2, c0, 2		// TTBCR = 0: use TTBR0 for all of memory
	mcr		p15, 0, r0, c2, c0, 0		// TTBR0 = table (attr bits 0: table walks uncached)
	mov		r1, #1
	mcr		p15, 0, r1, c3, c0, 0		// DACR: domain 0 = client

	mov		r1, #0
	mcr		p15, 0, r1, c8, c7, 0		// TLBIALL
	mcr		p15, 0, r1, c7, c5, 6		// BPIALL
	dsb
	isb

	mrc		p15, 0, r1, c1, c0, 0		// SCTLR
	orr		r1, r1, #0x1				// M: MMU on
	orr		r1, r1, #0x4				// C: D-cache on
	mcr		p15, 0, r1, c1, c0, 0
	isb
	bx		lr


// void mmu_off_and_jump(uint32_t entry) __attribute__((noreturn))
// Clean+invalidate the entire data cache (all levels, by set/way), disable
// MMU and D-cache, invalidate TLB/I-cache/branch predictor, jump to entry.
// Pure assembly: after the clean, nothing may write to the stack (it would
// re-dirty a cache line that then evicts stale data after the handoff).
// The set/way walk is the canonical ARMv7 sequence (ARM ARM B2.2).
.global mmu_off_and_jump
mmu_off_and_jump:
	mov		r9, r0						// save entry point
	dsb
	mrc		p15, 1, r0, c0, c0, 1		// CLIDR
	ands	r3, r0, #0x07000000			// LoC
	mov		r3, r3, lsr #23				// LoC * 2
	beq		5f
	mov		r10, #0						// level * 2
1:	add		r2, r10, r10, lsr #1		// level * 3
	mov		r1, r0, lsr r2
	and		r1, r1, #7					// cache type at this level
	cmp		r1, #2
	blt		4f							// no data cache at this level
	mcr		p15, 2, r10, c0, c0, 0		// CSSELR: select level (data)
	isb
	mrc		p15, 1, r1, c0, c0, 0		// CCSIDR
	and		r2, r1, #7
	add		r2, r2, #4					// log2(line size)
	ldr		r4, =0x3ff
	ands	r4, r4, r1, lsr #3			// ways - 1
	clz		r5, r4						// way field shift
	ldr		r7, =0x7fff
	ands	r7, r7, r1, lsr #13			// sets - 1
2:	mov		r6, r4						// way counter
3:	orr		r11, r10, r6, lsl r5
	orr		r11, r11, r7, lsl r2
	mcr		p15, 0, r11, c7, c14, 2		// DCCISW: clean+invalidate by set/way
	subs	r6, r6, #1
	bge		3b
	subs	r7, r7, #1
	bge		2b
4:	add		r10, r10, #2
	cmp		r3, r10
	bgt		1b
5:	mov		r10, #0
	mcr		p15, 2, r10, c0, c0, 0		// CSSELR back to 0
	dsb
	isb

	mrc		p15, 0, r0, c1, c0, 0		// SCTLR
	bic		r0, r0, #0x1				// M: MMU off
	bic		r0, r0, #0x4				// C: D-cache off
	mcr		p15, 0, r0, c1, c0, 0
	isb

	mov		r0, #0
	mcr		p15, 0, r0, c8, c7, 0		// TLBIALL
	mcr		p15, 0, r0, c7, c5, 0		// ICIALLU
	mcr		p15, 0, r0, c7, c5, 6		// BPIALL
	dsb
	isb
	bx		r9

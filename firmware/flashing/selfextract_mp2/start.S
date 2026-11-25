// The MP2 self-extract stub: entry point, and turning the MMU and caches on and off.
//
// TF-A BL2 loads the boot image (this stub and the packed A35 image) and jumps to _start, in EL3
// with the MMU and caches off: the same state the A35 image starts in when a debugger loads it.
// The stub unpacks the A35 image to where it's linked (stub.c) and jumps to it in that same state.
// While unpacking, the MMU and caches are on (DDR is much slower without them).
//
// If the payload is bad, the stub hangs.

#define SCTLR_M   (1 << 0)
#define SCTLR_A   (1 << 1)
#define SCTLR_C   (1 << 2)
#define SCTLR_SA  (1 << 3)
#define SCTLR_I   (1 << 12)
#define SCTLR_WXN (1 << 19)

// Flat map of the first 4GB in 1GB blocks: one level-1 table of 4 entries (4kB granule, T0SZ = 32)
#define BLOCK       (1 << 0)
#define ATTR_DEVICE (0 << 2) // MAIR index 0
#define ATTR_NORMAL (1 << 2) // MAIR index 1
#define AP_RW       (1 << 6) // (bit 6 is RES1 in EL3)
#define SH_INNER    (3 << 8)
#define AF          (1 << 10)
#define XN          (1 << 54)

#define MAIR ((0xFF << 8) | 0x00) // index 1: normal, write-back cacheable. index 0: device-nGnRnE

// 32-bit address space, 4kB granule, cacheable inner-shareable table walks, 32-bit physical addresses
#define TCR ((1 << 31) | (1 << 23) | (3 << 12) | (1 << 10) | (1 << 8) | 32)

.section .ttb, "a"
.balign 4096
ttb:
	.quad 0x00000000 | XN | AF | AP_RW | ATTR_DEVICE | BLOCK	// peripherals
	.quad 0x40000000 | XN | AF | AP_RW | ATTR_DEVICE | BLOCK	// peripherals
	.quad 0x80000000 | AF | SH_INNER | AP_RW | ATTR_NORMAL | BLOCK	// DDR
	.quad 0															// not used

.section .start, "ax"
.global _start
_start:
	msr		daifset, #0xf
	ldr		x0, =_stack_top
	mov		sp, x0

	// The MMU setup is for EL3, where TF-A starts us. In any other EL, unpack without it (slowly)
	mrs		x19, CurrentEL
	cmp		x19, #(3 << 2)
	b.ne	1f
	bl		mmu_on
1:
	ldr		x0, =_payload_start
	bl		unpack
	cbz		x0, hang
	mov		x20, x0					// the A35 image's entry point

	// From here on, nothing may write to memory: mmu_off writes the data cache out
	cmp		x19, #(3 << 2)
	b.ne	2f
	bl		mmu_off
2:
	br		x20

hang:
	wfe
	b		hang


// Turns on the MMU and the caches
mmu_on:
	mov		x28, x30

	// TF-A turned the data cache off without emptying it. Empty it (TF-A wrote out what it loaded)
	mov		x0, #0
	bl		dcache_all

	// As the A35 image does: writable memory can be executed (TF-A sets WXN), no alignment checks
	mrs		x0, sctlr_el3
	ldr		x1, =(SCTLR_WXN | SCTLR_A | SCTLR_SA)
	bic		x0, x0, x1
	msr		sctlr_el3, x0
	isb

	adr		x0, ttb
	msr		ttbr0_el3, x0
	ldr		x0, =MAIR
	msr		mair_el3, x0
	ldr		x0, =TCR
	msr		tcr_el3, x0
	isb

	tlbi	alle3
	ic		iallu
	dsb		sy
	isb

	mrs		x0, sctlr_el3
	ldr		x1, =(SCTLR_M | SCTLR_C | SCTLR_I)
	orr		x0, x0, x1
	msr		sctlr_el3, x0
	isb
	ret		x28


// Writes the data cache out to memory, and turns the MMU and the caches off.
// Uses registers only: a write to the stack here could be left behind in the cache.
mmu_off:
	mov		x28, x30

	mrs		x0, sctlr_el3
	bic		x0, x0, #SCTLR_C
	msr		sctlr_el3, x0
	isb

	mov		x0, #1
	bl		dcache_all

	mrs		x0, sctlr_el3
	ldr		x1, =(SCTLR_M | SCTLR_I)
	bic		x0, x0, x1
	msr		sctlr_el3, x0
	isb

	tlbi	alle3
	ic		iallu
	dsb		sy
	isb
	ret		x28


// Goes through every set and way of every level of data cache (the usual loop: see the Arm ARM's
// example code for cache maintenance).
// x0 = 0: invalidate (what's in the cache is lost). x0 = 1: clean and invalidate (it's written out)
// Uses x1-x11, and no memory.
dcache_all:
	dsb		sy
	mrs		x9, clidr_el1
	ubfx	x3, x9, #24, #3			// level of coherence
	cbz		x3, 5f
	mov		x10, #0					// level * 2
1:
	add		x2, x10, x10, lsr #1	// level * 3
	lsr		x1, x9, x2
	and		x1, x1, #7				// cache type of this level
	cmp		x1, #2
	b.lo	4f						// no data cache at this level
	msr		csselr_el1, x10
	isb
	mrs		x1, ccsidr_el1
	and		x2, x1, #7
	add		x2, x2, #4				// log2(line size)
	ubfx	x4, x1, #3, #10			// ways - 1
	clz		w5, w4					// where the way number goes
	ubfx	x6, x1, #13, #15		// sets - 1
2:
	mov		x7, x6					// set counter
3:
	lsl		x8, x4, x5
	orr		w11, w10, w8			// level and way
	lsl		x8, x7, x2
	orr		w11, w11, w8			// and set
	cbz		x0, 6f
	dc		cisw, x11
	b		7f
6:
	dc		isw, x11
7:
	subs	x7, x7, #1
	b.ge	3b
	subs	x4, x4, #1
	b.ge	2b
4:
	add		x10, x10, #2
	cmp		x3, x10, lsr #1
	b.hi	1b
5:
	mov		x10, #0
	msr		csselr_el1, x10
	dsb		sy
	isb
	ret

.ltorg

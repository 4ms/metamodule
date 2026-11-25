/* The MP2 boot image: the self-extract stub, followed by the packed A35 image.
   TF-A BL2 loads it to _A35_BOOT (system/linker/memory_mp2.ld) and jumps to its start. */

OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)

INCLUDE system/linker/memory_mp2.ld

_STACK_SZ = 64K;

MEMORY
{
	/* The stack is at the top. If the packed image doesn't fit under it, linking fails */
	BOOT (rwx) : ORIGIN = _A35_BOOT, LENGTH = _A35_BOOT_SZ - _STACK_SZ
}

ENTRY(_start)

SECTIONS
{
	.text :
	{
		KEEP(*(.start))
		*(.text*)
		*(.rodata*)
		*(.data*)
		. = ALIGN(4096);
		KEEP(*(.ttb))
		. = ALIGN(8);
		KEEP(*(.payload))
	} > BOOT

	.bss (NOLOAD) :
	{
		*(.bss*)
		*(COMMON)
	} > BOOT

	_stack_top = _A35_BOOT_END;

	/* Nothing zeroes .bss before the stub runs */
	ASSERT(SIZEOF(.bss) == 0, "The self-extract stub must not use .bss")

	/DISCARD/ : { *(.eh_frame*) *(.comment) *(.note*) }
}

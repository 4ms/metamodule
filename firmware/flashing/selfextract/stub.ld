/* Self-extract stub: linked into the FWBUFFER region (see system/linker/memory.ld).
 * Load address is region base + 0x40 so mp1-boot places the 64-byte uimg
 * header at the region base, matching how the main app image is loaded.
 */
MEMORY
{
	STUB (rwx) : ORIGIN = 0xCC000040, LENGTH = 20M - 0x40
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
		. = ALIGN(4);
		KEEP(*(.payload))
	} > STUB

	.bss (NOLOAD) :
	{
		*(.bss*)
		*(COMMON)
	} > STUB

	_stack_top = ORIGIN(STUB) + LENGTH(STUB);

	/* The stub must stay self-contained: nothing zeroes .bss before stub_main runs */
	ASSERT(SIZEOF(.bss) == 0, "self-extract stub must not use .bss (nothing zeroes it)")

	/* make jprog-assets and flash-t32-assets load assets.uimg at 0xCCC00000 (see memory.ld).
	   The stub must end before that, or it will be overwritten (see asset_fs.hh) */
	ASSERT(ADDR(.bss) + SIZEOF(.bss) <= 0xCCC00000, "self-extract stub overlaps the RAM-loaded assets image")
}

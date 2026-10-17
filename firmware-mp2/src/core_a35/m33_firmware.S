// The Cortex-M33 firmware binary (built by the core_m33 ExternalProject), embedded in the
// A35 image. The A35 copies it to M33_LOAD_ADDR and starts the M33 (see main.cc).
	.section .rodata.m33_firmware, "a"
	.balign 16
	.global m33_firmware
m33_firmware:
	.incbin M33_FIRMWARE_BIN
	.global m33_firmware_end
m33_firmware_end:

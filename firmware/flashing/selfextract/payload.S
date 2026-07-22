// Embeds the LZ4-packed full firmware image (built by lz4_pack.py).
// PAYLOAD_PATH is passed on the command line by CMake.
.section .payload, "a"
.balign 4
.global _payload_start
_payload_start:
.incbin PAYLOAD_PATH

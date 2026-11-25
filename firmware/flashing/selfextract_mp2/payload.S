// The packed A35 image (made by pack_elf.py). PAYLOAD_PATH is set by CMake.
.section .payload, "a"
.balign 8
.global _payload_start
_payload_start:
.incbin PAYLOAD_PATH

# Self-extracting boot stub.
#
# Wraps the full firmware uimg (MAIN_FULL_UIMG, set by the parent) in a tiny
# LZ4 self-extractor so the image stored in NOR flash is ~40% smaller.
# MP1-Boot loads and boots the stub exactly like a normal app image.

set(PAYLOAD_LZ4 ${CMAKE_CURRENT_BINARY_DIR}/payload.lz4)

add_custom_command(
  OUTPUT ${PAYLOAD_LZ4}
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/lz4_pack.py ${MAIN_FULL_UIMG} ${PAYLOAD_LZ4}
  DEPENDS main-full-uimg ${MAIN_FULL_UIMG} ${CMAKE_CURRENT_LIST_DIR}/lz4_pack.py
  COMMENT "LZ4-packing firmware image"
  VERBATIM
)

add_executable(selfextract_stub.elf start.S stub.c splash.c payload.S)

# -mno-unaligned-access is essential: the stub runs with the MMU off, so all
# data accesses are Device memory where any unaligned access is a fault (and
# mp1-boot's exception vectors just hang). Without this flag GCC merges byte
# reads (e.g. the LZ4 match-offset field) into unaligned ldrh/ldr.
target_compile_options(selfextract_stub.elf PRIVATE
  -mcpu=cortex-a7
  -marm
  -mfloat-abi=soft
  -mno-unaligned-access
  -ffreestanding
  -fno-builtin
  -fno-stack-protector
  -Os
)

set_source_files_properties(payload.S PROPERTIES
  COMPILE_OPTIONS "-DPAYLOAD_PATH=\"${PAYLOAD_LZ4}\""
  OBJECT_DEPENDS ${PAYLOAD_LZ4}
)

target_link_options(selfextract_stub.elf PRIVATE
  -mcpu=cortex-a7
  -marm
  -mfloat-abi=soft
  -nostdlib
  -nostartfiles
  -static
  -Wl,--build-id=none
  -T${CMAKE_CURRENT_LIST_DIR}/stub.ld
)

set_target_properties(selfextract_stub.elf PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/stub.ld)

# The MP2 boot image: a self-extracting LZ4 stub around the A35 image.
#
# TF-A BL2 loads one image, to one place, of at most 16MB. The A35 image is bigger than that, and
# has two parts that go to different places (code and constants, and .data). So what TF-A loads is
# this stub, which unpacks the parts to where they're linked.
#
# MP1's version is ../selfextract. The two share the LZ4 packer and decoder.

set(PAYLOAD ${CMAKE_CURRENT_BINARY_DIR}/payload.bin)
set(BOOT_UIMG ${CMAKE_BINARY_DIR}/main.uimg)

# main_a35.elf is finished (the symbol list is in it) by the time the target is built
add_custom_command(
  OUTPUT ${PAYLOAD}
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/pack_elf.py --avoid _A35_BOOT _A35_BOOT_END $<TARGET_FILE:main_a35.elf>
          ${PAYLOAD}
  DEPENDS main_a35.elf $<TARGET_FILE:main_a35.elf> ${CMAKE_CURRENT_LIST_DIR}/pack_elf.py
          ${CMAKE_CURRENT_LIST_DIR}/../selfextract/lz4_pack.py
  COMMENT "LZ4-packing the A35 image"
  VERBATIM
)

add_executable(selfextract_stub.elf start.S stub.c payload.S)

# -mstrict-align: until the stub turns the MMU on, unaligned accesses can fault
# -mgeneral-regs-only: nothing has enabled the FPU
target_compile_options(
  selfextract_stub.elf
  PRIVATE -mstrict-align
          -mgeneral-regs-only
          -ffreestanding
          -fno-builtin
          -fno-stack-protector
          -Os
)

set_source_files_properties(
  payload.S PROPERTIES COMPILE_OPTIONS "-DPAYLOAD_PATH=\"${PAYLOAD}\"" OBJECT_DEPENDS ${PAYLOAD}
)

target_link_options(
  selfextract_stub.elf
  PRIVATE -nostdlib
          -static
          -Wl,--build-id=none
          -L${PROJECT_SOURCE_DIR}
          -T${CMAKE_CURRENT_LIST_DIR}/stub.ld
)

set_target_properties(
  selfextract_stub.elf
  PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/stub.ld;${PROJECT_SOURCE_DIR}/system/linker/memory_mp2.ld"
)

# The image TF-A loads: the stub and payload, with a uimg header that says where to load and start it
add_custom_command(
  OUTPUT ${BOOT_UIMG}
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/stub_to_uimg.py $<TARGET_FILE:selfextract_stub.elf> ${BOOT_UIMG}
  DEPENDS selfextract_stub.elf $<TARGET_FILE:selfextract_stub.elf> ${CMAKE_CURRENT_LIST_DIR}/stub_to_uimg.py
  COMMENT "Creating self-extracting uimg file"
  VERBATIM
)

add_custom_target(boot-image ALL DEPENDS ${BOOT_UIMG})

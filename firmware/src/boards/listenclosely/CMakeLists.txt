#
# Board
#

# TODO: remove fatfs
# remove CoreModules, internal pluigin manager, vcv_plugin etc

add_library(board_a7 STATIC)

target_include_directories(
  board_a7
  PRIVATE ${FWDIR}
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/fs
          ${FWDIR}/src/core_a7
          ${BOARD_SUPPORT_DIR}
          ${FWDIR}/lib/mdrivlib
          ${FWDIR}/lib/mdrivlib/target/stm32mp1
          ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
          ${FWDIR}/lib
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
)

target_sources(
  board_a7 PRIVATE ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3060.cc ${BOARD_SUPPORT_DIR}/file_browser_adaptor_stub.cc
)

set_source_files_properties(
  ${BOARD_SUPPORT_DIR}/file_browser_adaptor_stub.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)

target_compile_definitions(board_a7 PRIVATE CPPUTIL_STATIC_STRING_USE_STD_STRING)

target_link_libraries(board_a7 PRIVATE mdrivlib_interface cpputil)

set(BOARD_a7_libraries
    board_a7
    PARENT_SCOPE
)

set(METAMODULE_HEADLESS
    1
    PARENT_SCOPE
)

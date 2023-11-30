set(SD_DISK_DEV
    ""
    CACHE STRING "SD Card device (e.g. /dev/disk4)"
)

add_custom_target(
  format-sd
  COMMAND ./format-partition-sdcard.sh ${SD_DISK_DEV}
  COMMENT "Formatting and partitioning SD Card: ${SD_DISK_DEV}"
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_target(
  flash-bootloader-sd
  COMMAND make load SD_DISK_DEV=${SD_DISK_DEV}
  DEPENDS bootloader
  COMMENT "Copy bootloader to SD Card"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bootloader/mp1-boot
  VERBATIM USES_TERMINAL
)

set(MAIN_UIMG ${CMAKE_CURRENT_BINARY_DIR}/main.uimg)

add_custom_target(
  flash-app-sd
  DEPENDS main.elf
  COMMAND ./flash-app-sd.sh ${MAIN_UIMG} ${SD_DISK_DEV}
  COMMAND ./unmount.sh ${SD_DISK_DEV}
  COMMENT "Copy app to SD Card"
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_target(
  flash-dfu
  DEPENDS main.elf
  COMMAND echo "---------------------------------------------------"
  COMMAND echo "|        Flashing MetaModule via DFU USB          |"
  COMMAND echo "| You must power-up with the Encoder pushed down. |"
  COMMAND echo "|      Connect a USB cable to the MetaModule      |"
  COMMAND echo "---------------------------------------------------"
  COMMAND dfu-util -a 0 -s 0x70080000 -D ${MAIN_UIMG}
  VERBATIM USES_TERMINAL
)

add_custom_target(
  jprog
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/main.uimg
  COMMENT "Using JLinkExe to program via JTAG (Note: JLinkExe must be on your PATH)"
  COMMAND time -p JLinkExe -device STM32MP15XX_A7 -if JTAG -speed 25000 -jtagconf -1,-1 -nogui 1 -AutoConnect 1
          -CommandFile ${PROJECT_SOURCE_DIR}/flashing/program.jlink
  COMMAND ${CMAKE_COMMAND} -E echo "-----------------"
  COMMAND ${CMAKE_COMMAND} -E echo "If the longest time shown above is less than 1 second, then this failed."
  COMMAND ${CMAKE_COMMAND} -E echo
          "You must do a hard reset with the Freeze jumper installed before running this command."
  VERBATIM USES_TERMINAL
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(
  debug
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/main.uimg
  COMMAND ${CMAKE_GDB} --command=flashing/multi.gdbinit
  VERBATIM USES_TERMINAL
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(
  start-jlinkgdb
  COMMAND JLinkGDBServer -select USB=0 -device STM32MP15xx_A7 -endian little -if JTAG -speed 25000 -noir -noLocalhostOnly -nologtofile -port 3333 
  VERBATIM USES_TERMINAL
)

add_custom_target(
  start-openocd
  COMMAND openocd -f board/stm32mp15x_dk2.cfg
  VERBATIM USES_TERMINAL
)

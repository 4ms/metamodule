# Makefile by Dan Green <danngreen1@gmail.com>, public domain

USE_FEWER_MODULES ?= 0

$(info --------------------)

ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),$(VALID_BOARDS)))
	target_board = $(word 1,$(MAKECMDGOALS))
    $(info Building for MP1 M4 core, "$(target_board)" module)
else
    $(error Board not supported)
endif

target_src := src/$(target_board)
target_chip_src := src/$(target_board)

core_src = src/core_m4
hal_conf_inc = src/core_m4 

TAG := [MP1M4-$(target_board)]
BUILDDIR = $(BUILDDIR_MP1M4)/$(target_board)
LOADFILE = $(LINKSCRIPTDIR)/stm32mp15xx_m4.ld
HALDIR = $(HALBASE)/stm32mp1
DEVICEDIR = $(DEVICEBASE)/stm32mp157c
TARGETDEVICEDIR = $(DRIVERLIB)/target/stm32mp1
TARGETDEVICEDIR_CM4 = $(DRIVERLIB)/target/stm32mp1_cm4

usb_src := src/usb
usbhost_libdir = $(LIBDIR)/stm32-usb-host-lib
usbdev_libdir = $(LIBDIR)/stm32-usb-device-lib
STARTUP = system/startup_stm32mp157cxx_cm4.s
SYSTEM = $(core_src)/system_stm32mp1xx.c

SHARED = src/shared

OPTFLAG = -O3
include makefile_opts.mk


ASM_SOURCES  = $(STARTUP)

SOURCES += $(SYSTEM)
SOURCES += $(HALDIR)/src/stm32mp1xx_hal.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_adc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_adc_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_rcc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_pwr_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_tim.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_mdma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_dma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_uart.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_usart.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_cortex.c
SOURCES += src/core_intercom/shared_memory.cc
SOURCES += $(core_src)/controls.cc
SOURCES += $(core_src)/main_m4.cc
SOURCES += system/libc_stub.c
SOURCES += system/libcpp_stub.cc
SOURCES += system/new.cc
SOURCES += $(DRIVERLIB)/drivers/hal_handlers.cc
SOURCES += $(DRIVERLIB)/drivers/i2c.cc
SOURCES += $(TARGETDEVICEDIR_CM4)/drivers/interrupt_handler.cc
SOURCES += $(DRIVERLIB)/drivers/pin.cc
SOURCES += $(DRIVERLIB)/drivers/rotary.cc
SOURCES += $(DRIVERLIB)/drivers/tim.cc
SOURCES += $(DRIVERLIB)/drivers/timekeeper.cc
SOURCES += src/console/uart_log.cc
SOURCES += lib/printf/printf.c

# SD Card (FATFS):
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_sdmmc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd_ex.c
SOURCES += $(LIBDIR)/fatfs/source/ff.c
SOURCES += $(LIBDIR)/fatfs/source/ffunicode.c
SOURCES += src/fs/fatfs/diskio.cc
SOURCES += src/fs/fatfs/fattime.cc
SOURCES += src/fs/time_convert.cc

# Nor flash/LFS
SOURCES += $(LIBDIR)/littlefs/lfs.c
SOURCES += $(LIBDIR)/littlefs/lfs_util.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_qspi.c
SOURCES += $(DRIVERLIB)/drivers/qspi_flash_driver.cc


# USB:
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_usb.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_usb_phy.c

# USB Host:
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_hcd.c
SOURCES += $(usb_src)/usbh_conf.cc
SOURCES += $(usb_src)/usbh_midi.cc
# SOURCES += $(usbhost_libdir)/Class/HUB/Src/usbh_hub.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_core.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_ctlreq.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_ioreq.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_pipes.c
SOURCES += $(usbhost_libdir)/Class/MSC/Src/usbh_msc.c
SOURCES += $(usbhost_libdir)/Class/MSC/Src/usbh_msc_bot.c
SOURCES += $(usbhost_libdir)/Class/MSC/Src/usbh_msc_scsi.c

# USB Device:
SOURCES += $(usb_src)/usb_drive_device.cc
SOURCES += $(usb_src)/usbd_conf.c
SOURCES += $(usb_src)/usbd_desc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_pcd.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_pcd_ex.c
SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc.c
SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_bot.c
SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_data.c
SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_scsi.c
SOURCES += $(usbdev_libdir)/Core/Src/usbd_core.c
SOURCES += $(usbdev_libdir)/Core/Src/usbd_ctlreq.c
SOURCES += $(usbdev_libdir)/Core/Src/usbd_ioreq.c


INCLUDES = -I$(DEVICEDIR)/include \
			-I$(CMSIS)/Include \
			-I$(HALDIR)/include \
			-I$(DRIVERLIB) \
			-I$(DRIVERLIB)/drivers \
			-I$(TARGETDEVICEDIR) \
			-I$(TARGETDEVICEDIR)/drivers \
			-I$(TARGETDEVICEDIR_CM4) \
			-I$(TARGETDEVICEDIR_CM4)/drivers \
			-I$(LIBDIR)/easiglib \
			-I. \
			-Isrc \
			-Isrc/console \
			-Isrc/params \
			-I$(target_src) \
			-I$(target_chip_src) \
			-I$(core_src) \
			-I$(hal_conf_inc) \
			-Isystem \
			-I$(SHARED) \
			-I$(SHARED)/processors \
			-I$(SHARED)/CoreModules \
			-I$(SHARED)/cpputil \
			-I$(SHARED)/patch \
			-I$(LIBDIR)/fatfs/source \
			-Isrc/fs/fatfs \
			-I$(usb_src) \
			-I$(usbhost_libdir)/Core/Inc \
			-I$(usbhost_libdir)/Class/MSC/Inc \
			-I$(usbdev_libdir)/Core/Inc \
			-I$(usbdev_libdir)/Class/MSC/Inc \
			
MCU = -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard

ARCH_CFLAGS = -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CM4 \
			  -DARM_MATH_CM4

include makefile_common.mk

all: $(target_src)/firmware_m4.h $(target_src)/firmware_m4_vectors.h $(BUILDDIR)/m4_rodata.ld 

$(target_src)/firmware_m4.h: $(BUILDDIR)/firmware.bin
	cd $(dir $<) && xxd -i -c 8 $(notdir $<) ../../../$@

$(target_src)/firmware_m4_vectors.h: $(BUILDDIR)/vectors.bin
	cd $(dir $<) && xxd -i -c 8 $(notdir $<) ../../../$@

$(BUILDDIR)/vectors.bin: $(BUILDDIR)/$(BINARYNAME).elf
	arm-none-eabi-objcopy -O binary \
		-j .isr_vector \
		$< $@

$(BUILDDIR)/firmware.bin: $(BUILDDIR)/$(BINARYNAME).elf
	arm-none-eabi-objcopy -O binary \
		-j .text \
		-j .startup_copro_fw.Reset_Handler \
		-j .init_array \
		-j .data \
		$< $@

$(BUILDDIR)/m4_rodata.bin: $(BUILDDIR)/$(BINARYNAME).elf
	arm-none-eabi-objcopy -O binary -j .rodata $< $@

# $(BUILDDIR)/m4_ddr_code.bin: $(BUILDDIR)/$(BINARYNAME).elf
# 	arm-none-eabi-objcopy -O binary -j .ddr_code $< $@

# $(BUILDDIR)/m4_data.bin: $(BUILDDIR)/$(BINARYNAME).elf
# 	arm-none-eabi-objcopy -O binary -j .data $< $@
			
$(BUILDDIR)/%.ld: $(BUILDDIR)/%.bin
	cat $< | hexdump -v -e '"BYTE(0x" 1/1 "%02X" ")\n"' > $@


mini: all

medium: all

max: all

pcmdev: all


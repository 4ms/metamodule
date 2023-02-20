# Makefile by Dan Green <danngreen1@gmail.com>, public domain

USE_FEWER_MODULES ?= 0

$(info --------------------)

ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),$(VALID_BOARDS)))
	target_board = $(word 1,$(MAKECMDGOALS))
    $(info Building for MP1 M4 core, $(target_board) module)
else
    $(error Board not supported)
endif

target_src := src/$(target_board)

ifeq "$(target_board)" "mini"
	target_chip_src := src/$(target_board)/mp1
else
	target_chip_src := src/$(target_board)
endif

core_src = src/mp1m4
hal_conf_inc = src/mp1m4 

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
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_cortex.c
SOURCES += $(target_src)/controls.cc
SOURCES += $(target_chip_src)/main-m4.cc
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
SOURCES += src/uart_log.cc
SOURCES += lib/printf/printf.c

# SD Card (FATFS):
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_sdmmc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd_ex.c
SOURCES += $(LIBDIR)/fatfs/source/ff.c
SOURCES += $(LIBDIR)/fatfs/source/ffunicode.c
SOURCES += src/fatfs/diskio.cc
SOURCES += src/fatfs/fattime.cc
SOURCES += src/time_convert.cc

SOURCES += src/patch_fileio.cc

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
# SOURCES += $(usb_src)/midi_host.cc
# SOURCES += $(usbhost_libdir)/Class/HUB/Src/usbh_hub.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_core.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_ctlreq.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_ioreq.c
SOURCES += $(usbhost_libdir)/Core/Src/usbh_pipes.c

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

# yaml
# SOURCES += $(SHARED)/patch_convert/yaml_to_patch.cc
# SOURCES += $(SHARED)/patch_convert/ryml/ryml_serial.cc
# rymldir = $(SHARED)/patch_convert/ryml/rapidyaml
# SOURCES += $(wildcard $(rymldir)/src/c4/yml/*.cpp)
# SOURCES += $(wildcard $(rymldir)/ext/c4core/src/c4/*.cpp)

## LVGL / Gui-Guider
# LVGL_DIR=$(LIBDIR)/lvgl
# LVGL_DIR_NAME=lvgl
# SOURCES += $(shell find -L $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets -name \*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/others/gridnav/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/core/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/sw/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/widgets/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/font/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/misc/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/hal/*.c)

# SOURCES += src/pages/page_manager.cc
# SOURCES += src/pages/fonts/MuseoSansRounded_500_12.c
# SOURCES += src/pages/fonts/MuseoSansRounded_700_12.c
# SOURCES += src/pages/fonts/MuseoSansRounded_700_14.c
# SOURCES += src/pages/fonts/MuseoSansRounded_700_16.c
# SOURCES += src/pages/fonts/MuseoSansRounded_700_18.c

# ifeq "$(USE_FEWER_MODULES)" "1"
# SOURCES += src/pages/images/modules/Djembe_artwork_240.c
# SOURCES += src/pages/images/modules/StMix_artwork_240.c
# SOURCES += src/pages/images/modules/PEG_artwork_240.c
# SOURCES += src/pages/images/modules/SMR_artwork_240.c
# SOURCES += src/pages/images/modules/MultiLFO_artwork_240.c
# SOURCES += src/pages/images/modules/PitchShift_artwork_240.c
# SOURCES += src/pages/images/modules/HPF_artwork_240.c
# SOURCES += src/pages/images/modules/InfOsc_artwork_240.c
# SOURCES += src/pages/images/modules/KPLS_artwork_240.c
# SOURCES += src/pages/images/modules/Freeverb_artwork_240.c
# SOURCES += src/pages/images/modules/Seq8_artwork_240.c
# SOURCES += src/pages/images/modules/EnOsc_artwork_240.c

# SOURCES += src/pages/images/modules/Djembe_artwork_120.c
# SOURCES += src/pages/images/modules/StMix_artwork_120.c
# SOURCES += src/pages/images/modules/PEG_artwork_120.c
# SOURCES += src/pages/images/modules/MultiLFO_artwork_120.c
# SOURCES += src/pages/images/modules/SMR_artwork_120.c
# SOURCES += src/pages/images/modules/PitchShift_artwork_120.c
# SOURCES += src/pages/images/modules/HPF_artwork_120.c
# SOURCES += src/pages/images/modules/InfOsc_artwork_120.c
# SOURCES += src/pages/images/modules/KPLS_artwork_120.c
# SOURCES += src/pages/images/modules/Freeverb_artwork_120.c
# SOURCES += src/pages/images/modules/Seq8_artwork_120.c
# SOURCES += src/pages/images/modules/EnOsc_artwork_120.c
# else
# SOURCES += $(wildcard src/pages/images/modules/*.c)
# endif
# # SOURCES += $(wildcard src/pages/images/ui/*.c)
# SOURCES += $(wildcard src/pages/images/components/*.c)


INCLUDES =
INCLUDES += -I$(DEVICEDIR)/include 
INCLUDES += -I$(CMSIS)/Include 
INCLUDES += -I$(HALDIR)/include 
INCLUDES += -I$(DRIVERLIB) 
INCLUDES += -I$(DRIVERLIB)/drivers 
INCLUDES += -I$(TARGETDEVICEDIR) 
INCLUDES += -I$(TARGETDEVICEDIR)/drivers 
INCLUDES += -I$(TARGETDEVICEDIR_CM4) 
INCLUDES += -I$(TARGETDEVICEDIR_CM4)/drivers 
INCLUDES += -I$(LIBDIR)/easiglib 
INCLUDES += -I. 
INCLUDES += -Isrc 
INCLUDES += -I$(target_src) 
INCLUDES += -I$(target_chip_src) 
INCLUDES += -I$(core_src) 
INCLUDES += -I$(hal_conf_inc) 
INCLUDES += -Isystem 
INCLUDES += -I$(SHARED) 
INCLUDES += -I$(SHARED)/processors 
INCLUDES += -I$(SHARED)/CoreModules 
INCLUDES += -I$(SHARED)/cpputil 
INCLUDES += -I$(SHARED)/patch 
INCLUDES += -I$(LIBDIR)/fatfs/source 
INCLUDES += -Isrc/fatfs 
INCLUDES += -I$(usb_src) 
INCLUDES += -I$(usbhost_libdir)/Core/Inc 
INCLUDES += -I$(usbdev_libdir)/Class/MSC/Inc 
INCLUDES += -I$(usbdev_libdir)/Core/Inc 
INCLUDES += -I$(usbdev_libdir)/Class/HUB/Inc 
# INCLUDES +=	-I$(SHARED)/patch_convert
# INCLUDES +=	-I$(SHARED)/patch_convert/ryml
# INCLUDES += -I$(rymldir)/src
# INCLUDES += -I$(rymldir)/ext/c4core/src
INCLUDES += -I$(SHARED)/etl/include
# INCLUDES +=	-I$(LIBDIR)/lvgl

MCU = -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard

ARCH_CFLAGS = -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CM4 \
			  -DARM_MATH_CM4

include makefile_common.mk

all: $(target_src)/firmware_m4.h $(target_src)/firmware_m4_vectors.h $(BUILDDIR)/m4_ddr_code.ld $(BUILDDIR)/m4_data.ld

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
		$< $@

$(BUILDDIR)/m4_ddr_code.bin: $(BUILDDIR)/$(BINARYNAME).elf
	arm-none-eabi-objcopy -O binary -j .ddr_code $< $@

$(BUILDDIR)/m4_data.bin: $(BUILDDIR)/$(BINARYNAME).elf
	arm-none-eabi-objcopy -O binary \
		-j .rodata \
		-j .data \
		$< $@
			
$(BUILDDIR)/%.ld: $(BUILDDIR)/%.bin
	cat $< | hexdump -v -e '"BYTE(0x" 1/1 "%02X" ")\n"' > $@


mini: all

medium: all

max: all

pcmdev: all


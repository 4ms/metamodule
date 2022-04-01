#----------------------------------
# Uncomment to compile unoptimized:
# $(BUILDDIR)/src/patchlist_ryml_tests.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/patch_convert/ryml/ryml_serial.o: OPTFLAG = -O0
# $(BUILDDIR)/src/pages/page_manager.o: OPTFLAG = -O0
# $(BUILDDIR)/lib/mdrivlib/drivers/rotary.o: OPTFLAG = -O0
# $(BUILDDIR)/src/pages/page_manager.o: OPTFLAG = -O0
# $(BUILDDIR)/src/norflash-loader/main.o: OPTFLAG = -O0
$(BUILDDIR)/src/a7/main.o: OPTFLAG = -O0
$(BUILDDIR)/src/patchfileio.o: OPTFLAG = -O0
# $(BUILDDIR)/src/timekeeper.o: OPTFLAG = -O0
# $(BUILDDIR)/src/m4/main.o: OPTFLAG = -O0
# $(BUILDDIR)/src/m4/controls.o: OPTFLAG = -O0
# $(BUILDDIR)/src/screen.o: OPTFLAG = -O0
# $(BUILDDIR)/src/audio.o: OPTFLAG = -O0
# $(BUILDDIR)/src/patchlist.o: OPTFLAG = -O0
# $(BUILDDIR)/src/patchfileio.o: OPTFLAG = -O0
# $(BUILDDIR)/src/shared/patch_convert/yaml_to_patch.o: OPTFLAG = -O0
$(BUILDDIR)/src/fatfs/diskio.o: OPTFLAG = -O0
$(BUILDDIR)/src/fatfs/norflashramdisk_ops.o: OPTFLAG = -O0
# $(BUILDDIR)/lib/fatfs/source/ff.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O3
# $(BUILDDIR)/$(PERIPH)/src/stm32h7xx_hal_qspi.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/qspi_flash_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/sdram.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/system.o: OPTFLAG = -O0
# build/mp1corem4/medium/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_i2c.o: OPTFLAG = -O0
# build/mp1corea7/medium/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver_dma.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/sai.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/qspi_flash_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/lfoCore.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/fmoscCore.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/multilfoCore.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/target/stm32mp1/drivers/sai_tdm.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/target/stm32mp1/drivers/adc_builtin_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/codec_PCM3168.o: OPTFLAG = -O0
# $(BUILDDIR)/lib/mcufont/decoder/mf_kerning.o: OPTFLAG = -O0
#
# $(BUILDDIR)/lib/lvgl/lvgl/src/lv_core/%.o: OPTFLAG = -O0
# $(BUILDDIR)/lib/lvgl/lvgl/src/lv_draw/%.o: OPTFLAG = -O0
#
# $(BUILDDIR)/lib/lvgl/lvgl/src/lv_draw/%.o: OPTFLAG = -O0
#-----------------------------------

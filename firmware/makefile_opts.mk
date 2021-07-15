#----------------------------------
# Uncomment to compile unoptimized:
# $(BUILDDIR)/lib/mdrivlib/drivers/rotary.o: OPTFLAG = -O0
# $(BUILDDIR)/src/a7/main.o: OPTFLAG = -O0
# $(BUILDDIR)/src/m7/main.o: OPTFLAG = -O0
# $(BUILDDIR)/src/timekeeper.o: OPTFLAG = -O0
# $(BUILDDIR)/src/m4/main.o: OPTFLAG = -O0
# $(BUILDDIR)/src/m4/controls.o: OPTFLAG = -O0
# $(BUILDDIR)/src/screen.o: OPTFLAG = -O0
# $(BUILDDIR)/src/audio.o: OPTFLAG = -O0
# $(BUILDDIR)/src/patchlist.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O3
# $(BUILDDIR)/$(PERIPH)/src/stm32h7xx_hal_qspi.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/sdram.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/system.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/stm32h7xx_hal_i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver_dma.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/sai.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/qspi_flash_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/lfoCore.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/fmoscCore.o: OPTFLAG = -O0
# $(BUILDDIR)/$(SHARED)/CoreModules/multilfoCore.o: OPTFLAG = -O0

#FixMe: for some reason gcc uses invalid alignmet in a VST1.8 instruction (base address is aligned to 4 bytes, but instruction requires 8-byte alignment). Why?? Setting -O0 fixes it...
$(BUILDDIR)/lib/mcufont/decoder/mf_kerning.o: OPTFLAG = -O0
#-----------------------------------

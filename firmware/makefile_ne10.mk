# SOURCES += $(NE10DIR)/common/NE10_mask_table.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_rfft_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_int32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_int16.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fir.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fir_init.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_iir.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_iir_init.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.neonintrinsic.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.neonintrinsic.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_init_dsp.c

# NE10_ASM_OPTIMIZATION = 1

# ifneq ($(NE10_ASM_OPTIMIZATION),)
# SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.c \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.c \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.c \

# ASM_SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.s \

# NE10_CFLAGS = -DNE10_UNROLL_LEVEL=0
# else
# SOURCES += \
# 	$(NE10DIR)/modules/dsp/NE10_fft_float32.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_fft_int32.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_fft_int16.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_rfft_float32.neonintrinsic.c \

# NE10_CFLAGS = -DNE10_UNROLL_LEVEL=1
# endif

# ASM_SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fir.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_iir.neon.s \
# 		  $(NE10DIR)/common/NE10header.s \
# 		  $(NE10DIR)/common/versionheader.s \
# INCLUDES +=		-I$(NE10DIR)/inc
# INCLUDES +=		-I$(NE10DIR)/common
# INCLUDES +=		-I$(NE10DIR)/modules/dsp


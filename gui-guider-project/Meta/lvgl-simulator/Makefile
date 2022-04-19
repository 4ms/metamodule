# SPDX-License-Identifier: MIT
# Copyright 2020-2021 NXP
#
# Makefile
#

makefile_name := $(abspath $(lastword $(MAKEFILE_LIST)))
makefile_path := $(strip $(patsubst %/,% , $(dir $(makefile_name))))


CC := gcc
PRJ_DIR := $(makefile_path)/..
LVGL_DIR := $(PRJ_DIR)
SIMULATOR_DIR := $(makefile_path)
LVGL_DIR_NAME ?= lvgl
CFLAGS := -O3 -g0 -I$(LVGL_DIR)/ -I$(makefile_path)/ -c -fmessage-length=0
LDFLAGS := -lSDL2 -lm

BUILD_DIR := build/
OBJ_DIR := $(BUILD_DIR)object/
GEN_OBJ_DIR := $(OBJ_DIR)generated/
BIN_DIR := $(BUILD_DIR)bin/

NORMAL_OUT := 1

RM := rm -f
RMDIR := rm -rf

ifeq ($(OS),Windows_NT)
LDFLAGS += -LSDL2\i686-w64-mingw32\lib
SIMULATOR_EXE = simulator.exe
BUILD_ENV := build\object build\bin
NULL_OUT := nul
MKDIR_P = mkdir
else
SIMULATOR_EXE = simulator
NULL_OUT := /dev/null
MKDIR_P = mkdir -p
endif

CFLAGS += -DLV_CONF_INCLUDE_SIMPLE=1

#Collect the files to compile
-include $(LVGL_DIR)/lvgl/lvgl.mk
-include $(SIMULATOR_DIR)/lv_drivers/lv_drivers.mk
-include $(PRJ_DIR)/generated/generated.mk
-include $(PRJ_DIR)/custom/custom.mk

CSRCS += main.c
DEPPATH += --dep-path $(makefile_path)/
VPATH += :$(makefile_path)/
CFLAGS += "-I$(makefile_path)/"

ifeq ($(OS),Windows_NT)
#SDL2
CFLAGS += "-ISDL2\i686-w64-mingw32\include" -MMD -MP
endif

OBJEXT := .o

AOBJS = $(addprefix $(OBJ_DIR),$(ASRCS:.S=$(OBJEXT)))
COBJS = $(addprefix $(OBJ_DIR),$(CSRCS:.c=$(OBJEXT)))
DEPS = $(addprefix $(OBJ_DIR),$(CSRCS:.c=.d))
GEN_AOBJS = $(addprefix $(GEN_OBJ_DIR),$(GEN_ASRCS:.S=$(OBJEXT)))
GEN_COBJS = $(addprefix $(GEN_OBJ_DIR),$(GEN_CSRCS:.c=$(OBJEXT)))

DEPS += $(addprefix $(GEN_OBJ_DIR),$(GEN_CSRCS:.c=.d))


SRCS = $(ASRCS) $(CSRCS)
OBJS = $(AOBJS) $(COBJS)
GEN_SRCS = $(GEN_ASRCS) $(GEN_CSRCS)
GEN_OBJS = $(GEN_AOBJS) $(GEN_COBJS)

.PHONY: all env clean default cp_lib clean_gen run
ifeq ($(OS),Windows_NT)
all: env default cp_lib
else
all: env default
endif
# monitor header files
-include $(DEPS)

ifeq ($(OS),Windows_NT)
env:
	@if not exist "build/bin" $(MKDIR_P) "build/bin"
	@if not exist "build/object/generated" $(MKDIR_P) "build/object/generated"
else
env:
	@if [ ! -d "build/bin" ]; then $(MKDIR_P) build/bin; fi
	@if [ ! -d "build/object/generated" ]; then $(MKDIR_P) build/object/generated; fi
endif
$(OBJ_DIR)main.o: main.c
	@echo "Compiling $(makefile_path)/$<"
	@$(CC)  $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: %.c
	@echo "Compiling $<"
	@$(CC)  $(CFLAGS) -c $< -o $@

$(GEN_OBJ_DIR)%.o: %.c
	@echo "Compiling $<"
	@$(CC)  $(CFLAGS) -c $< -o $@

default: $(OBJS) $(GEN_OBJS)
	@echo "Linking $(SIMULATOR_EXE)"
	@$(CC) -o $(BIN_DIR)$(SIMULATOR_EXE) $(OBJS) $(GEN_OBJS) $(LDFLAGS)

cp_lib:
	-@cp SDL2/lib/SDL2.dll build/bin/SDL2.dll $(NORMAL_OUT)>$(NULL_OUT)

clean:
	-@$(RMDIR) build

gen_images := $(wildcard $(PRJ_DIR)/generated/images/*.c)
gen_srcs := $(gen_images) $(wildcard $(PRJ_DIR)/generated/*.c) $(wildcard $(PRJ_DIR)/generated/*.h)

ifeq ($(OS),Windows_NT)
clean_gen_img:
	-@rm $(gen_images)

clean_gen: clean_gen_img
	-@rm $(gen_srcs)
run:
	build\bin\simulator.exe
else

clean_gen_img:
	$(RM) $(LVGL_DIR)/generated/images/*.c

clean_gen: clean_gen_img
	$(RM) $(LVGL_DIR)/generated/*.c
	$(RM) $(LVGL_DIR)/generated/*.h

run:
	./build/bin/simulator
endif

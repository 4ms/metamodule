/**
 ******************************************************************************
 * @file    usbh_conf_template.h
 * @author  MCD Application Team
 * @brief   Header file for usbh_conf_template.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                      www.st.com/SLA0044
 *
 ******************************************************************************
 */

#ifndef __USBH_CONF_TEMPLATE_H
#define __USBH_CONF_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32mp1xx.h"
// #include <stdio.h>
// #include <stdlib.h>
#include <string.h> //for memset/memcpy

static inline void Error_Handler() {
}

#define USBH_MAX_NUM_ENDPOINTS 16U
#define USBH_MAX_NUM_INTERFACES 16U
#define USBH_MAX_NUM_CONFIGURATION 2U
#define USBH_KEEP_CFG_DESCRIPTOR 1U
#define USBH_MAX_NUM_SUPPORTED_CLASS 16U
#define USBH_MAX_SIZE_CONFIGURATION 0x200U
#define USBH_MAX_DATA_BUFFER 0x200U
#define USBH_USE_OS 0U

#define USBH_USER_LOG_OUTPUT 0
#define USBH_ERR_LOG_OUTPUT 1
#define USBH_DBG_LOG_OUTPUT 0

enum { MidiStreamingBufferSize = 256 };
enum { HOST_HS = 0, HOST_FS = 1 };

void *msc_malloc(size_t);
void msc_free(void *);
#define USBH_malloc msc_malloc
#define USBH_free msc_free
#define USBH_memset memset
#define USBH_memcpy memcpy

#if (USBH_USER_LOG_OUTPUT || USBH_ERR_LOG_OUTPUT || USBH_DBG_LOG_OUTPUT)
#include <stdio.h>
#endif

#if USBH_USER_LOG_OUTPUT
#define USBH_UsrLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBH USER: ");                                                                                         \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
	} while (0)
#else
#define USBH_UsrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if USBH_ERR_LOG_OUTPUT
#define USBH_ErrLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBH ERROR: ");                                                                                        \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
	} while (0)
#else
#define USBH_ErrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if USBH_DBG_LOG_OUTPUT
#define USBH_DbgLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBH DEBUG: ");                                                                                        \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
	} while (0)
#else
#define USBH_DbgLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __USBH_CONF_TEMPLATE_H */

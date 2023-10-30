/**
 ******************************************************************************
 * @file    usbd_conf_template.h
 * @author  MCD Application Team
 * @brief   Header file for the usbd_conf_template.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF_TEMPLATE_H
#define __USBD_CONF_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx.h"

#define USB_USB_HS // used in usbd_core.c

/** @addtogroup STM32_USB_DEVICE_LIBRARY
 * @{
 */

/** @defgroup USBD_CONF
 * @brief USB device low level driver configuration file
 * @{
 */

/** @defgroup USBD_CONF_Exported_Defines
 * @{
 */

#define USBD_MAX_NUM_INTERFACES 1U
#define USBD_MAX_NUM_CONFIGURATION 1U
#define USBD_MAX_STR_DESC_SIZ 0x100U
#define USBD_SELF_POWERED 1U
#define USBD_DEBUG_LEVEL 3U

#if (USBD_DEBUG_LEVEL > 0U)
#include <stdio.h>
#endif

/* ECM, RNDIS, DFU Class Config */
#define USBD_SUPPORT_USER_STRING_DESC 1U

/* BillBoard Class Config */
#define USBD_CLASS_USER_STRING_DESC 1U
#define USBD_CLASS_BOS_ENABLED 1U
#define USB_BB_MAX_NUM_ALT_MODE 0x2U

/* bEndpointAddress in Endpoint Descriptor */
#define UVC_IN_EP 0x81U

#define UVC_CAM_FPS_FS 10U
#define UVC_CAM_FPS_HS 5U

#define UVC_ISO_FS_MPS 512U
#define UVC_ISO_HS_MPS 512U

/* Memory management macros make sure to use static memory allocation */
/** Alias for memory allocation. */
#define USBD_malloc (void *)USBD_static_malloc

/** Alias for memory release. */
#define USBD_free USBD_static_free

/** Alias for memory set. */
#define USBD_memset memset

/** Alias for memory copy. */
#define USBD_memcpy memcpy

/** Alias for delay. */
#define USBD_Delay HAL_Delay

/* DEBUG macros */
#if (USBD_DEBUG_LEVEL > 0U)
#define USBD_UsrLog(...)                                                                                               \
	do {                                                                                                               \
		printf_(__VA_ARGS__);                                                                                          \
		printf_("\n");                                                                                                 \
	} while (0)
#else
#define USBD_UsrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 1U)

#define USBD_ErrLog(...)                                                                                               \
	do {                                                                                                               \
		printf_("ERROR: ");                                                                                            \
		printf_(__VA_ARGS__);                                                                                          \
		printf_("\n");                                                                                                 \
	} while (0)
#else
#define USBD_ErrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if (USBD_DEBUG_LEVEL > 2U)
#define USBD_DbgLog(...)                                                                                               \
	do {                                                                                                               \
		printf_("DEBUG : ");                                                                                           \
		printf_(__VA_ARGS__);                                                                                          \
		printf_("\n");                                                                                                 \
	} while (0)
#else
#define USBD_DbgLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

/**
 * @}
 */

/**
 * @}
 */

/** @defgroup USBD_CONF_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @defgroup USBD_CONF_Exported_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USBD_CONF_Exported_Variables
 * @{
 */
/**
 * @}
 */

/** @defgroup USBD_CONF_Exported_FunctionsPrototype
 * @{
 */
/* Exported functions -------------------------------------------------------*/
void *USBD_static_malloc(uint32_t size);
void USBD_static_free(void *p);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CONF_TEMPLATE_H */

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

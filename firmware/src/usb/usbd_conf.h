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
#define USBD_DEBUG_LEVEL 1U /*used in usbd lib, so keep this*/

#define USBD_USER_LOG_OUTPUT 0
#define USBD_ERR_LOG_OUTPUT 1
#define USBD_DBG_LOG_OUTPUT 0

#if (USBD_USER_LOG_OUTPUT || USBD_ERR_LOG_OUTPUT || USBD_DBG_LOG_OUTPUT)
#include <stdio.h>
#endif

/* ECM, RNDIS, DFU Class Config */
#define USBD_SUPPORT_USER_STRING_DESC 1U

/* BillBoard Class Config */
#define USBD_CLASS_USER_STRING_DESC 1U
#define USBD_CLASS_BOS_ENABLED 1U
#define USB_BB_MAX_NUM_ALT_MODE 0x2U

/* UVC Video Class Configuration */
#include "device_video/uvc_format_config.hh"

#define UVC_WIDTH 320U
#define UVC_HEIGHT 240U

/* bEndpointAddress in Endpoint Descriptor */
#define UVC_IN_EP 0x81U

#define UVC_CAM_FPS_FS 10U
#define UVC_CAM_FPS_HS 15U

#define UVC_ISO_FS_MPS 512U
#define UVC_ISO_HS_MPS 1024U
#define UVC_PACKET_SIZE 1024U

#ifdef USE_UVC_FORMAT_BGR3
// BGR24 advertised via UVC "Frame Based" format (VS_FORMAT_FRAME_BASED, subtype 0x10).
// Uncompressed subtype (0x04) only officially supports YUV GUIDs (YUY2/NV12/...),
// so macOS and Windows reject non-YUV GUIDs there. Frame Based permits any GUID.
// GUID: {e436eb7d-524f-11ce-9f53-0020af0ba770}  (MEDIASUBTYPE_RGB24 / "BGR3")
#define USBD_UVC_FORMAT_FRAME_BASED
#define UVC_BITS_PER_PIXEL 24U
#define UVC_UNCOMPRESSED_GUID 0xE436EB7DU
#define UVC_GUID_SUFFIX_BYTES 0x4F, 0x52, 0xCE, 0x11, 0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
// No RGB->YUV matrix was applied (BGR24 pass-through), so report "Unspecified"
// instead of the library default of BT.601 (0x04).
#define UVC_MATRIX_COEFFICIENTS 0x00U
#else
// YUY2 4:2:2 advertised via UVC "Uncompressed" format (subtype 0x04).
// GUID: {32595559-0000-0010-8000-00AA00389B71}
#define USBD_UVC_FORMAT_UNCOMPRESSED
#define UVC_BITS_PER_PIXEL 16U
#define UVC_UNCOMPRESSED_GUID 0x32595559U
#define UVC_GUID_SUFFIX_BYTES 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71
#endif

// ST library formula has a bug (*16/2 instead of *16/8), override with correct value
#define UVC_MAX_FRAME_SIZE (UVC_WIDTH * UVC_HEIGHT * UVC_BITS_PER_PIXEL / 8U)

#include <string.h>

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
#if USBD_USER_LOG_OUTPUT
#define USBD_UsrLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBD USER: ");                                                                                         \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
	} while (0)
#else
#define USBD_UsrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if USBD_ERR_LOG_OUTPUT
#define USBD_ErrLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBD ERROR: ");                                                                                        \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
	} while (0)
#else
#define USBD_ErrLog(...)                                                                                               \
	do {                                                                                                               \
	} while (0)
#endif

#if USBD_DBG_LOG_OUTPUT
#define USBD_DbgLog(...)                                                                                               \
	do {                                                                                                               \
		printf("USBD DEBUG: ");                                                                                        \
		printf(__VA_ARGS__);                                                                                           \
		printf("\n");                                                                                                  \
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

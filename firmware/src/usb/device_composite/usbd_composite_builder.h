/**
 ******************************************************************************
 * @file    usbd_composite_builder.h
 * @brief   MetaModule replacement for ST's Class/CompositeBuilder.
 *
 * usbd_core.c and usbd_ctlreq.c include this header *by name* and call
 * USBD_CMPSIT_AddClass() plus USBD_CMPSIT.Get*ConfigDescriptor() whenever
 * USE_USBD_COMPOSITE is defined. ST's builder is not on the include path: it
 * generates config descriptors from a fixed per-class table that has no
 * USB-MIDI entry, and it gives no control over interface strings. We supply
 * our own descriptor instead and use only the core's composite plumbing --
 * pClass[]/pClassDataCmsit[]/pUserData[] and the USBD_CoreFindIF() /
 * USBD_CoreFindEP() routing of SETUP, DataIn and DataOut to the owning class.
 *
 * Two profiles exist, one per UsbDeviceMode:
 *   MidiConsole - CDC ACM + USB-MIDI in one composite configuration (our
 *                 hand-written descriptor, below)
 *   Video       - UVC on its own; the descriptor request is forwarded straight
 *                 back to USBD_VIDEO. It still goes through the composite
 *                 registration path because a composite-enabled core only
 *                 dispatches DataIn/DataOut to classes listed in tclasslist.
 ******************************************************************************
 */

#ifndef __USBD_COMPOSITE_BUILDER_H
#define __USBD_COMPOSITE_BUILDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_def.h"

/* USB-MIDI is not one of ST's CLASS_TYPE_* values. Only our AddClass() ever
 * interprets this field, so extend the range locally rather than patching the
 * library's enum. */
/* 13 is unused by ST (their list ends at CLASS_TYPE_CCID = 12) and stays
 * inside the enum's value range, so the cast is well-defined in C++ too. */
#define CLASS_TYPE_MIDI ((USBD_CompositeClassTypeDef)13)

/* Interface numbers within the MidiConsole configuration. The CDC functional
 * descriptors reference these, so they cannot be reordered freely. */
#define CMPSIT_IF_CDC_COMM 0U
#define CMPSIT_IF_CDC_DATA 1U
#define CMPSIT_IF_MIDI_AC 2U
#define CMPSIT_IF_MIDI_MS 3U

typedef enum {
	UsbCompositeProfile_MidiConsole = 0,
	UsbCompositeProfile_Video,
} UsbCompositeProfile;

/* Select which configuration descriptor is served. Call before USBD_Init():
 * USBD_LL_Init() also sizes the OTG FIFOs from the selected profile. */
void USBD_CMPSIT_SelectProfile(UsbCompositeProfile profile);
UsbCompositeProfile USBD_CMPSIT_GetProfile(void);

/* Endpoint address lists handed to USBD_RegisterClassComposite(). The order is
 * the order AddClass() consumes them in; see usbd_composite.c. */
extern uint8_t CMPSIT_CDC_EpAdd[3];
extern uint8_t CMPSIT_MIDI_EpAdd[2];
extern uint8_t CMPSIT_VIDEO_EpAdd[1];

/* Called by USBD_RegisterClassComposite() in usbd_core.c */
uint8_t USBD_CMPSIT_AddClass(USBD_HandleTypeDef *pdev,
							 USBD_ClassTypeDef *pclass,
							 USBD_CompositeClassTypeDef classtype,
							 uint8_t cfgidx);

/* Called by USBD_UnRegisterClassComposite(). Our configuration descriptors are
 * static per profile, so there is nothing to tear down. */
uint8_t USBD_CMPST_ClearConfDesc(USBD_HandleTypeDef *pdev);

extern USBD_ClassTypeDef USBD_CMPSIT;

#ifdef __cplusplus
}
#endif

#endif /* __USBD_COMPOSITE_BUILDER_H */

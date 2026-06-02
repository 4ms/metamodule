/**
 ******************************************************************************
 * @file    usbd_midi.h
 * @brief   Header for the USB-MIDI device class driver (usbd_midi.c).
 *
 * Implements the "Universal Serial Bus Device Class Definition for MIDI
 * Devices, Release 1.0". A single embedded MIDI IN jack and a single embedded
 * MIDI OUT jack are exposed over one bulk OUT and one bulk IN endpoint.
 *
 * ST ships no MIDI device class, so this is a hand-written class driver modeled
 * on the structure of usbd_cdc.c (bulk IN/OUT + RegisterInterface callbacks).
 ******************************************************************************
 */

#ifndef __USB_MIDI_H
#define __USB_MIDI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_ioreq.h"

/* Endpoint addresses (EP1, shares the FIFO layout used by CDC/VIDEO) */
#define MIDI_IN_EP  0x81U /* device -> host (bulk IN)  */
#define MIDI_OUT_EP 0x01U /* host -> device (bulk OUT) */

#define MIDI_DATA_HS_MAX_PACKET_SIZE 512U /* HS bulk endpoints must be 512 */
#define MIDI_DATA_FS_MAX_PACKET_SIZE 64U

/* USB-MIDI event packets are always 4 bytes: [CN|CIN][MIDI_0][MIDI_1][MIDI_2] */
#define MIDI_EVENT_PACKET_SIZE 4U

/* Full configuration descriptor length, computed in usbd_midi.c */
#define USB_MIDI_CONFIG_DESC_SIZ 101U

typedef struct _USBD_MIDI_Itf {
	int8_t (*Init)(void);
	int8_t (*DeInit)(void);
	int8_t (*Receive)(uint8_t *Buf, uint32_t *Len);
	int8_t (*TransmitCplt)(uint8_t *Buf, uint32_t *Len, uint8_t epnum);
} USBD_MIDI_ItfTypeDef;

typedef struct {
	uint8_t *RxBuffer;
	uint8_t *TxBuffer;
	uint32_t RxLength;
	uint32_t TxLength;
	__IO uint32_t TxState;
} USBD_MIDI_HandleTypeDef;

extern USBD_ClassTypeDef USBD_MIDI;
#define USBD_MIDI_CLASS &USBD_MIDI

uint8_t USBD_MIDI_RegisterInterface(USBD_HandleTypeDef *pdev, USBD_MIDI_ItfTypeDef *fops);
uint8_t USBD_MIDI_SetTxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff, uint32_t length);
uint8_t USBD_MIDI_SetRxBuffer(USBD_HandleTypeDef *pdev, uint8_t *pbuff);
uint8_t USBD_MIDI_TransmitPacket(USBD_HandleTypeDef *pdev);
uint8_t USBD_MIDI_ReceivePacket(USBD_HandleTypeDef *pdev);

#ifdef __cplusplus
}
#endif

#endif /* __USB_MIDI_H */

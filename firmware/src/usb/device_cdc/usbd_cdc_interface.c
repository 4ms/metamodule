/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/usbd_cdc_interface.c
  * @author  MCD Application Team
  * @brief   Source file for USBD CDC interface
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

// TODO: this goes into a class, which gets constructed with a ref to the USBD_Device that the device manager owns

/* Includes ------------------------------------------------------------------ */
#include "usbd_cdc.h"

#define APP_RX_DATA_SIZE 2048
#define APP_TX_DATA_SIZE 2048

USBD_CDC_LineCodingTypeDef LineCoding = {
	115200, /* baud rate */
	0x00,	/* stop bits-1 */
	0x00,	/* parity - none */
	0x08	/* nb. of bits 8 */
};

/* Prescaler declaration */
uint32_t uwPrescalerValue = 0;

uint8_t UserRxBuffer[APP_RX_DATA_SIZE]; /* Received Data over USB are stored in
                                         * this buffer */
uint8_t UserTxBuffer[APP_TX_DATA_SIZE]; /* Received Data over UART (CDC
                                         * interface) are stored in this buffer
                                         */

uint32_t UserTxBufPtrIn = 0;  /* Increment this pointer or roll it back to
                                 * start address when data are received over
                                 * USART */
uint32_t UserTxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 * start address when data are sent over USB */

extern USBD_HandleTypeDef USBD_Device;

/* Private function prototypes ----------------------------------------------- */
static int8_t CDC_Itf_Init(void);
static int8_t CDC_Itf_DeInit(void);
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_TransmitCplt(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);
static void Error_Handler(void);
static void ComPort_Config(void);
static void TIM_Config(void);

USBD_CDC_ItfTypeDef USBD_CDC_fops = {
	CDC_Itf_Init,
	CDC_Itf_DeInit,
	CDC_Itf_Control,
	CDC_Itf_Receive,
	CDC_TransmitCplt,
};

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Initializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Init(void) {
	// TIM_Config();
	// if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK) {
	// 	Error_Handler();
	// }

	USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer, 0);
	USBD_CDC_SetRxBuffer(&USBD_Device, UserRxBuffer);

	return USBD_OK;
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit(void) {
	// if (HAL_UART_DeInit(&UartHandle) != HAL_OK) {
	// 	Error_Handler();
	// }
	return USBD_OK;
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length) {
	switch (cmd) {
		case CDC_SEND_ENCAPSULATED_COMMAND:
			/* Add your code here */
			break;

		case CDC_GET_ENCAPSULATED_RESPONSE:
			/* Add your code here */
			break;

		case CDC_SET_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_GET_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_CLEAR_COMM_FEATURE:
			/* Add your code here */
			break;

		case CDC_SET_LINE_CODING:
			LineCoding.bitrate = (uint32_t)(pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24));
			LineCoding.format = pbuf[4];
			LineCoding.paritytype = pbuf[5];
			LineCoding.datatype = pbuf[6];

			/* Set the new configuration */
			// ComPort_Config();
			break;

		case CDC_GET_LINE_CODING:
			pbuf[0] = (uint8_t)(LineCoding.bitrate);
			pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
			pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
			pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
			pbuf[4] = LineCoding.format;
			pbuf[5] = LineCoding.paritytype;
			pbuf[6] = LineCoding.datatype;
			break;

		case CDC_SET_CONTROL_LINE_STATE:
			/* Add your code here */
			break;

		case CDC_SEND_BREAK:
			/* Add your code here */
			break;

		default:
			break;
	}

	return (USBD_OK);
}

// periodically transfer circular buffer -> USB
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
// 	uint32_t buffptr;
// 	uint32_t buffsize;

// 	if (UserTxBufPtrOut != UserTxBufPtrIn) {
// 		if (UserTxBufPtrOut > UserTxBufPtrIn) /* Rollback */ {
// 			buffsize = APP_TX_DATA_SIZE - UserTxBufPtrOut;
// 		} else {
// 			buffsize = UserTxBufPtrIn - UserTxBufPtrOut;
// 		}

// 		buffptr = UserTxBufPtrOut;

// 		USBD_CDC_SetTxBuffer(&USBD_Device, (uint8_t *)&UserTxBuffer[buffptr], buffsize);

// 		if (USBD_CDC_TransmitPacket(&USBD_Device) == USBD_OK) {
// 			UserTxBufPtrOut += buffsize;
// 			if (UserTxBufPtrOut == APP_RX_DATA_SIZE) {
// 				UserTxBufPtrOut = 0;
// 			}
// 		}
// 	}
// }

// UART -> circular buffer
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
// 	/* Increment Index for buffer writing */
// 	UserTxBufPtrIn++;

// 	/* To avoid buffer overflow */
// 	if (UserTxBufPtrIn == APP_RX_DATA_SIZE) {
// 		UserTxBufPtrIn = 0;
// 	}

// 	/* Start another reception: provide the buffer pointer with offset and the
//    * buffer size */
// 	HAL_UART_Receive_IT(huart, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
// }

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */

// USB -> UART
static int8_t CDC_Itf_Receive(uint8_t *Buf, uint32_t *Len) {
	// SCB_CleanDCache_by_Addr((uint32_t *)Buf, *Len);

	// HAL_UART_Transmit_DMA(&UartHandle, Buf, *Len);
	return USBD_OK;
}

/**
  * @brief  CDC_TransmitCplt
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum) {
	UNUSED(Buf);
	UNUSED(Len);
	UNUSED(epnum);

	return 0;
}

/**
  * @brief  Tx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	/* Initiate next USB packet transfer once UART completes transfer
   * (transmitting data over Tx line) */
	USBD_CDC_ReceivePacket(&USBD_Device);
}

/**
  * @brief  ComPort_Config
  *         Configure the COM Port with the parameters received from host.
  * @param  None.
  * @retval None
  * @note   When a configuration is not supported, a default value is used.
  */
// static void ComPort_Config(void) {
// 	if (HAL_UART_DeInit(&UartHandle) != HAL_OK) {
// 		/* Initialization Error */
// 		Error_Handler();
// 	}

// 	/* set the Stop bit */
// 	switch (LineCoding.format) {
// 		case 0:
// 			UartHandle.Init.StopBits = UART_STOPBITS_1;
// 			break;
// 		case 2:
// 			UartHandle.Init.StopBits = UART_STOPBITS_2;
// 			break;
// 		default:
// 			UartHandle.Init.StopBits = UART_STOPBITS_1;
// 			break;
// 	}

// 	/* set the parity bit */
// 	switch (LineCoding.paritytype) {
// 		case 0:
// 			UartHandle.Init.Parity = UART_PARITY_NONE;
// 			break;
// 		case 1:
// 			UartHandle.Init.Parity = UART_PARITY_ODD;
// 			break;
// 		case 2:
// 			UartHandle.Init.Parity = UART_PARITY_EVEN;
// 			break;
// 		default:
// 			UartHandle.Init.Parity = UART_PARITY_NONE;
// 			break;
// 	}

// 	/* set the data type : only 8bits and 9bits is supported */
// 	switch (LineCoding.datatype) {
// 		case 0x07:
// 			/* With this configuration a parity (Even or Odd) must be set */
// 			UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
// 			break;
// 		case 0x08:
// 			if (UartHandle.Init.Parity == UART_PARITY_NONE) {
// 				UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
// 			} else {
// 				UartHandle.Init.WordLength = UART_WORDLENGTH_9B;
// 			}

// 			break;
// 		default:
// 			UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
// 			break;
// 	}

// 	UartHandle.Init.BaudRate = LineCoding.bitrate;
// 	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
// 	UartHandle.Init.Mode = UART_MODE_TX_RX;
// 	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

// 	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
// 		/* Initialization Error */
// 		Error_Handler();
// 	}

// 	/* Start reception: provide the buffer pointer with offset and the buffer
//    * size */
// 	HAL_UART_Receive_IT(&UartHandle, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
// }

/**
  * @brief  TIM_Config: Configure TIMx timer
  * @param  None.
  * @retval None
  */
// static void TIM_Config(void) {
// 	/* Set TIMx instance */
// 	TimHandle.Instance = TIMx;

// 	/* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */
// 	uwPrescalerValue = (uint32_t)(SystemCoreClock / (2 * 10000)) - 1;

// 	/* Initialize TIM3 peripheral as follows: + Period = (CDC_POLLING_INTERVAL *
//    * 10000) - 1 + Prescaler = ((APB1 frequency / 1000000) - 1) + ClockDivision
//    * = 0 + Counter direction = Up */
// 	TimHandle.Init.Period = (CDC_POLLING_INTERVAL * 1000) - 1;
// 	TimHandle.Init.Prescaler = uwPrescalerValue;
// 	TimHandle.Init.ClockDivision = 0;
// 	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
// 	if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK) {
// 		/* Initialization Error */
// 		Error_Handler();
// 	}
// 	/* ##-2- Start the TIM Base generation in interrupt mode #################### */
// 	/* Start Channel1 */
// 	if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK) {
// 		/* Starting Error */
// 		Error_Handler();
// 	}
// }

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @retval None
  */
// void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
// 	/* Transfer error occurred in reception and/or transmission process */
// 	Error_Handler();
// }

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void) {
	/* Add your own code here */
}

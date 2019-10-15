/*
 * codec_sai.c
 *
 * Author: Dan Green (danngreen1@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See http://creativecommons.org/licenses/MIT/ for more information.
 *
 * -----------------------------------------------------------------------------
 */

#pragma once

#include <stm32f7xx.h>
#include "codec_i2c.h"

//
// Codec SAI pins
//

#define CODEC_I2S_TX					SPI2
#define CODEC_I2S_RX					SPI3

#define CODEC_I2S_RCC_TX_ENABLE			__HAL_RCC_SPI2_CLK_ENABLE
#define CODEC_I2S_RCC_RX_ENABLE			__HAL_RCC_SPI3_CLK_ENABLE

#define CODEC_I2S_TX_GPIO_AF			GPIO_AF5_SPI2
#define CODEC_I2S_RX_GPIO_AF			GPIO_AF7_SPI3
#define CODEC_I2S_SCK_RX_GPIO_AF		GPIO_AF6_SPI3

#define CODEC_I2S_GPIO_CLOCK_ENABLE		__HAL_RCC_GPIOB_CLK_ENABLE();__HAL_RCC_GPIOA_CLK_ENABLE();__HAL_RCC_GPIOA_CLK_ENABLE

#define CODEC_I2S_MCK_GPIO				GPIOC
#define CODEC_I2S_MCK_PIN				GPIO_PIN_6

#define CODEC_I2S_WS_TX_GPIO			GPIOB
#define CODEC_I2S_WS_TX_PIN				GPIO_PIN_12

#define CODEC_I2S_WX_RX_GPIO			GPIOA
#define CODEC_I2S_WS_RX_PIN				GPIO_PIN_15

#define CODEC_I2S_SCK_TX_GPIO			GPIOB
#define CODEC_I2S_SCK_TX_PIN			GPIO_PIN_13

#define CODEC_I2S_SCK_RX_GPIO 			GPIOC
#define CODEC_I2S_SCK_RX_PIN			GPIO_PIN_10

#define CODEC_I2S_SDO_GPIO				GPIOB
#define CODEC_I2S_SDO_PIN				GPIO_PIN_15

#define CODEC_I2S_SDI_GPIO				GPIOB
#define CODEC_I2S_SDI_PIN				GPIO_PIN_2



#define CODEC_I2S_DMA_CLOCK_ENABLE		__HAL_RCC_DMA1_CLK_ENABLE

#define	CODEC_I2S_TX_DMA				DMA1
#define	CODEC_I2S_TX_DMA_ISR			LISR
#define	CODEC_I2S_TX_DMA_IFCR			LIFCR
#define CODEC_I2S_TX_DMA_STREAM			DMA1_Stream4
#define CODEC_I2S_TX_DMA_IRQn 			DMA1_Stream4_IRQn
#define CODEC_I2S_TX_DMA_IRQHandler		DMA1_Stream4_IRQHandler
#define CODEC_I2S_TX_DMA_CHANNEL		DMA_CHANNEL_0

#define CODEC_I2S_TX_DMA_FLAG_TC		DMA_FLAG_TCIF0_4
#define CODEC_I2S_TX_DMA_FLAG_HT		DMA_FLAG_HTIF0_4
#define CODEC_I2S_TX_DMA_FLAG_FE		DMA_FLAG_FEIF0_4
#define CODEC_I2S_TX_DMA_FLAG_TE		DMA_FLAG_TEIF0_4
#define CODEC_I2S_TX_DMA_FLAG_DME		DMA_FLAG_DMEIF0_4

#define	CODEC_I2S_RX_DMA				DMA1
#define	CODEC_I2S_RX_DMA_ISR			LISR
#define	CODEC_I2S_RX_DMA_IFCR			LIFCR
#define CODEC_I2S_RX_DMA_STREAM			DMA1_Stream0
#define CODEC_I2S_RX_DMA_IRQn			DMA1_Stream0_IRQn
#define CODEC_I2S_RX_DMA_IRQHandler		DMA1_Stream0_IRQHandler
#define CODEC_I2S_RX_DMA_CHANNEL		DMA_CHANNEL_0

#define CODEC_I2S_RX_DMA_FLAG_TC		DMA_FLAG_TCIF0_4
#define CODEC_I2S_RX_DMA_FLAG_HT		DMA_FLAG_HTIF0_4
#define CODEC_I2S_RX_DMA_FLAG_FE		DMA_FLAG_FEIF0_4
#define CODEC_I2S_RX_DMA_FLAG_TE		DMA_FLAG_TEIF0_4
#define CODEC_I2S_RX_DMA_FLAG_DME		DMA_FLAG_DMEIF0_4



// #define codec_BUFF_LEN 		64							/* DMA rx/tx buffer size, in number of DMA Periph/MemAlign-sized elements (words) */
// #define codec_HT_LEN 		(codec_BUFF_LEN>>1) 		/* Half Transfer buffer size (both channels interleved) */
// #define codec_HT_CHAN_LEN 	(codec_HT_LEN>>1) 			/* Half Transfer buffer size per channel */
// #define STEREO_BUFSZ 		codec_HT_LEN
// #define MONO_BUFSZ 			codec_HT_CHAN_LEN

typedef void (*audio_callback_func_type)(int32_t *src, int32_t *dst);


enum Codec_Errors init_i2s_clock(uint32_t sample_rate);

void start_audio(void);
void stop_audio(void);
enum Codec_Errors init_audio_DMA(uint32_t sample_rate, int32_t *tx_buf, int32_t *rx_buf, uint32_t buff_len);
void set_audio_callback(audio_callback_func_type callback);
// void reboot_codec(uint32_t sample_rate);

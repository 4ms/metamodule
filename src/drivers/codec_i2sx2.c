/*
 * codec_i2sx2.c - dual i2s for duplex audio
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

#include "codec_i2sx2.h"
#include "codec_i2c.h"

I2S_HandleTypeDef hi2s2;
I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi3_rx;

int32_t *tx_buffer;
int32_t *rx_buffer;
uint32_t buffer_size;

enum Codec_Errors codec_dma_it_err = CODEC_NO_ERR;

uint32_t *(tx_buffer_halves[2]);
uint32_t *(rx_buffer_halves[2]);
uint32_t tx_buffer_start, rx_buffer_start, tx_buffer_half, rx_buffer_half;

static audio_callback_func_type audio_callback;

//Private
enum Codec_Errors init_I2S_DMA(void);
void deinit_I2S_DMA(void);
void deinit_I2S_clock(void);
void setup_I2S(uint32_t sample_rate);


void set_audio_callback(audio_callback_func_type callback)
{
	audio_callback = callback;
}

enum Codec_Errors init_audio_DMA(uint32_t sample_rate, int32_t *tx_buf, int32_t *rx_buf, uint32_t buff_len)
{
	buffer_size = buff_len;

	setup_I2S(sample_rate);

	tx_buffer_start = (uint32_t)tx_buf;
	rx_buffer_start = (uint32_t)rx_buf;

	tx_buffer_half = (uint32_t)(&(tx_buf[buffer_size/2]));
	rx_buffer_half = (uint32_t)(&(rx_buf[buffer_size/2]));

	tx_buffer_halves[0] = &(tx_buf[0]);
	tx_buffer_halves[1] = &(tx_buf[buffer_size/2]);

	rx_buffer_halves[0] = &(rx_buf[0]);
	rx_buffer_halves[1] = &(rx_buf[buffer_size/2]);

	return init_I2S_DMA();
}


// void reboot_codec(uint32_t sample_rate)
// {
// 	static uint32_t last_sample_rate;

// 	if (sample_rate!=44100 && sample_rate!=48000 && sample_rate!=96000)
// 		sample_rate = 44100;


// 	//Do nothing if the sample_rate did not change
	
// 	if (last_sample_rate != sample_rate)
// 	{
// 		last_sample_rate = sample_rate; 

// 		//Take everything down...
// 		codec_power_down();
// 	    codec_deinit();
// 	   	HAL_Delay(80);

// 	    deinit_I2S_clock();
// 	    deinit_I2S_DMA();
// 	   	HAL_Delay(80);

// 	   	//...and bring it all back up
// 		init_I2S_clock(sample_rate);

// 		codec_GPIO_init();
// 		init_audio_DMA(sample_rate);

// 		codec_I2C_init();
// 		codec_register_setup(sample_rate);

// 		start_audio();
// 	}

// }

void start_audio(void)
{
	HAL_NVIC_EnableIRQ(CODEC_I2S_RX_DMA_IRQn); 
}

void stop_audio(void)
{
	HAL_NVIC_DisableIRQ(CODEC_I2S_RX_DMA_IRQn); 
}


void deinit_I2S_clock(void)
{
	HAL_RCCEx_DisablePLLI2S();
}

void deinit_I2S_DMA(void)
{
	// HAL_NVIC_DisableIRQ(CODEC_I2S_TX_DMA_IRQn); 
	// HAL_NVIC_DisableIRQ(CODEC_I2S_RX_DMA_IRQn); 

	// //__HAL_RCC_DMA2_CLK_DISABLE();
	// HAL_RCCEx_DisablePLLSAI();

	// __HAL_RCC_SAI2_CLK_DISABLE();

	// HAL_SAI_DeInit(&hsai2a_rx);
	// HAL_SAI_DeInit(&hsai2b_tx);

	// HAL_DMA_Abort(&hdma_sai2a_rx);
	// HAL_DMA_Abort(&hdma_sai2b_tx);

	// HAL_DMA_DeInit(&hdma_sai2a_rx);
	// HAL_DMA_DeInit(&hdma_sai2b_tx);
}



void setup_I2S(uint32_t sample_rate)
{
    GPIO_InitTypeDef gpio;

    // TX I2S

    CODEC_I2S_RCC_TX_ENABLE();
    CODEC_I2S_GPIO_CLOCK_ENABLE();

    hi2s2.Instance = SPI2;
    hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
    hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
    hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hi2s2.Init.AudioFreq = sample_rate;
    hi2s2.Init.CPOL = I2S_CPOL_LOW;
    hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
	HAL_I2S_Init(&hi2s2);

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    gpio.Alternate  = CODEC_I2S_TX_GPIO_AF;

    gpio.Pin = CODEC_I2S_WS_TX_PIN;     HAL_GPIO_Init(CODEC_I2S_WS_TX_GPIO, &gpio);
    gpio.Pin = CODEC_I2S_SCK_TX_PIN;    HAL_GPIO_Init(CODEC_I2S_SCK_TX_GPIO, &gpio);
    gpio.Pin = CODEC_I2S_SDO_PIN;       HAL_GPIO_Init(CODEC_I2S_SDO_GPIO, &gpio);
    gpio.Pin = CODEC_I2S_MCK_PIN;       HAL_GPIO_Init(CODEC_I2S_MCK_GPIO, &gpio);

    // RX I2S

    CODEC_I2S_RCC_RX_ENABLE();

    hi2s3.Instance = SPI3;
    hi2s3.Init.Mode = I2S_MODE_SLAVE_RX;
    hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s3.Init.DataFormat = I2S_DATAFORMAT_24B;
    hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    hi2s3.Init.AudioFreq = sample_rate;
    hi2s3.Init.CPOL = I2S_CPOL_LOW;
    hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
	HAL_I2S_Init(&hi2s3);

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    gpio.Alternate  = CODEC_I2S_RX_GPIO_AF;
    gpio.Pin = CODEC_I2S_WS_RX_PIN;     HAL_GPIO_Init(CODEC_I2S_WX_RX_GPIO, &gpio);
    gpio.Pin = CODEC_I2S_SDI_PIN;       HAL_GPIO_Init(CODEC_I2S_SDI_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_SCK_RX_GPIO_AF;
    gpio.Pin = CODEC_I2S_SCK_RX_PIN;    HAL_GPIO_Init(CODEC_I2S_SCK_RX_GPIO, &gpio);

	//
	//Don't initialize them yet, we have to de-init the DMA first
	//
	// HAL_SAI_DeInit(&hsai2a_rx);
	// HAL_SAI_DeInit(&hsai2b_tx);

}

enum Codec_Errors init_I2S_DMA(void)
{
	//
	// Prepare the DMA for RX (but don't enable yet)
	//
	CODEC_I2S_DMA_CLOCK_ENABLE();

	hdma_spi2_tx.Instance = CODEC_I2S_TX_DMA_STREAM;
	hdma_spi2_tx.Init.Channel = CODEC_I2S_TX_DMA_CHANNEL;
	hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma_spi2_tx.Init.Mode = DMA_CIRCULAR;
	hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_DeInit(&hdma_spi2_tx);

	// if (HAL_SAI_InitProtocol(&hsai2b_tx, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_24BIT, 2) != HAL_OK)
	// 	return CODEC_SAIB_INIT_ERR;

	HAL_DMA_Init(&hdma_spi2_tx);
    __HAL_LINKDMA(&hi2s2, hdmatx, hdma_spi2_tx);

    hdma_spi3_rx.Instance = CODEC_I2S_RX_DMA_STREAM;
    hdma_spi3_rx.Init.Channel = CODEC_I2S_RX_DMA_CHANNEL;
    hdma_spi3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_spi3_rx.Init.Mode = DMA_NORMAL;
    hdma_spi3_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_spi3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_DeInit(&hdma_spi3_rx);

	// if (HAL_SAI_InitProtocol(&hsai2a_rx, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_24BIT, 2) != HAL_OK)
	// 	return CODEC_SAIA_INIT_ERR;

    HAL_DMA_Init(&hdma_spi3_rx);
    __HAL_LINKDMA(&hi2s3, hdmarx, hdma_spi3_rx);

    //
    // DMA IRQ and start DMAs
    //

	HAL_NVIC_DisableIRQ(CODEC_I2S_TX_DMA_IRQn); 

	HAL_NVIC_SetPriority(CODEC_I2S_RX_DMA_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(CODEC_I2S_RX_DMA_IRQn); 

	HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t *)tx_buffer, buffer_size);
	HAL_I2S_Receive_DMA(&hi2s3, (uint16_t *)rx_buffer, buffer_size);

	// if (HAL_SAI_Transmit_DMA(&hsai2b_tx, (uint8_t *)tx_buffer, buffer_size) != HAL_OK)
	// 		return CODEC_SAIA_XMIT_DMA_ERR;
	// if (HAL_SAI_Receive_DMA(&hsai2a_rx, (uint8_t *)rx_buffer, buffer_size) != HAL_OK)
	// 		return CODEC_SAIB_XMIT_DMA_ERR;
	// __HAL_SAI_ENABLE(&hsai2a_rx);
	// __HAL_SAI_ENABLE(&hsai2b_tx);
	
    return CODEC_NO_ERR;
}

void CODEC_I2S_RX_DMA_IRQHandler(void)
{
	// HAL_DMA_IRQHandler(&hdma_spi3_rx);

	int32_t *src, *dst;

	//Read the interrupt status register (ISR)
	uint32_t tmpisr = CODEC_I2S_RX_DMA->CODEC_I2S_RX_DMA_ISR;

	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_FE) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_FE))
	// 	codec_dma_it_err=CODEC_DMA_IT_FE; 
		
	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_TE) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_TE))
	// 	codec_dma_it_err=CODEC_DMA_IT_TE; 

	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_DME) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_DME))
	// 	codec_dma_it_err=CODEC_DMA_IT_DME; 

	// Transfer Complete (TC)
	if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_TC) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_TC))
	{
		// Point to 2nd half of buffers
		src = (int32_t *)(rx_buffer_half);
		dst = (int32_t *)(tx_buffer_half);

		//process_audio_block_codec(src, dst);
		audio_callback(src, dst);

		CODEC_I2S_RX_DMA->CODEC_I2S_RX_DMA_IFCR = CODEC_I2S_RX_DMA_FLAG_TC;
	}

	// // Half Transfer complete (HT)
	if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_HT) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_HT))
	{
		// Point to 1st half of buffers
		src = (int32_t *)(rx_buffer_start);
		dst = (int32_t *)(tx_buffer_start);

		//process_audio_block_codec(src, dst);
		audio_callback(src, dst);

		CODEC_I2S_RX_DMA->CODEC_I2S_RX_DMA_IFCR = CODEC_I2S_RX_DMA_FLAG_HT;
	}
}

void CODEC_I2S_TX_DMA_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi2_tx);
}


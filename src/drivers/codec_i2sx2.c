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

// int32_t *tx_buffer;
// int32_t *rx_buffer;
uint32_t buffer_size_bytes;

enum Codec_Errors codec_dma_it_err = CODEC_NO_ERR;

int16_t *(tx_buffer_halves[2]);
int16_t *(rx_buffer_halves[2]);

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

enum Codec_Errors init_audio_DMA(uint32_t sample_rate, int16_t *tx_buf, int16_t *rx_buf, uint32_t buff_size_bytes)
{
	buffer_size_bytes = buff_size_bytes;
	uint32_t buffer_size_samples = buffer_size_bytes / 2;

	setup_I2S(sample_rate);

	tx_buffer_halves[0] = &(tx_buf[0]);
	tx_buffer_halves[1] = &(tx_buf[buffer_size_samples/2]);

	rx_buffer_halves[0] = &(rx_buf[0]);
	rx_buffer_halves[1] = &(rx_buf[buffer_size_samples/2]);

	return init_I2S_DMA();
}

void start_audio(void)
{
	HAL_NVIC_SetPriority(CODEC_I2S_TX_DMA_IRQn, 1, 1);
	HAL_NVIC_SetPriority(CODEC_I2S_RX_DMA_IRQn, 1, 0);

	HAL_NVIC_EnableIRQ(CODEC_I2S_RX_DMA_IRQn); 
	// HAL_NVIC_EnableIRQ(CODEC_I2S_TX_DMA_IRQn); 

	uint16_t int16s_to_xfer = buffer_size_bytes / 4;

	if (HAL_I2S_Receive_DMA(&hi2s3, (uint16_t *)(rx_buffer_halves[0]), buffer_size_bytes / 2) != HAL_OK)
		codec_dma_it_err = CODEC_I2S_RX_XMIT_DMA_ERR;

	if (HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t *)(tx_buffer_halves[0]), buffer_size_bytes / 4) != HAL_OK)
		codec_dma_it_err = CODEC_I2S_TX_XMIT_DMA_ERR;

}

void stop_audio(void)
{
	HAL_NVIC_DisableIRQ(CODEC_I2S_RX_DMA_IRQn); 
}


void deinit_I2S_clock(void)
{
	HAL_RCCEx_DisablePLLI2S();
}

void setup_I2S(uint32_t sample_rate)
{
    GPIO_InitTypeDef gpio;

    CODEC_I2S_GPIO_CLOCK_ENABLE();

    // RX I2S

    CODEC_I2S_RCC_RX_ENABLE();

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    gpio.Alternate  = CODEC_I2S_WS_RX_GPIO_AF;
    gpio.Pin = CODEC_I2S_WS_RX_PIN;     
    HAL_GPIO_Init(CODEC_I2S_WS_RX_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_SDI_GPIO_AF;
    gpio.Pin = CODEC_I2S_SDI_PIN;       
    HAL_GPIO_Init(CODEC_I2S_SDI_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_SCK_RX_GPIO_AF;
    gpio.Pin = CODEC_I2S_SCK_RX_PIN;
    HAL_GPIO_Init(CODEC_I2S_SCK_RX_GPIO, &gpio);

    hi2s3.Instance = SPI3;
    hi2s3.Init.Mode = I2S_MODE_SLAVE_RX;
    hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
    hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    hi2s3.Init.AudioFreq = sample_rate;
    hi2s3.Init.CPOL = I2S_CPOL_LOW;
    hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  	HAL_I2S_DeInit(&hi2s2);
	// HAL_I2S_Init(&hi2s3);

    // TX I2S

    CODEC_I2S_RCC_TX_ENABLE();

    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;

    gpio.Alternate  = CODEC_I2S_WS_TX_GPIO_AF;
    gpio.Pin = CODEC_I2S_WS_TX_PIN;     
    HAL_GPIO_Init(CODEC_I2S_WS_TX_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_SCK_TX_GPIO_AF;
    gpio.Pin = CODEC_I2S_SCK_TX_PIN;    
    HAL_GPIO_Init(CODEC_I2S_SCK_TX_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_SDO_GPIO_AF;
    gpio.Pin = CODEC_I2S_SDO_PIN;       
    HAL_GPIO_Init(CODEC_I2S_SDO_GPIO, &gpio);

    gpio.Alternate  = CODEC_I2S_MCK_GPIO_AF;
    gpio.Pin = CODEC_I2S_MCK_PIN;       
    HAL_GPIO_Init(CODEC_I2S_MCK_GPIO, &gpio);

    hi2s2.Instance = SPI2;
    hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
    hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B;
    hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hi2s2.Init.AudioFreq = sample_rate;
    hi2s2.Init.CPOL = I2S_CPOL_LOW;
    hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  	HAL_I2S_DeInit(&hi2s2);
	// HAL_I2S_Init(&hi2s2);
}

enum Codec_Errors init_I2S_DMA(void)
{
	HAL_NVIC_DisableIRQ(CODEC_I2S_TX_DMA_IRQn); 
	HAL_NVIC_DisableIRQ(CODEC_I2S_RX_DMA_IRQn); 

	CODEC_I2S_DMA_CLOCK_ENABLE();

    hdma_spi3_rx.Instance = CODEC_I2S_RX_DMA_STREAM;
    hdma_spi3_rx.Init.Channel = CODEC_I2S_RX_DMA_CHANNEL;
    hdma_spi3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_spi3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi3_rx.Init.Mode = DMA_CIRCULAR;//DMA_NORMAL;
    hdma_spi3_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_spi3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_DeInit(&hdma_spi3_rx);

	HAL_I2S_Init(&hi2s3);
    HAL_DMA_Init(&hdma_spi3_rx);
    __HAL_LINKDMA(&hi2s3, hdmarx, hdma_spi3_rx);

	hdma_spi2_tx.Instance = CODEC_I2S_TX_DMA_STREAM;
	hdma_spi2_tx.Init.Channel = CODEC_I2S_TX_DMA_CHANNEL;
	hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma_spi2_tx.Init.Mode = DMA_CIRCULAR;
	hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH;
	hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_DeInit(&hdma_spi2_tx);

	HAL_I2S_Init(&hi2s2);
	HAL_DMA_Init(&hdma_spi2_tx);
    __HAL_LINKDMA(&hi2s2, hdmatx, hdma_spi2_tx);
	
    return CODEC_NO_ERR;
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
	audio_callback((int32_t *)(rx_buffer_halves[0]), (int32_t *)(tx_buffer_halves[0]));
}
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
	audio_callback((int32_t *)(rx_buffer_halves[1]), (int32_t *)(tx_buffer_halves[1]));
}

void CODEC_I2S_RX_DMA_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi3_rx);
}
/*
	int32_t *src, *dst;
	uint8_t half;
	uint32_t flag;

	//Read the interrupt status register (ISR)
	uint32_t tmpisr = CODEC_I2S_RX_DMA->CODEC_I2S_RX_DMA_ISR;

	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_FE) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_FE))
	// 	codec_dma_it_err=CODEC_DMA_IT_FE; 
		
	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_TE) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_TE))
	// 	codec_dma_it_err=CODEC_DMA_IT_TE; 

	// if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_DME) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_DME))
	// 	codec_dma_it_err=CODEC_DMA_IT_DME; 

	// Transfer Complete (TC)
	if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_TC) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_TC)) {
		half = 1;
		flag = CODEC_I2S_RX_DMA_FLAG_TC;
	}

	// Half Transfer complete (HT)
	else if ((tmpisr & CODEC_I2S_RX_DMA_FLAG_HT) && __HAL_DMA_GET_IT_SOURCE(&hdma_spi3_rx, DMA_IT_HT)) {
		half = 0;
		flag = CODEC_I2S_RX_DMA_FLAG_HT;
	}

	else
		return; //error?

	src = (int32_t *)(rx_buffer_halves[half]);
	dst = (int32_t *)(tx_buffer_halves[half]);

	audio_callback(src, dst);

	CODEC_I2S_RX_DMA->CODEC_I2S_RX_DMA_IFCR = flag;
*/

/*
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s);
*/

void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s) {
	__BKPT();
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s) {
	// audio_callback((int32_t *)(rx_buffer_halves[1]), (int32_t *)(tx_buffer_halves[1]));
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
	// audio_callback((int32_t *)(rx_buffer_halves[0]), (int32_t *)(tx_buffer_halves[0]));
}

void CODEC_I2S_TX_DMA_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi2_tx);
}

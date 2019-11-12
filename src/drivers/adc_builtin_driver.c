/*
 * adc_builtin_driver.c - adc driver for built-in adcs
 * Uses DMA to dump ADC values into buffers
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

#include "drivers/adc_builtin_driver.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc3;

void ADC1_Init(uint16_t *adc_buffer, uint32_t num_channels, builtinAdcSetup *adc_setup)
{

	ADC_ChannelConfTypeDef 	sConfig;
	GPIO_InitTypeDef 		gpio;
	uint8_t i;

	//Enable DMA2 clock
	__HAL_RCC_DMA2_CLK_ENABLE();

	//Set GPIO pins to analog
	for (i=0; i<num_channels; i++)
	{
	    gpio.Pin = adc_setup[i].pin;
	    gpio.Mode = GPIO_MODE_ANALOG;
	    gpio.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(adc_setup[i].gpio, &gpio);
	}

	//Initialize ADC1 peripheral
	hadc1.Instance 						= ADC1;
	hadc1.Init.ClockPrescaler 			= ADC_CLOCK_SYNC_PCLK_DIV8;
	hadc1.Init.Resolution 				= ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode 			= ENABLE;
	hadc1.Init.ContinuousConvMode 		= ENABLE;
	hadc1.Init.DiscontinuousConvMode 	= DISABLE;
	hadc1.Init.ExternalTrigConvEdge 	= ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv 		= ADC_EXTERNALTRIGCONV_T1_CC1;//ADC_SOFTWARE_START;
	hadc1.Init.DataAlign 				= ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion 			= num_channels;
	hadc1.Init.DMAContinuousRequests 	= ENABLE;//DISABLE;
	hadc1.Init.EOCSelection 			= ADC_EOC_SEQ_CONV;//ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	for (i=0; i<num_channels; i++)
	{
		sConfig.Channel 		= adc_setup[i].channel;
		sConfig.Rank 			= ADC_REGULAR_RANK_1 + i;
		sConfig.SamplingTime	= adc_setup[i].sample_time;
		HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	}

	__HAL_ADC_DISABLE_IT(&hadc1, (ADC_IT_EOC | ADC_IT_OVR));

	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, num_channels);
	//Enable interrupt
	NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	NVIC_SetPriority(DMA2_Stream4_IRQn, 2, 2);
}

//
//This is called from HAL_ADC_Init()
//
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
	if(adcHandle->Instance==ADC1)
	{
		__HAL_RCC_ADC1_CLK_ENABLE();

		hdma_adc1.Instance 					= DMA2_Stream4;
		hdma_adc1.Init.Channel 				= DMA_CHANNEL_0;
		hdma_adc1.Init.Direction 			= DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc 			= DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc 				= DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment 	= DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment 	= DMA_MDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode 				= DMA_NORMAL;//DMA_CIRCULAR;
		hdma_adc1.Init.Priority 			= DMA_PRIORITY_MEDIUM;
		hdma_adc1.Init.FIFOMode 			= DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&hdma_adc1);

		__HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);
	}

}


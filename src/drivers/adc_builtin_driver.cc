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

#include "adc_builtin_driver.hh"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_dma.h"
#include <stm32f7xx_ll_bus.h>

AdcPeriph::AdcPeriph(ADC_TypeDef *ADCx)
{
	ADCx_ = ADCx;
	num_channels_ = 0;
	LL_ADC_Disable(ADCx_);

	if (ADCx_ == ADC1)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	else if (ADCx_ == ADC2)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	else if (ADCx_ == ADC3)
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC3);

	NVIC_SetPriority(ADC_IRQn, (0 << 2) | 3);
	NVIC_EnableIRQ(ADC_IRQn);

	LL_ADC_SetCommonClock(ADC123_COMMON, LL_ADC_CLOCK_SYNC_PCLK_DIV2);

	LL_ADC_SetResolution(ADCx_, LL_ADC_RESOLUTION_12B);
	LL_ADC_SetDataAlignment(ADCx_, LL_ADC_DATA_ALIGN_RIGHT);
	LL_ADC_SetSequencersScanMode(ADCx_, LL_ADC_SEQ_SCAN_ENABLE);

	LL_ADC_REG_InitTypeDef adcreginit;

	adcreginit.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	adcreginit.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE; //modify each time we add a channel 
	adcreginit.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	adcreginit.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	adcreginit.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	LL_ADC_REG_Init(ADCx_, &adcreginit);
	LL_ADC_REG_SetFlagEndOfConversion(ADCx_, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
}

void AdcPeriph::add_channel(AdcChan adcc) {
	//adcc.pin.init(); //Todo: make sure pin constructor is called
	LL_ADC_REG_SetSequencerRanks(ADCx_, num_channels_, adcc.channel_);
	LL_ADC_REG_SetSequencerLength(ADCx_, LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS + num_channels_);
	LL_ADC_SetChannelSamplingTime(ADCx_, adcc.channel_, adcc.sampletime_);
	num_channels_++;

}
const uint32_t ADC_DMA_Stream = LL_DMA_STREAM_4;
const uint32_t ADC_DMA_Channel = LL_DMA_CHANNEL_0;

void AdcPeriph::start(uint16_t *raw_buffer)
{
	if (!num_channels_) return;

	//Enable DMA2_Stream4 Channel 0
	NVIC_SetPriority(DMA2_Stream4_IRQn, (1<<2) | 0);
	NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	LL_DMA_SetChannelSelection(DMA2, ADC_DMA_Stream, ADC_DMA_Channel);
	LL_DMA_ConfigTransfer(DMA2,
						ADC_DMA_Stream,
						LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
						LL_DMA_MODE_CIRCULAR |
						LL_DMA_PERIPH_NOINCREMENT |
						LL_DMA_MEMORY_INCREMENT |
						LL_DMA_PDATAALIGN_HALFWORD |
						LL_DMA_MDATAALIGN_HALFWORD |
						LL_DMA_PRIORITY_HIGH);

	LL_DMA_ConfigAddresses(DMA2, ADC_DMA_Stream, ADCx_->DR, (uint32_t)raw_buffer, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetDataLength(DMA2, ADC_DMA_Stream, num_channels_);
	LL_DMA_EnableIT_TC(DMA2, ADC_DMA_Stream);
	LL_DMA_DisableIT_HT(DMA2, ADC_DMA_Stream);
	LL_DMA_EnableIT_TE(DMA2, ADC_DMA_Stream);
	LL_DMA_EnableStream(DMA2, ADC_DMA_Stream);

	LL_ADC_Enable(ADCx_);

	LL_ADC_REG_StartConversionSWStart(ADCx_);
}

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
#include <stm32f7xx.h>
#include "adc_builtin_driver.hh"
#include "stm32f7xx_ll_adc.h"
#include "stm32f7xx_ll_dma.h"
#include "stm32f7xx_ll_bus.h"

//Todo: research if there's a way to not have to declare these class templates
template class AdcPeriph<AdcPeriphNum::ADC_1>;
template class AdcPeriph<AdcPeriphNum::ADC_2>;
template class AdcPeriph<AdcPeriphNum::ADC_3>;

template <AdcPeriphNum adc_n>
AdcPeriph<adc_n>& AdcPeriph<adc_n>::AdcInstance()
{
	// static_assert(adc_n == ADC_1 || adc_n == ADC_2 || adc_n == ADC_3, "Only ADC1, ADC2, and ADC3 peripherals supported");
	static AdcPeriph<adc_n> Adc_;
	return Adc_;
}

template <AdcPeriphNum adc_n>
AdcPeriph<adc_n>::AdcPeriph()
{
	// static_assert(adc_n==ADC_1 || adc_n==ADC_2 || adc_n==ADC_3, "Only ADC1, ADC2, and ADC3 peripherals supported");
	if (adc_n==AdcPeriphNum::ADC_1) {
		ADCx_ = ADC1;
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	}
	else if (adc_n==AdcPeriphNum::ADC_2) {
		ADCx_ = ADC2;
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	}
	else if (adc_n==AdcPeriphNum::ADC_3) {
		ADCx_ = ADC3;
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC3);
	}

	num_channels_ = 0;
	LL_ADC_Disable(ADCx_);

	NVIC_SetPriority(ADC_IRQn, (0 << 2) | 3);
	NVIC_EnableIRQ(ADC_IRQn);

	LL_ADC_SetCommonClock(ADC123_COMMON, LL_ADC_CLOCK_SYNC_PCLK_DIV2);

	LL_ADC_SetResolution(ADCx_, LL_ADC_RESOLUTION_12B);
	LL_ADC_SetDataAlignment(ADCx_, LL_ADC_DATA_ALIGN_RIGHT);
	LL_ADC_SetSequencersScanMode(ADCx_, LL_ADC_SEQ_SCAN_ENABLE);

	LL_ADC_REG_InitTypeDef adcreginit;

	adcreginit.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	adcreginit.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	adcreginit.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	adcreginit.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	adcreginit.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	LL_ADC_REG_Init(ADCx_, &adcreginit);
	LL_ADC_REG_SetFlagEndOfConversion(ADCx_, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
}

constexpr uint32_t _LL_ADC_DECIMAL_NB_TO_RANK(const uint8_t x) {
	return ((x <= 5)  ? (ADC_SQR3_REGOFFSET | (x*5))
		  : (x <= 11) ? (ADC_SQR2_REGOFFSET | ((x-6)*5))
		  : (x <= 15) ? (ADC_SQR1_REGOFFSET | ((x-12)*5))
		  : 0);
}

constexpr uint32_t _LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(const uint8_t x) {
	return (x << ADC_SQR1_L_Pos);
}

//Todo: add overload that allows for Rank to be set manually (then start_dma must verify and fix any gaps in seqeuence ranks)
template <AdcPeriphNum adc_n>
uint8_t AdcPeriph<adc_n>::add_channel(const AdcChanNum channel, const uint32_t sampletime)
{
	uint8_t channel_u8 = static_cast<uint8_t>(channel);
	uint8_t rank = _LL_ADC_DECIMAL_NB_TO_RANK(num_channels_);
	LL_ADC_REG_SetSequencerRanks(ADCx_, rank, __LL_ADC_DECIMAL_NB_TO_CHANNEL(channel_u8));
	LL_ADC_REG_SetSequencerLength(ADCx_, _LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(num_channels_));
	LL_ADC_SetChannelSamplingTime(ADCx_, __LL_ADC_DECIMAL_NB_TO_CHANNEL(channel_u8), sampletime);
	num_channels_++;
	return rank;
}

template <AdcPeriphNum adc_n>
void AdcPeriph<adc_n>::start_dma(const uint32_t ADC_DMA_Stream, const uint32_t ADC_DMA_Channel, const IRQn_Type ADC_DMA_Streamx_IRQn)
{
	if (!num_channels_) return;

	//Todo: add DMA# to parameter list
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
	LL_DMA_ConfigAddresses(DMA2,
						ADC_DMA_Stream,
						LL_ADC_DMA_GetRegAddr(ADCx_, LL_ADC_DMA_REG_REGULAR_DATA),
						(uint32_t)(dma_buffer_),
						LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetDataLength(DMA2, ADC_DMA_Stream, num_channels_);
	LL_DMA_EnableIT_TC(DMA2, ADC_DMA_Stream);
	LL_DMA_DisableIT_HT(DMA2, ADC_DMA_Stream);
	LL_DMA_EnableIT_TE(DMA2, ADC_DMA_Stream);
	LL_DMA_EnableStream(DMA2, ADC_DMA_Stream);

	NVIC_SetPriority(ADC_DMA_Streamx_IRQn, (1 << 2) | 0);
	NVIC_EnableIRQ(ADC_DMA_Streamx_IRQn);

	LL_ADC_Enable(ADCx_);

	LL_ADC_REG_StartConversionSWStart(ADCx_);
}

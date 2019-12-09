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
template class AdcPeriph<ADC_1>;
template class AdcPeriph<ADC_2>;
template class AdcPeriph<ADC_3>;

template <AdcPeripheral p()>
AdcPeriph<p>& AdcPeriph<p>::AdcInstance()
{
	static AdcPeriph<p> Adc_;
	return Adc_;
}

template <AdcPeripheral p()>
AdcPeriph<p>::AdcPeriph()
{
	System::enable_adc_rcc(p());

	num_channels_ = 0;
	LL_ADC_Disable(p());

	NVIC_SetPriority(ADC_IRQn, (0 << 2) | 3);
	NVIC_EnableIRQ(ADC_IRQn);

	LL_ADC_SetCommonClock(ADC123_COMMON, LL_ADC_CLOCK_SYNC_PCLK_DIV2);

	LL_ADC_SetResolution(p(), LL_ADC_RESOLUTION_12B);
	LL_ADC_SetDataAlignment(p(), LL_ADC_DATA_ALIGN_RIGHT);
	LL_ADC_SetSequencersScanMode(p(), LL_ADC_SEQ_SCAN_ENABLE);

	LL_ADC_REG_InitTypeDef adcreginit;

	adcreginit.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	adcreginit.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	adcreginit.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	adcreginit.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	adcreginit.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	LL_ADC_REG_Init(p(), &adcreginit);
	LL_ADC_REG_SetFlagEndOfConversion(p(), LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
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

template <AdcPeripheral p()>
void AdcPeriph<p>::add_channel(const AdcChanNum channel, const uint32_t sampletime)
{
	uint32_t channel_int = static_cast<uint32_t>(channel);
	LL_ADC_REG_SetSequencerRanks(p(), _LL_ADC_DECIMAL_NB_TO_RANK(num_channels_), __LL_ADC_DECIMAL_NB_TO_CHANNEL(channel_int));
	LL_ADC_REG_SetSequencerLength(p(), _LL_ADC_DECIMAL_NB_TO_REG_SEQ_LENGTH(num_channels_));
	LL_ADC_SetChannelSamplingTime(p(), __LL_ADC_DECIMAL_NB_TO_CHANNEL(channel_int), sampletime);
	uint8_t rank_decimal = num_channels_;
	num_channels_++;
	ranks_[channel_int] = rank_decimal;
}

template <AdcPeripheral p()>
void AdcPeriph<p>::start_dma(DMA_TypeDef * const DMAx, const uint32_t ADC_DMA_Stream, const uint32_t ADC_DMA_Channel, const IRQn_Type ADC_DMA_Streamx_IRQn)
{
	if (!num_channels_) return;

	System::enable_dma_rcc(DMAx);
	
	LL_DMA_SetChannelSelection(DMAx, ADC_DMA_Stream, ADC_DMA_Channel);
	LL_DMA_ConfigTransfer(DMAx,
						ADC_DMA_Stream,
						LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
						LL_DMA_MODE_CIRCULAR |
						LL_DMA_PERIPH_NOINCREMENT |
						LL_DMA_MEMORY_INCREMENT |
						LL_DMA_PDATAALIGN_HALFWORD |
						LL_DMA_MDATAALIGN_HALFWORD |
						LL_DMA_PRIORITY_HIGH);
	LL_DMA_ConfigAddresses(DMAx,
						ADC_DMA_Stream,
						LL_ADC_DMA_GetRegAddr(p(), LL_ADC_DMA_REG_REGULAR_DATA),
						(uint32_t)(dma_buffer_),
						LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetDataLength(DMAx, ADC_DMA_Stream, num_channels_);
	LL_DMA_EnableIT_TC(DMAx, ADC_DMA_Stream);
	LL_DMA_DisableIT_HT(DMAx, ADC_DMA_Stream);
	LL_DMA_EnableIT_TE(DMAx, ADC_DMA_Stream);
	LL_DMA_EnableStream(DMAx, ADC_DMA_Stream);

	NVIC_SetPriority(ADC_DMA_Streamx_IRQn, (1 << 2) | 0);
	NVIC_EnableIRQ(ADC_DMA_Streamx_IRQn);

	LL_ADC_Enable(p());

	LL_ADC_REG_StartConversionSWStart(p());
}

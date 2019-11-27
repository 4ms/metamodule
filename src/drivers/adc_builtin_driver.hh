/*
 * adc_builtin_driver.h - adc driver for built-in adcs
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
#include <stm32f7xx_ll_adc.h>
#include "pin.hh"

enum AdcChannelNumbers{ ADCChan0, ADCChan1, ADCChan2, ADCChan3, ADCChan4, ADCChan5, ADCChan6, ADCChan7,
						ADCChan8, ADCChan9, ADCChan10, ADCChan11, ADCChan12, ADCChan13, ADCChan14, ADCChan15
						};
enum AdcPeriphNums {ADC_1=1, ADC_2=2, ADC_3=3};

template <enum AdcPeriphNums adc_n> class AdcPeriph;

template <enum AdcPeriphNums adc_n>
class AdcChan {
public:
	AdcChan(enum AdcChannelNumbers channel, Pin pin, uint32_t sampletime)
	: adc_periph_(AdcPeriph<adc_n>::AdcInstance()),
	  channel_(channel),
	  pin_(pin),
	  sampletime_(sampletime)
	{
		AdcPeriph<adc_n>::add_channel(channel, sampletime);
	}

private:
	AdcPeriph<adc_n>& adc_periph_;
	Pin<NORMAL> pin_;
	enum AdcChannelNumbers channel_;
	uint32_t sampletime_;
};

template <enum AdcPeriphNums adc_n>
class AdcPeriph
{
public:
	static void start_dma(uint16_t *raw_buffer, uint32_t ADC_DMA_Stream, uint32_t ADC_DMA_Channel, IRQn_Type ADC_DMA_Streamx_IRQn);
	static void add_channel(enum AdcChannelNumbers channel, uint32_t sampletime);
	//Todo:
	//set_dma_destination(uint16_t *)
	//set_dma_parameters(DMA1/2, stream, channel, IRQn);
	//start_dma() //overload with no parameters

private:
	AdcPeriph();
	static AdcPeriph<adc_n> &AdcInstance();
	template <enum AdcPeriphNums adc_chan_n>
	friend class AdcChan;

	static inline ADC_TypeDef *ADCx_;
	static inline uint8_t num_channels_;
	// static inline uint16_t raw_values[16]; //todo: use vector for dynamic
};

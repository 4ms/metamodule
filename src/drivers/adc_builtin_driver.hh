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
enum AdcPeriphNums {ADC_1, ADC_2, ADC_3};

//template function with local static object
//Todo: make sAdcPeriph private? somehow not publically callable. Place in .cc file?
//Todo: allow sAdcChan to call add_channel, but not publically callable. friend class?
template <enum AdcPeriphNums adc_n> class sAdcChan;

template <enum AdcPeriphNums adc_n>
class sAdcPeriph {
public: //todo: how to allow constructor just for AdcInstance function, using protected? friend? member method?
	sAdcPeriph();
	//: num_channels_(0), ADCx_(adc_n==ADC_1 ? ADC1 : adc_n==ADC_2 ? ADC2 : ADC3)
	// {}
public:
	static void start_dma(uint16_t *raw_buffer, uint32_t ADC_DMA_Stream, uint32_t ADC_DMA_Channel);
	void add_channel(const sAdcChan<adc_n>& adcc);

private: 
	static ADC_TypeDef *ADCx_;
	static uint8_t num_channels_;
};

template<enum AdcPeriphNums adc_n>
sAdcPeriph<adc_n>& AdcInstance() {
	static_assert(adc_n==ADC_1 || adc_n==ADC_2 || adc_n==ADC_3, "Only ADC1, ADC2, and ADC3 peripherals supported");
	static sAdcPeriph<adc_n> Adc_;
	return Adc_;
}

template <enum AdcPeriphNums adc_n>
class sAdcChan {
public:
	sAdcChan(enum AdcChannelNumbers channel, Pin<NORMAL> pin, uint32_t sampletime)
	: adc_periph_(AdcInstance<adc_n>()), 
	  channel_(channel), 
	  pin_(pin), 
	  sampletime_(sampletime)
	{
		adc_periph_.add_channel(*this);
	}

private:
	sAdcPeriph<adc_n>& adc_periph_;
	Pin<NORMAL> pin_;
public:
	enum AdcChannelNumbers channel_;
	uint32_t sampletime_;
};



////////////////////////
//non-singleton:
/*
struct AdcChan {
	AdcChan(enum AdcChannelNumbers channel, Pin<NORMAL> pin, uint32_t sampletime) 
	: channel_(channel), pin_(pin), sampletime_(sampletime){}

	enum AdcChannelNumbers channel_;
	Pin<NORMAL> pin_;
	uint32_t sampletime_;
};

template <int adc_n>
class AdcPeriph
{
public:
	AdcPeriph();
	void add_channel(const AdcChan adcc);
	void start_dma(uint16_t *raw_buffer, uint32_t ADC_DMA_Stream, uint32_t ADC_DMA_Channel);

private: 
	ADC_TypeDef *ADCx_;
	uint8_t num_channels_;
};

*/
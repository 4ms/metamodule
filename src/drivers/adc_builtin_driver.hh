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

#include <array>
#include <stm32f7xx.h>
#include "stm32f7xx_ll_adc.h"
#include "pin.hh"

// namespace Adc {
// enum Channels { Chan0, ...}; //usage: Adc::Chan0
// enum Peripherals { Periph1 = ADC1_BASE, Periph2 = ADC2_BASE, Periph3 = ADC3_BASE }; //usage: Adc::Periph1
enum class AdcChanNum { Chan0, Chan1, Chan2, Chan3, Chan4, Chan5, Chan6, Chan7,
						Chan8, Chan9, Chan10, Chan11, Chan12, Chan13, Chan14, Chan15 };
enum class AdcPeriphNum {ADC_1, ADC_2, ADC_3};


template <AdcPeriphNum periph> class AdcPeriph;

template <AdcPeriphNum p, AdcChanNum c> 
class AdcChanL {
	using ValueType = uint32_t;
public:
	AdcChanL(const uint32_t sampletime=LL_ADC_SAMPLINGTIME_144CYCLES) {
		auto init_adc_once = AdcPeriph<p>::AdcInstance();
		AdcPeriph<p>::add_channel(c, sampletime);
	}
	ValueType& get_val_ref() { return AdcPeriph<p>::get_val_ref(c); } //experimental, perhaps dangerous? Todo: create a read-only struct to return
	ValueType get_val() { return AdcPeriph<p>::get_val(c); }
};


//Todo: use an int for the template parameter, set to ADC1_BASE, ADC2_BASE, ...
//We could just redefine the enum AdcPEriphNum elements to = ADC1_BASE, etc
//Then do (reinterpret_cast<ADC_TypeDef *>(periph)) to get the peripheral 
template <AdcPeriphNum periph>
class AdcPeriph
{
	template <AdcPeriphNum adc_chan_periph>
	friend class AdcChan;

	template <AdcPeriphNum, AdcChanNum>
	friend class AdcChanL;

public:
	static void start_dma(const uint32_t ADC_DMA_Stream, const uint32_t ADC_DMA_Channel, const IRQn_Type ADC_DMA_Streamx_IRQn);
	static uint16_t get_val(const AdcChanNum channel) { return dma_buffer_[ ranks_[static_cast<uint8_t>(channel)] ];}
	static uint16_t& get_val_ref(const AdcChanNum channel) { return dma_buffer_[ ranks_[static_cast<uint8_t>(channel)] ];}

private:
	//Returns rank channel was added
	static uint8_t add_channel(const AdcChanNum channel, const uint32_t sampletime);

	//Todo:
	//add_channel(rank, channel, sampletime)
	//set_dma_parameters(DMA1/2, stream, channel, IRQn);
	//start_dma() //overload with no parameters

	AdcPeriph();
	static AdcPeriph<periph> &AdcInstance();

	static inline ADC_TypeDef *ADCx_;
	static inline uint8_t num_channels_;
	static inline uint8_t ranks_[16];
	// static inline std::vector<uint16_t> dma_buffer_;
	// static inline std::array<uint16_t, 16> dma_buffer_;
	static inline uint16_t dma_buffer_[16]; //todo: use vector for dynamic
};

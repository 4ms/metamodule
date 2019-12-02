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

enum class AdcChanNum { Chan0, Chan1, Chan2, Chan3, Chan4, Chan5, Chan6, Chan7,
						Chan8, Chan9, Chan10, Chan11, Chan12, Chan13, Chan14, Chan15 };
enum class AdcPeriphNum {ADC_1, ADC_2, ADC_3};

template <AdcPeriphNum periph> class AdcPeriph;

    //Todo? avoid virtual base class IAdcChanBase
	//Instead of AdcChan<>::get_val() {...}, do AdcPeriph<>.get_val(uint8_t channel_rank) {return dma_buffer_[channel_rank];}
	//Instead of CVJack having a IAdcChanBase& member, it has two uint8_t members: adc_channel_num_, adc_periph_num_
    //CVJack ctor sets adc_channel_num_(Hardware::freq1cv_adc.get_rank(), and CVJack.adc_periph_num_ to ::.adc_num_
    //get() calls AdcPeriph<adc_periph_num_>::get(adc_rank_num)
	//Cons: this technique makes AdcPeriph a visible class
	//Pros: no virtual base class needed, more simple. Possible speed increase due to no vtable... Todo: measure

	//Or:
	//template <class periphT> AdcChan {}
	//...?

	//Or: attempt again to make AdcChan non-template

class IAdcChanBase {
public: 
	virtual uint16_t& get_val_ref() = 0;
	virtual uint16_t get_val() = 0;
};

template <AdcPeriphNum periph>
class AdcChan : public IAdcChanBase {
public:
	AdcChan(const AdcChanNum channel, const Pin pin, const uint32_t sampletime=LL_ADC_SAMPLINGTIME_144CYCLES)
	: adc_periph_(AdcPeriph<periph>::AdcInstance()),
	  channel_(channel),
	  pin_(pin),
	  sampletime_(sampletime),
	  rank_(AdcPeriph<periph>::add_channel(channel, sampletime))
	{}

	virtual uint16_t& get_val_ref() { return adc_periph_.dma_buffer_[rank_]; }
	virtual uint16_t get_val() { return adc_periph_.dma_buffer_[rank_]; }
	constexpr uint8_t get_rank() { return rank_; }
	constexpr AdcPeriphNum get_periph_num() { return periph; }

private:
	const AdcPeriph<periph> &adc_periph_;
	const Pin pin_;
	const AdcChanNum channel_;
	const uint32_t sampletime_;
	const uint8_t rank_;
};

template <AdcPeriphNum periph>
class AdcPeriph
{
	template <AdcPeriphNum adc_chan_periph>
	friend class AdcChan;

public:
	static void start_dma(const uint32_t ADC_DMA_Stream, const uint32_t ADC_DMA_Channel, const IRQn_Type ADC_DMA_Streamx_IRQn);
	static void get_channel_val(const uint8_t adc_channel_rank_);

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
	// static inline std::vector<uint16_t> dma_buffer_;
	// static inline std::array<uint16_t, 16> dma_buffer_;
	static inline uint16_t dma_buffer_[16]; //todo: use vector for dynamic
};

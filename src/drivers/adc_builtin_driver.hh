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

enum class AdcChanNum { _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15 };

using AdcPeripheral = ADC_TypeDef*;

constexpr AdcPeripheral ADC_1() { return ADC1; }
constexpr AdcPeripheral ADC_2() { return ADC2; }
constexpr AdcPeripheral ADC_3() { return ADC3; }


template <AdcPeripheral ADC_X()> class AdcPeriph;

template <AdcPeripheral ADC_X(), AdcChanNum c, typename T> 
class AdcChan {
public:
	AdcChan(const uint32_t sampletime=LL_ADC_SAMPLINGTIME_144CYCLES) {
		auto init_adc_once = AdcPeriph<ADC_X>::AdcInstance();
		AdcPeriph<ADC_X>::add_channel(c, sampletime);
	}

	T& get_val_ref() {  //experimental, perhaps dangerous? Todo: create a read-only struct to return
		return AdcPeriph<ADC_X>::get_val_ref(c); 
	}

	T get_val() { 
		return AdcPeriph<ADC_X>::get_val(c); 
	}

	void start_dma( DMA_TypeDef * const DMAx, 
					const uint32_t ADC_DMA_Stream, 
					const uint32_t ADC_DMA_Channel, 
					const IRQn_Type ADC_DMA_Streamx_IRQn) 
	{ 
		AdcPeriph<ADC_X>::start_dma(DMAx, ADC_DMA_Stream, ADC_DMA_Channel, ADC_DMA_Streamx_IRQn);
	}
};

template <AdcPeripheral ADC_X()> 
class AdcPeriph
{
	template <AdcPeripheral p(), AdcChanNum c, typename T>
	friend class AdcChan;

public:
	static void start_dma(DMA_TypeDef * const DMAx, 
						  const uint32_t ADC_DMA_Stream, 
						  const uint32_t ADC_DMA_Channel, 
						  const IRQn_Type ADC_DMA_Streamx_IRQn);

	static uint16_t get_val(const AdcChanNum channel) { 
		return dma_buffer_[ 
			ranks_[static_cast<uint8_t>(channel)] 
		];
	}

	static uint16_t& get_val_ref(const AdcChanNum channel) { 
		return dma_buffer_[ 
			ranks_[static_cast<uint8_t>(channel)] 
		];
	}

private:
	static void add_channel(const AdcChanNum channel, const uint32_t sampletime);

	//Todo:
	//set_dma_parameters(DMA1/2, stream, channel, IRQn);
	//start_dma() //overload with no parameters

	AdcPeriph();
	static AdcPeriph<ADC_X> &AdcInstance();

	static inline uint8_t num_channels_;
	static inline uint8_t ranks_[16];
	static inline uint16_t dma_buffer_[16]; //todo: use vector for dynamic
	// static inline std::vector<uint16_t> dma_buffer_;
	// static inline std::array<uint16_t, 16> dma_buffer_;
};

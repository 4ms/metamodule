#include "stm32f7xx_ll_dma.h"
#include "controls.hh"

const uint32_t kNumAdcChannels = 4;

std::array<uint16_t, kNumAdcChannels> Controls::adc_raw;
std::array<CVJack, kNumAdcChannels> Controls::CV;
int32_t Controls::rotary_turn[2]; //-1, 0, 1
Button Controls::rotary_button[2]; //0, 1
TouchCtl Controls::pads;

Controls::Controls()
{

    //Todo: add AdcPeriph::set_dma_destination(uint16_t *)
    //AdcPeriph::set_dma_parameters(DMA1/2, stream, channel, >>> then lookup IRQ based on Stream and DMA#?)
    //AdcPeriph::start_dma() //overload with no parameters
    AdcPeriph<ADC_1>::start_dma(adc_raw.data(), LL_DMA_STREAM_4, LL_DMA_CHANNEL_0, DMA2_Stream4_IRQn);
}

void Controls::read()
{
    //Todo: find an STL way to do this, apply add_val function to each element of adc_raw and store result in cv.val:
    auto raw_val = Controls::adc_raw.begin();
    for (auto cv : Controls::CV) {
        cv.oversampler.add_val(*raw_val++);
    }


        //read_rotary
        // Controls::rotary_turn[0] = read_rotary(0);
        //todo: use queue, from SWN

        //read_button
        //Todo: same as SEG
        // uint32_t new_state = get_button_state(0);
        // if (Controls::rotary_button[0].state && !new_state)
        // {
        //     rotary_button[0].just_pressed = 1;
        //     //..
        // }
}

extern "C" void DMA2_Stream4_IRQHandler(void)
{
    if (LL_DMA_IsActiveFlag_TC4(DMA2)) {
        LL_DMA_ClearFlag_TC4(DMA2);
        Controls::read();
    }
    // if (LL_DMA_IsActiveFlag_HT4(DMA2)) {
    //     LL_DMA_ClearFlag_HT4(DMA2);
    // }
    if (LL_DMA_IsActiveFlag_TE4(DMA2)) {
        LL_DMA_ClearFlag_TE4(DMA2);
    }
}

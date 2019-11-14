#include "stm32f7xx_ll_dma.h"
#include "controls.hh"
#include "adc_builtin_driver.hh"

const uint32_t kOverSampleBits = 3;
const uint32_t kOverSampleAmt = 8;
const uint32_t kNumAdcChannels = 4;

uint16_t Controls::adc_raw[kNumAdcChans];
CVJack Controls::CV[4];
int32_t Controls::rotary_turn[2]; //-1, 0, 1
Button Controls::rotary_button[2]; //0, 1
TouchCtl Controls::pads;

Controls::Controls()
{
    ADC_.add_channel(adcc[0]);
    ADC_.add_channel(adcc[1]);
    ADC_.add_channel(adcc[2]);
    ADC_.add_channel(adcc[3]);
    ADC_.start(adc_raw);
}

extern "C" void DMA2_Stream4_IRQHandler(void) {
    static uint32_t lpf_i = 0;
    uint32_t i;
    if (LL_DMA_IsActiveFlag_TC4(DMA2) == 1)
    {
        LL_DMA_ClearFlag_TC4(DMA2);

        for (i = 0; i < kNumAdcChannels; i++)
        {
            Controls::CV[i].rawval = Controls::adc_raw[i];
            Controls::CV[i].os_buffer += Controls::adc_raw[i];
        }
        if (++lpf_i >= kOverSampleAmt)
        {
            lpf_i = 0;
            for (i = 0; i < kNumAdcChannels; i++)
                Controls::CV[i].os_val = Controls::CV[i].os_buffer >> kOverSampleBits;
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
}

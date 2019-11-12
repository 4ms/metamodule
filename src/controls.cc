#include "controls.hh"
#include "adc_builtin_driver.h"

const uint32_t kOverSampleBits = 3;
const uint32_t kOverSampleAmt = 8;

extern "C" void DMA2_Stream4_IRQHandler(void)
{
    static uint32_t lpf_i = 0;
    uint32_t i;

    for (i = 0; i < NUM_ADCS; i++)
    {
        Controls::adc_[i].rawval = Controls::adc_buffer[i];
        Controls::adc_[i].lpf_accum += Controls::adc_buffer[i];
        if (lpf_i >= kOverSampleAmt)
        {
            lpf_i = 0;
            Controls::adc_[i].lpf_val = Controls::adc_[i].lpf_accum >> kOverSampleBits;
        }
    }
    //read_rotary
    Controls::rotary_turn[0] = read_rotary(0);
    //todo: use queue, from SWN

    //read_button
    //Todo: same as SEG
    uint32_t new_state = get_button_state(0);
    if (Controls::rotary_button[0].state && !new_state)
    {
        rotary_button[0].just_pressed = 1;
        //..
    }
}

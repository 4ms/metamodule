#include "stm32f7xx_ll_dma.h"
#include "controls.hh"
#include "debug.hh"

const uint32_t kNumAdcChannels = 4;

// std::array<uint16_t, kNumAdcChannels> Controls::adc_raw;
// std::array<CVJack, kNumAdcChannels> Controls::CV;
int32_t Controls::rotary_turn[2]; //-1, 0, 1
Button Controls::rotary_button[2]; //0, 1
TouchCtl Controls::pads;


//controls.read():
//read CV jack --> update controls.cv[].rawval   				?====>params with raw values (is there HW oversampling?)
//read rotary pins ---> update controls.rotary[].turned = +/-1     ?====> params.freq/res with +1, -1
//read rotary buttons ---> update controls.rotary[].pushed
//check ALERT pin --> initiate I2C read over DMA/IT
//check new value from DMA/IT TC IRQ -->> update controls.pad[].touching

void Controls::read()
{
    Debug::set(0,0);
    freq1CV.read();
    freq2CV.read();
    res1CV.read();
    res2CV.read();
	Debug::set(0,1);
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

Controls::Controls()
{
    AdcPeriph<ADC_1>::start_dma(adc_raw.data(), LL_DMA_STREAM_4, LL_DMA_CHANNEL_0, DMA2_Stream4_IRQn);
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

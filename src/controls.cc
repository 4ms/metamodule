#include "stm32f7xx_ll_dma.h"
#include "controls.hh"
#include "debug.hh"

//Controls::read()
//read CV jack --> update controls.CV*   				?====>params with raw values
//read rotary pins ---> update controls.rotary[].turned = +/-1     ?====> params.freq/res with +1, -1
//read rotary buttons ---> update controls.rotary[].pushed
//check ALERT pin --> initiate I2C read over DMA/IT
//check new value from DMA/IT TC IRQ -->> update controls.pad[].touching

void Controls::read()
{
    Debug::set(0,true);
    freq1CV.read();
    freq2CV.read();
    res1CV.read();
    res2CV.read();
    pads.check_alert_received();
	Debug::set(0,false);

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
    //Todo: wrap this in a member function of Controls
    AdcPeriph<AdcPeriphNum::ADC_1>::start_dma(LL_DMA_STREAM_4, LL_DMA_CHANNEL_0, DMA2_Stream4_IRQn);
}

//every 11.6us (86.2kHz), ~400ns
extern "C" void DMA2_Stream4_IRQHandler(void)
{
    if (LL_DMA_IsActiveFlag_TC4(DMA2)) {
        LL_DMA_ClearFlag_TC4(DMA2);
        Controls::read();
    }
    if (LL_DMA_IsActiveFlag_TE4(DMA2)) {
        LL_DMA_ClearFlag_TE4(DMA2);
        //Todo: Handle ADC DMA error
    }
}

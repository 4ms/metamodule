#include <stm32f7xx.h>
#include "touch.hh"

class Controls
{
public:
    Controls()
    {
    }
    struct Button
    {
        uint32_t just_pressed;
        uint32_t just_released;
        uint32_t state;
    };

    struct AdcVals
    {
        uint16_t rawval;
        uint32_t lpf_accum;
        uint16_t lpf_val;
    };
    static AdcVals adc_[NUM_ADCS];

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;
};

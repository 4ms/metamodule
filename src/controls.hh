#include <stm32f7xx.h>
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_adc.h"
#include "adc_builtin_driver.hh"
#include "touch.hh"
#include "filter.hh"
// #include "easiglib/util.hh"

#include <array>

// ADC_TypeDef * const CV_ADC = ADC1;
const uint32_t kNumAdcChans = 4;
const int kOverSampleAmt = 4;

//Todo: put Button and CVJack in their own files
struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};

struct CVJack {
    bool plugged;
    uint32_t val;
    Oversampler<uint16_t, kOverSampleAmt> oversampler;
};

//Controls class reads raw hardware, does fast conditioning (debouncing), and stores values into objects representing each hardware object
class Controls {
public:
    Controls();
    static void read();

public:
    static std::array<uint16_t, kNumAdcChans> adc_raw;
    static std::array<CVJack, kNumAdcChans> CV;

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;
};

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

struct Button {
    uint32_t just_pressed;
    uint32_t just_released;
    uint32_t state;
};


using CVJack = Oversampler<uint16_t, kOverSampleAmt>;

class Controls {
public:
    Controls();
    static void read();

private:
    // sAdcPeriph<ADC_1> ADC_;

    //todo: ADcChan constructor calls add_channel():
    //how to connect to AdcPeriph?
    //AdcPeriph<ADC1, 4/*#channels*/> {freq1cv_adc, res1cv_adc, freq2cv_adc, res2cv_adc};
    //AdcChan freq1adc {ADC1, freq1cv_adc_init};
    //or
    //AdcPeriph ADC_{Adc1 /*enum for 1*/};
    //AdcChan<Adc1, AdcChan0> freq1cv {freq1cv_pin}; //or
    //AdcChan freq1cv {Adc1, AdcChan0, freq1cv_pin};

public:
    static std::array<uint16_t, kNumAdcChans> adc_raw;
    static std::array<CVJack, kNumAdcChans> CV;

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;
};

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
    // CVJack(AdcChan<adc_n> &adcchan) : adc(adcchan) {}

    bool plugged;
    template <enum AdcPeriphNums adc_n> static AdcChan<adc_n> &adc;
    Oversampler<uint16_t, kOverSampleAmt> oversampler;
};

// template<> AdcChan<ADC_1>& CVJack::adc = {ADCChan10, {LL_GPIO_PIN_0, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};


// template <int adc_enum>
// struct CVJack_n {
//     bool plugged;

// };
//Ideal:
/*
const CVJack freq1CV {...};
const CVJack res1CV ...
...

class Controls{
    CVJack CV[4] = {freq1CV, res1CV, freq2CV, res2CV};
    JackSense CVsense[4] = {in1sense, in2sense, out1freq2sense, res2sense};
    Rotary rotary[2] = {rotary1, rotary2};
    Button rotary_press[2] = {}...;

//or
    AdcChan<ADC_1> freq1Adc {...};
    CVJack freq1CV = {freq1Adc, };

    AdcChan<ADC_1> res1Adc {ADCChan11, {LL_GPIO_PIN_1, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    CVJack freq2CV = {res1Adc, };
    ...
    //then in Controls::read(), do:
    freq1CV.oversampler.add_value(freq1CV.adc.get());
    freq2CV.oversampler.add_value(freq2CV.adc.get());

    or 

    CVJack::CVJack(enum CVJackNames cvjackname) : cvjackname_(cvjackname) {};

    AdcChan<ADC_1>
    freq2CV.oversampler.add_value(adc.get(freq2CV.get_cvjackname()));

}
*/

//Controls class reads raw hardware, does fast conditioning (debouncing), and stores values into objects representing each hardware object
class Controls {
public:
    Controls();
    static void read();

public:
    //Note: constructor adds channel to AdcPeriph, destructor does nothing (channels can't be removed)
    //Todo: seems like these are created and copied. Use R-value reference to move
    AdcChan<ADC_1> freq1cv_adc = {ADCChan10, {LL_GPIO_PIN_0, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> res1cv_adc = {ADCChan11, {LL_GPIO_PIN_1, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> freq2cv_adc = {ADCChan12, {LL_GPIO_PIN_2, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};
    AdcChan<ADC_1> res2cv_adc = {ADCChan13, {LL_GPIO_PIN_3, GPIOC, ANALOG}, LL_ADC_SAMPLINGTIME_144CYCLES};


    static std::array<uint16_t, kNumAdcChans> adc_raw;
    static std::array<CVJack, kNumAdcChans> CV;

    static int32_t rotary_turn[2];  //-1, 0, 1
    static Button rotary_button[2]; //0, 1
    static TouchCtl pads;
};

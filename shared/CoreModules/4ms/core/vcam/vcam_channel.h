#pragma once

#include "Tables.h"

class Channel
{
public:
    Channel()
        : potValue(0.f), inputValue(0.f), outputValue(0.f), controlValue(0.f) {

    }

    void input(float input) {
        inputValue = input;
    }

    void pot(float pot) {
        potValue = pot;
    }

    void control(float control) {
        controlValue = control;
    }

    float output(void) {
        outputValue = inputValue * VoltageToGainTable.lookup(potValue * controlValue);

        return outputValue;
    }

    float getLEDbrightness(void) {
        return VoltageToGainTable.lookup(potValue * controlValue);
    }

private:
float potValue;
float inputValue;
float outputValue;
float controlValue;
};

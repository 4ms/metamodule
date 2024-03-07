#pragma once

#include "Tables.h"

class Channel
{
public:
    Channel()
        : controlPatched(false), potValue(0.f), inputValue(0.f), outputValue(0.f) {

    }

    void input(float input) {
        inputValue = input;
    }

    void pot(float pot) {
        potValue = pot;
    }

    void setControlPatched(bool isPatched) {
        controlPatched = isPatched;
    }

    float output(void) {
        if(controlPatched) {
            outputValue = inputValue;
        } else {
            outputValue = inputValue * VoltageToGainTable.lookup(potValue * 5.f);
        }

        return outputValue;
    }

private:
bool controlPatched;
float potValue;
float inputValue;
float outputValue;
};

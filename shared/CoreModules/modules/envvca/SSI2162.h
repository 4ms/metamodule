#pragma once

#include <cmath>

class SSI2162
{
public:
    SSI2162() : scalingFactor(1.0)
    {        
    }

    void setScaling(float gainInV)
    {
        scalingFactor = std::pow(10.0f, -33e-3 * gainInV / 20.0f);
    }

    float process(float input) const
    {
        return input * scalingFactor;
    }

private:
    float scalingFactor;
};
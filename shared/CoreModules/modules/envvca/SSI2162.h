#pragma once

#include "gcem/include/gcem.hpp"
#include <cmath>
#include <algorithm>

class SSI2162
{
public:
    SSI2162() : scalingFactor(1.0)
    {        
    }

    void setScaling(float gainInV)
    {
        auto gainIndB = gainInV / -33e-3f;

        gainIndB = std::clamp(gainIndB, -100.0f, 20.0f);

        scalingFactor = gcem::pow(10.0f, gainIndB / 20.0f);

        // printf("Gain %.2fV -> %.2f dB -> scaling %.4f\n", gainInV, gainIndB, scalingFactor);
    }

    float process(float input) const
    {
        return input * scalingFactor;
    }

private:
    float scalingFactor;
};

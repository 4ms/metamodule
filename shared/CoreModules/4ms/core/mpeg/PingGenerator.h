#pragma once

#include <cstdio>
#include <cmath>
#include <optional>

class PingGenerator
{
public:
    PingGenerator() : taps{0}, phase(0.f), lastUpdate(0), periodOrigin(NONE), isFreeRunning(true)
    {
    }


    void tap(uint32_t now)
    {
        auto newPeriod = now - taps[1];
        auto previousPeriod = taps[1] - taps[0];

        auto periodRatio = float(newPeriod) / float(previousPeriod);

        if (periodRatio <= 1.f + maxTapOffset && periodRatio >= 1.f - maxTapOffset)
        {
            period = (newPeriod + previousPeriod) / 2.f;
        }
        else
        {
            period = float(newPeriod);
        }

        periodOrigin = TAP;

        taps[0] = taps[1];
        taps[1] = now;

        phase = 0.f;
    }

    void ping(uint32_t now)
    {
        if (previousPing.has_value())
        {
            period = now - *previousPing;
            periodOrigin = PING;
        }
            
        previousPing = now;

        phase = 0.f;
    }

    void update(uint32_t now)
    {
        if(period.has_value())
        {
            auto phaseIncrement = (now - lastUpdate) / *period;

            phase += phaseIncrement;

            if (periodOrigin == TAP)
            {
                phase = std::fmod(phase, 1.0f);
            }
            else if (periodOrigin == PING && isFreeRunning)
            {
                phase = std::fmod(phase, 1.0f);
            }


            lastUpdate = now;
        }
    }

    void reset()
    {
        period.reset();
    }

    void setFreeRunning(bool val)
    {
        isFreeRunning = val;
    }

    float getPhase()
    {
        return phase;
    }

private:
    std::array<uint32_t, 2> taps;
    std::optional<uint32_t> previousPing;
    float phase;
    uint32_t lastUpdate;
    bool isFreeRunning;
    std::optional<float> period;

private:
    enum PeriodOrigin_t {TAP, PING, NONE};
    PeriodOrigin_t periodOrigin;


private:
    static constexpr float maxTapOffset = 0.1;

};
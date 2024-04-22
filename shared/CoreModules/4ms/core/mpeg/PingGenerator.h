#pragma once

#include <cstdio>
#include <cmath>
#include <optional>

class PingGenerator
{
public:
    PingGenerator() : taps{0}, phase(0.f), phaseTap(0.f), lastUpdate(0), periodOrigin(NONE), isFreeRunning(true)
    {
    }


    void tap(uint32_t now)
    {
        auto newTapPeriod = now - taps[1];
        auto previousTapPeriod = taps[1] - taps[0];

        auto periodRatio = float(newTapPeriod) / float(previousTapPeriod);

        if (periodRatio <= 1.f + maxTapOffset && periodRatio >= 1.f - maxTapOffset)
        {
            periodTap = (newTapPeriod + previousTapPeriod) / 2.f;
        }
        else
        {
            periodTap = float(newTapPeriod);
        }

        periodOrigin = TAP;

        taps[0] = taps[1];
        taps[1] = now;

        phase = 0.f;
        phaseTap = 0.f;
    }

    void ping(uint32_t now)
    {
        if (previousPing.has_value())
        {
            periodPing = now - *previousPing;
            periodOrigin = PING;
        }
            
        previousPing = now;

        phase = 0.f;
    }

    void update(uint32_t now)
    {
        if (periodOrigin == TAP)
        {
            if (periodTap.has_value())
            {
                auto phaseIncrement = (now - lastUpdate) / *periodTap;
                phase += phaseIncrement;
                phase = std::fmod(phase, 1.0f);
            }
        }
        else if (periodOrigin == PING)
        {
            if (periodPing.has_value())
            {
                auto phaseIncrement = (now - lastUpdate) / *periodPing;
                phase += phaseIncrement;
            }

            if (isFreeRunning)
            {
                phase = std::fmod(phase, 1.0f);
            }
        }

        if (periodTap.has_value())
        {
            auto phaseIncrement = (now - lastUpdate) / *periodTap;
            phaseTap += phaseIncrement;
            phaseTap = std::fmod(phaseTap, 1.0f);
        }


        lastUpdate = now;
    }

    void reset()
    {
        periodTap.reset();
        periodPing.reset();
    }

    void setFreeRunning(bool val)
    {
        isFreeRunning = val;
    }

    float getPhase()
    {
        return phase;
    }

    float getPhaseTap()
    {
        return phaseTap;
    }

private:
    std::array<uint32_t, 2> taps;
    std::optional<uint32_t> previousPing;
    float phase;
    float phaseTap;
    uint32_t lastUpdate;
    bool isFreeRunning;
    std::optional<float> periodTap;
    std::optional<float> periodPing;

private:
    enum PeriodOrigin_t {TAP, PING, NONE};
    PeriodOrigin_t periodOrigin;


private:
    static constexpr float maxTapOffset = 0.1;

};
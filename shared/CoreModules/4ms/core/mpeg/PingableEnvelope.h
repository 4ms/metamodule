#pragma once

#include <cstdio>

class PingableEnvelope
{
private:
    enum SlopeState_t {IDLE, RISING, FALLING};
    using timestamp_t = uint32_t;

public:
    PingableEnvelope() : periodInTicks(0), phase(0.f), running(false), lastUpdate(0)
    {        
    };

    void start()
    {
        phase = 0.f;
        running = true;
    }

    void update(timestamp_t now)
    {
        if (running && lastUpdate.has_value())
        {
            float phaseIncrement = float(now - *lastUpdate) / float(periodInTicks);
            phase += phaseIncrement;

            if(phase >= 1.0f)
            {
                phase = 0.f;
                running = false; 
            }
        }

        lastUpdate = now;
    }

    float getPhase()
    {
        return phase;
    }

    void setPeriod(timestamp_t valueInTicks)
    {
        periodInTicks = valueInTicks;
    }

    bool isRunning()
    {
        return running;
    }

private:
    timestamp_t periodInTicks;
    float phase;
    bool running;
    std::optional<timestamp_t> lastUpdate;
};

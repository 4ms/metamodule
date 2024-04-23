#pragma once

#include <cstdio>

class PingableEnvelope
{
private:
    enum SlopeState_t {IDLE, RISING, FALLING};
    using timestamp_t = uint32_t;

public:
    PingableEnvelope() : periodInTicks(0), phase(0.f), running(false), stopped(false), hold(false), lastUpdate(0)
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

            if (hold == true && phase <= 0.5f && phase + phaseIncrement > 0.5f)
            {
                //hold
            }
            else
            {
                phase += phaseIncrement;
            }

            if(phase >= 1.0f)
            {
                phase = 0.f;
                running = false; 
                stopped = true;
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

    void setHold(bool val)
    {
        hold = val;
    }

    bool stoppedAfterLastUpdate()
    {
        if (stopped == true)
        {
            stopped = false;
            return true;
        }

        return stopped;
    }

private:
    timestamp_t periodInTicks;
    float phase;
    bool running;
    bool stopped;
    bool hold;
    std::optional<timestamp_t> lastUpdate;
};

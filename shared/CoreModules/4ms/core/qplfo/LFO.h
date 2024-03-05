#include <cmath>
#include <optional>

class LFO
{
public:
    using Timestamp_t = uint32_t;

public:
    LFO() : phase(0)
    {

    }

    void update(Timestamp_t now)
    {
        auto timeIncrement = now - lastUpdateTime;
        lastUpdateTime = now;

        if (periodLength)
        {
            auto phaseIncrement = float(timeIncrement) / float(*periodLength);

            phase = std::fmod(phase + phaseIncrement, 1.0f);
        }
    }

    void setPeriodLength(Timestamp_t val)
    {
        periodLength = val;
    }

    float getPhase()
    {
        return phase;
    }

    float getValue()
    {
        return phase;
    }

private:
    float phase;

    Timestamp_t lastUpdateTime;

    std::optional<Timestamp_t> periodLength;

};
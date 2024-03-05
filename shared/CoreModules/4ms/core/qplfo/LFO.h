#include <cmath>
#include <optional>
#include <numeric>
#include "../helpers/mapping.h"

namespace QPLFO
{
struct FadeTableRange {
	static constexpr float min = 0.0f;
	static constexpr float max = 1.0f;
};

constinit auto QuarticFadeTable =
Mapping::LookupTable_t<50>::generate<FadeTableRange>([](auto val) {
    val = 1.0f - val;
    return val * val * val * val;
});

class LFO
{
public:
    using Timestamp_t = uint32_t;

public:
    LFO(Timestamp_t pulseWidth) : phase(0), PulseWidth(pulseWidth)
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

    void setSkew(float val)
    {
        val = std::clamp(val, 0.0f, 1.0f);

        constexpr float PulseThres    = 0.02f;
        constexpr float PlugRampThres = 0.06f;

        if (val < PulseThres)
        {
            mode = Mode_t::Pulse;
            quarticToLinearAmount = 0.0f;
            relativeRiseTime = 0.01f;
        }
        else if (val < PlugRampThres)
        {
            mode = Mode_t::Fade;
            quarticToLinearAmount = (val - PulseThres) / (PlugRampThres - PulseThres);
            relativeRiseTime = 0.01f;
        }
        else
        {
            auto fadePos = (val - PlugRampThres - PulseThres) / (1.0f - PlugRampThres - PulseThres);

            mode = Mode_t::Fade;
            quarticToLinearAmount = 1.0f;
            relativeRiseTime = fadePos;
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
        if (mode == Mode_t::Fade)
        {
            if (phase <= relativeRiseTime)
            {
                return phase / relativeRiseTime;
            }
            else
            {
                auto relativeFallPhase = (phase - relativeRiseTime) / (1.0f - relativeRiseTime);

                auto EnvQuad = QuarticFadeTable.lookup(relativeFallPhase);
                auto EnvLin = 1.0f - relativeFallPhase;

                return std::lerp(EnvQuad, EnvLin, quarticToLinearAmount);
            }
        }
        else
        {
            if (periodLength)
            {
                if (phase * periodLength.value() < PulseWidth)
                {
                    return 1.0f;
                }
                else
                {
                    return 0.0f;
                }
            }
            else
            {
                return 0.0f;
            }
        }
    }

private:
    float phase;

    Timestamp_t lastUpdateTime;

    std::optional<Timestamp_t> periodLength;
    float relativeRiseTime;

    float quarticToLinearAmount;
    enum Mode_t {Fade, Pulse};
    Mode_t mode;

    const Timestamp_t PulseWidth;

};
}
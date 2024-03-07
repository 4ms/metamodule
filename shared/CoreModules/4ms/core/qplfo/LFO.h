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
    LFO(Timestamp_t pulseWidth) : phase(0), PulseWidth(pulseWidth), resetLockPoint(0), phaseOffset(0)
    {
    }

    void update(Timestamp_t now)
    {
        auto timeIncrement = now - lastUpdateTime;
        lastUpdateTime = now;

        if (periodLength)
        {
            auto phaseIncrement = float(timeIncrement) / float(*periodLength);

            phase = wrapPhase(phase + phaseIncrement);
        }
    }

    void reset()
    {
        if (periodLength)
        {
            resetLockPoint = phase * periodLength.value();
            phaseOffset = phase;
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

        if (periodLength and periodLength > resetLockPoint)
        {
            // keep lock point and calculate new phase offset for new tempo
            phaseOffset = float(resetLockPoint) / float(*periodLength);
        }
        else
        {
            // lock point is larger than period
            // reset lock point
            resetLockPoint = 0;
            phaseOffset = 0;
        }
    }

    float getPhase()
    {
        return phase;
    }

    float getValue()
    {
        // work off of a new phase that includes the reset lock point
        float shiftedPhase = wrapPhase(phase - phaseOffset);

        if (mode == Mode_t::Fade)
        {
            if (shiftedPhase <= relativeRiseTime)
            {
                return shiftedPhase / relativeRiseTime;
            }
            else
            {
                auto relativeFallPhase = (shiftedPhase - relativeRiseTime) / (1.0f - relativeRiseTime);

                auto EnvQuad = QuarticFadeTable.lookup(relativeFallPhase);
                auto EnvLin = 1.0f - relativeFallPhase;

                return std::lerp(EnvQuad, EnvLin, quarticToLinearAmount);
            }
        }
        else
        {
            if (periodLength)
            {
                if (shiftedPhase * periodLength.value() < PulseWidth)
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

    static float wrapPhase(float val)
    {
        while (val < 0.0f) val += 1.0f;
        while (val >= 1.0f) val -= 1.0f;
        return val;
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

    Timestamp_t resetLockPoint;
    float phaseOffset;

};
}
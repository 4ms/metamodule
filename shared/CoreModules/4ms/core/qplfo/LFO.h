#include <cmath>
#include <optional>
#include <numeric>
#include <variant>
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
    LFO(Timestamp_t pulseWidth) : phase(0), mode(TriggerMode{}), PulseWidth(pulseWidth), resetLockPoint(0), phaseOffset(0)
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
            mode = TriggerMode{};
        }
        else if (val < PlugRampThres)
        {
            mode = ExpMode
            {
                .quarticToLinearAmount = (val - PulseThres) / (PlugRampThres - PulseThres)
            };
        }
        else
        {
            auto fadePos = (val - PlugRampThres - PulseThres) / (1.0f - PlugRampThres - PulseThres);

            mode = LinearMode
            {
                .relativeRiseTime = fadePos
            };
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

        if (periodLength)
        {
            if (std::holds_alternative<TriggerMode>(mode))
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
            else if (auto expParams = std::get_if<ExpMode>(&mode))
            {
                auto EnvQuad = QuarticFadeTable.lookup(shiftedPhase);
                auto EnvLin = 1.0f - shiftedPhase;

                return std::lerp(EnvQuad, EnvLin, expParams->quarticToLinearAmount);
            }
            else if (auto linParams = std::get_if<LinearMode>(&mode))
            {
                if (shiftedPhase <= linParams->relativeRiseTime)
                {
                    return shiftedPhase / linParams->relativeRiseTime;
                }
                else
                {
                    auto relativeFallPhase = (shiftedPhase - linParams->relativeRiseTime) / (1.0f - linParams->relativeRiseTime);

                    return 1.0f - relativeFallPhase;
                }
            }
        }

        return 0.0f;
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

    struct TriggerMode {};
    struct ExpMode
    {
        float quarticToLinearAmount;    
    };
    struct LinearMode {
        float relativeRiseTime;
    };

    using Mode_t = std::variant<TriggerMode, ExpMode, LinearMode>;
    Mode_t mode;

    const Timestamp_t PulseWidth;

    Timestamp_t resetLockPoint;
    float phaseOffset;

};
}
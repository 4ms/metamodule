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
    LFO(float pulseWidthInS) : phase(0), mode(TriggerMode{}), PulseWidthInS(pulseWidthInS), resetLockPointInS(0.f), phaseOffset(0), skewTouchedZero(true), running(false)
    {
    }

    void update(float timeStepInS)
    {
        if (periodLengthInS && running == true)
        {
            auto phaseIncrement = float(timeStepInS) / float(*periodLengthInS);

            phase += phaseIncrement;

            if (phase > 1.0f)
            {
                // phase = std::fmod(phase, 1.0f);

                // track skew touching zero
                skewTouchedZeroLastPeriod = skewTouchedZero;
                skewTouchedZero = false;

                // always set new mode on a new period
                nextMode = mode;

                running = false;
            }
        }
    }

    void reset()
    {
        if (periodLengthInS)
        {
            resetLockPointInS = phase * periodLengthInS.value();
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
            skewTouchedZero = true;
            updateMode(TriggerMode{});
        }
        else if (val < PlugRampThres)
        {
            updateMode(ExpMode
            {
                .quarticToLinearAmount = (val - PulseThres) / (PlugRampThres - PulseThres)
            });
        }
        else
        {
            auto fadePos = (val - PlugRampThres - PulseThres) / (1.0f - PlugRampThres - PulseThres);

            updateMode(LinearMode
            {
                .relativeRiseTime = fadePos
            });
        }
    }

    void setPeriodLength(float valInS)
    {
        periodLengthInS = valInS;

        if (periodLengthInS and periodLengthInS > resetLockPointInS)
        {
            // keep lock point and calculate new phase offset for new tempo
            phaseOffset = float(resetLockPointInS) / float(*periodLengthInS);
        }
        else
        {
            // lock point is larger than period
            // reset lock point
            resetLockPointInS = 0.f;
            phaseOffset = 0.f;
        }
    }

    bool hasPeriodLength()
    {
        return periodLengthInS.has_value();
    }

    float getPhase()
    {
        return phase;
    }

    bool isRunning()
    {
        return running;
    }

    void start()
    {
        phase = 0.f;
        running = true;
    }

    float getValue()
    {
        // work off of a new phase that includes the reset lock point
        float shiftedPhase = wrapPhase(phase - phaseOffset);

        if (periodLengthInS)
        {
            if (std::holds_alternative<TriggerMode>(mode))
            {
                if (shiftedPhase * periodLengthInS.value() < PulseWidthInS)
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

    struct TriggerMode
    {
    };
    struct ExpMode
    {
        float quarticToLinearAmount;    
    };
    struct LinearMode
     {
        float relativeRiseTime;
    };

    using Mode_t = std::variant<TriggerMode, ExpMode, LinearMode>;

    void updateMode(Mode_t newMode)
    {
        nextMode = newMode;

        // only switch to a non-linear mode
        // if skew touched zero in last period
        if (    std::holds_alternative<LinearMode>(mode) and
                not std::holds_alternative<LinearMode>(nextMode) and
                not skewTouchedZeroLastPeriod
            )
        {
            // do set new mode now
            // will be done on next period start
        }
        else
        {
            mode = nextMode;
        }       
    }

private:

    float phase;

    std::optional<float> periodLengthInS;

    Mode_t mode;
    Mode_t nextMode;

    const float PulseWidthInS;

    float resetLockPointInS;
    float phaseOffset;

    bool skewTouchedZero;
    bool skewTouchedZeroLastPeriod;

    bool running;


};
}
#pragma once

#include "../mpeg/main.hh"

#include "../helpers/FlipFlop.h"
#include "../helpers/EdgeDetector.h"

using namespace MetaModule::PEG;

namespace MetaModule
{

template<class Parent, class Mapping>
class PEGChannel 
{
private:
    template<Parent::Info::Elem EL>
	void setOutput(auto val)
	{
		return parent->template setOutput<EL>(val);
	}

	template<Parent::Info::Elem EL>
	auto getInput()
	{
		return parent->template getInput<EL>();
	}

	template<Parent::Info::Elem EL, typename VAL>
	void setLED(const VAL &value)
	{
		return parent->template setLED<EL>(value);
	}

	template<Parent::Info::Elem EL>
	auto getState()
	{
		return parent->template getState<EL>();
	}

private:
    Parent* parent;

public:
    PEGChannel(Parent* parent_)
        : parent(parent_), pingIn(1.f, 2.f)
        , cycleIn(1.f, 2.f)
        , triggerIn(1.f, 2.f)
        , qntIn(1.f, 2.f)
        , asyncIn(1.f, 2.f)
        , timerPhase(0)
        , timerPhaseIncrement(1.0f) {
        // TODO: maybe calling these is not required
        sideloadDrivers();
        sideloadSystemSettings();
        peg.update_all_envelopes();

        peg.settings.shift_value = 0.5f * 4095.f;
        
        peg.settings.cycle_jack_behavior = CYCLE_JACK_BOTH_EDGES_TOGGLES;
    };

    void update() {
        sideloadDrivers();
        sideloadSystemSettings();

        timerPhase += timerPhaseIncrement;
        while (timerPhase > 1.0f) {
            peg.update_all_envelopes();
            timerPhase -= 1.0f;
        }

        peg.update();
    }

    void toggleInput(auto input)
    {
        peg.digio.CycleJack.sideload_set(cycleIn(input.value_or(0.f)));
    }

    void set_samplerate(float sr) {
        timerPhaseIncrement = float(PEG::MiniPEG::kDacSampleRate) / sr;
    }

    enum MainMode {EOF_GATE, EOF_TRIG, TAP_GATE, TAP_TRIG};
    enum SecondaryMode {EOR_GATE, EOR_TRIG, HR_GATE, HR_TRIG};

    void setMainMode(MainMode mode)
    {
        if (mode == EOF_GATE or mode == TAP_GATE)
        {
            peg.settings.trigout_is_trig = 0;
        }
        else
        {
            peg.settings.trigout_is_trig = 1;
        }

        if (mode == EOF_GATE or mode == EOF_TRIG)
        {
            peg.settings.trigout_function = TRIGOUT_IS_ENDOFFALL;
        }
        else
        {
            peg.settings.trigout_function = TRIGOUT_IS_TAPCLKOUT;
        }
    }

    void setSecondaryMode(SecondaryMode mode)
    {
        if (mode == EOR_GATE or mode == HR_GATE)
        {
            peg.settings.trigout_secondary_is_trig = 0;
        }
        else
        {
            peg.settings.trigout_secondary_is_trig = 1;
        }

        if (mode == EOR_GATE or mode == EOR_TRIG)
        {
            peg.settings.trigout_secondary_function = TRIGOUT_IS_ENDOFRISE;
        }
        else
        {
            peg.settings.trigout_secondary_function = TRIGOUT_IS_HALFRISE;
        }
    }

private:
    void sideloadDrivers() {
        auto MapOutputFunc = [](auto val) -> uint16_t {
            auto result = val / CVInputFullScaleInV + 0.5f;
            return uint16_t(std::clamp(result, 0.f, 1.f) * 4095.f);
        };

        //TODO: shape is split into skew and curve
        // peg.adc_dma_buffer[CV_SHAPE] = MapOutputFunc(getInput<Mapping::ShapeCvIn>().value_or(0.f));

        //TODO: this scaling needs adjustment
        peg.adc_dma_buffer[CV_DIVMULT] = MapOutputFunc(getInput<Mapping::DivJackIn>().value_or(0.f));

        auto MapKnobFunc = [](auto val) -> uint16_t {
            return uint16_t(val * 4095.f);
        };

        peg.adc_dma_buffer[POT_SCALE] = MapKnobFunc(getState<Mapping::ScaleKnob>());
        peg.adc_dma_buffer[POT_OFFSET] = MapKnobFunc(getState<Mapping::BiNPolarButton>() == LatchingButton::State_t::DOWN ? 0.5f : 1.f);
        //TODO: shape is split into skew and curve
        // peg.adc_dma_buffer[POT_SHAPE] = MapKnobFunc(getState<Mapping::ShapeKnob>());

        peg.adc_dma_buffer[POT_DIVMULT] = MapKnobFunc(getState<Mapping::PingDivMultKnob>());

        peg.digio.PingBut.sideload_set(getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED);
        peg.digio.CycleBut.sideload_set(getState<Mapping::CycleButton>() == MomentaryButton::State_t::PRESSED);
        
        auto qntJackIn = getInput<Mapping::QntIn>().value_or(0.f);
        auto asyncJackIn = getInput<Mapping::AsyncIn>().value_or(0.f);

        auto qntRisingEdge = qntEdge(qntIn(qntJackIn));
        auto asyncRisingEdge = asyncEdge(asyncIn(asyncJackIn));

        if (qntRisingEdge) 
        {
            peg.settings.trigin_function = TRIGIN_IS_QNT;
        }
        else if(asyncRisingEdge)
        {
            peg.settings.trigin_function = TRIGIN_IS_ASYNC_SUSTAIN;
        }

        if (peg.settings.trigin_function == TRIGIN_IS_QNT)
        {
            peg.digio.TrigJack.sideload_set(qntIn(qntJackIn));
        }
        else
        {
            peg.digio.TrigJack.sideload_set(asyncIn(asyncJackIn));
        }

        // TODO: ping input originall has internal lowpass filtering
        // peg.digio.PingJack.sideload_set(pingIn(getInput<PingTrigIn>().value_or(0.f)));
        if (pingEdge(pingIn(getInput<Mapping::PingJackIn>().value_or(0.f)))) {
            peg.pingEdgeIn();
        }

        setOutput<Mapping::EoFOut>(peg.digio.EOJack.sideload_get() ? TriggerOutputInV : 0.f);

        // Secondary out with directly coupled LED
        // TODO: convert LED to unicolor
        setOutput<Mapping::SecondaryOut>(peg.digio.EOJackSecondary.sideload_get() ? TriggerOutputInV : 0.f);
        setLED<Mapping::SecondaryLight>(peg.digio.EOJackSecondary.sideload_get() ? 1.0f : 0.f);

        auto MapDACFunc = [](auto val) -> float {
            return float(val) / 4095.f;
        };

        setOutput<Mapping::EnvOut>(MapDACFunc(peg.dac_vals[0]) * EnvelopeOutFullScaleInV + EnvelopeOutOffsetInV);
        setOutput<Mapping::_5VEnvOut>(MapDACFunc(peg.dac_vals[1]) * 5.f);

        auto PWMToFloatFunc = [](uint16_t pwm_val) -> float {
            return float(pwm_val) / float(4095);
        };

        setLED<Mapping::EnvOutLight>(MapDACFunc(peg.dac_vals[1]));
        setLED<Mapping::CycleButton>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_R]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_G]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_B])});
        setLED<Mapping::PingButton>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_R]),
                                                PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_G]),
                                                PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_B])});
        setLED<Mapping::EofLight>(PWMToFloatFunc(peg.pwm_vals[PWM_EOF_LED]));

        setLED<Mapping::BiNPolarButton>(getState<Mapping::BiNPolarButton>() == LatchingButton::State_t::DOWN);
    }

    void sideloadSystemSettings() {
        peg.settings.limit_skew = getState<Mapping::SkewLimitAltParam>() == 1 ? 1 : 0;
        peg.settings.free_running_ping = getState<Mapping::FreeNRunningPingAltParam>() == 0 ? 1 : 0;
        
        // static constexpr std::array<CycleJackBehaviors, 3> CycleJackOptions{
        // 	CYCLE_JACK_RISING_EDGE_TOGGLES, CYCLE_JACK_BOTH_EDGES_TOGGLES_QNT, CYCLE_JACK_BOTH_EDGES_TOGGLES};

        // peg.settings.cycle_jack_behavior = CycleJackOptions[getState<Mapping::CycleJackModeAltParam>()];

        // static constexpr std::array<TrigInFunctions, 3> TriggerInOptions{
        // 	TRIGIN_IS_ASYNC, TRIGIN_IS_ASYNC_SUSTAIN, TRIGIN_IS_QNT};

        // peg.settings.trigin_function = TriggerInOptions[getState<Mapping::TrigJackModeAltParam>()];
    }

private:
    static constexpr float CVInputFullScaleInV = -10.0f;
    static constexpr float TriggerOutputInV = 5.0f;
    static constexpr float EnvelopeOutFullScaleInV = -20.0f;
    static constexpr float EnvelopeOutOffsetInV = 10.0f;

private:
    PEG::MiniPEG peg;

private:
    FlipFlop pingIn;
    FlipFlop cycleIn;
    FlipFlop triggerIn;
    EdgeDetector pingEdge;

    FlipFlop qntIn;
    FlipFlop asyncIn;
    EdgeDetector qntEdge;
    EdgeDetector asyncEdge;

private:
    float timerPhase;
    float timerPhaseIncrement;
};


}
#pragma once

#include "../mpeg/main.hh"

#include "../helpers/FlipFlop.h"
#include "../helpers/EdgeDetector.h"

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
        , timerPhase(0)
        , timerPhaseIncrement(1.0f) {
        // TODO: maybe calling these is not required
        sideloadDrivers();
        sideloadSystemSettings();
        peg.update_all_envelopes();
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

    void set_samplerate(float sr) {
        timerPhaseIncrement = float(PEG::MiniPEG::kDacSampleRate) / sr;
    }

private:
    void sideloadDrivers() {
        auto MapOutputFunc = [](auto val) -> uint16_t {
            auto result = val / CVInputFullScaleInV + 0.5f;
            return uint16_t(std::clamp(result, 0.f, 1.f) * 4095.f);
        };

        peg.adc_dma_buffer[CV_SHAPE] = MapOutputFunc(getInput<Mapping::ShapeCvIn>().value_or(0.f));
        peg.adc_dma_buffer[CV_DIVMULT] = MapOutputFunc(getInput<Mapping::DivIn>().value_or(0.f));

        auto MapKnobFunc = [](auto val) -> uint16_t {
            return uint16_t(val * 4095.f);
        };

        peg.adc_dma_buffer[POT_SCALE] = MapKnobFunc(getState<Mapping::ScaleKnob>());
        peg.adc_dma_buffer[POT_OFFSET] = MapKnobFunc(getState<Mapping::OffsetKnob>());
        peg.adc_dma_buffer[POT_SHAPE] = MapKnobFunc(getState<Mapping::ShapeKnob>());
        peg.adc_dma_buffer[POT_DIVMULT] = MapKnobFunc(getState<Mapping::Div_MultKnob>());

        peg.digio.PingBut.sideload_set(getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED);
        peg.digio.CycleBut.sideload_set(getState<Mapping::CycleButton>() == MomentaryButton::State_t::PRESSED);

        peg.digio.CycleJack.sideload_set(cycleIn(getInput<Mapping::CycleTrigIn>().value_or(0.f)));
        peg.digio.TrigJack.sideload_set(triggerIn(getInput<Mapping::TriggerIn>().value_or(0.f)));

        // TODO: ping input originall has internal lowpass filtering
        // peg.digio.PingJack.sideload_set(pingIn(getInput<PingTrigIn>().value_or(0.f)));
        if (pingEdge(pingIn(getInput<Mapping::PingTrigIn>().value_or(0.f)))) {
            peg.pingEdgeIn();
        }

        setOutput<Mapping::EofOut>(peg.digio.EOJack.sideload_get() ? TriggerOutputInV : 0.f);

        auto MapDACFunc = [](auto val) -> float {
            return float(val) / 4095.f;
        };

        setOutput<Mapping::EnvOut>(MapDACFunc(peg.dac_vals[0]) * EnvelopeOutFullScaleInV + EnvelopeOutOffsetInV);
        setOutput<Mapping::_5VEnvOut>(MapDACFunc(peg.dac_vals[1]) * 5.f);

        auto PWMToFloatFunc = [](uint16_t pwm_val) -> float {
            return float(pwm_val) / float(4095);
        };

        setLED<Mapping::EnvOutLight>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_R]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_G]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_ENVA_B])});
        setLED<Mapping::_5VEnvLight>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_R]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_G]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_ENVB_B])});
        setLED<Mapping::CycleButton>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_R]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_G]),
                                                    PWMToFloatFunc(peg.pwm_vals[PWM_CYCLEBUT_B])});
        setLED<Mapping::PingButton>(std::array<float, 3>{PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_R]),
                                                PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_G]),
                                                PWMToFloatFunc(peg.pwm_vals[PWM_PINGBUT_B])});
        setLED<Mapping::EofLight>(PWMToFloatFunc(peg.pwm_vals[PWM_EOF_LED]));
    }

    void sideloadSystemSettings() {
        // peg.settings.limit_skew = getState<Mapping::SkewLimitAltParam>() == 1 ? 1 : 0;
        // peg.settings.free_running_ping = getState<Mapping::FreeNRunningPingAltParam>() == 0 ? 1 : 0;
        // peg.settings.trigout_is_trig = getState<Mapping::EofJackTypeAltParam>() == 1 ? 1 : 0;

        // static constexpr std::array<TrigOutFunctions, 4> TrigOutOptions{
        // 	TRIGOUT_IS_ENDOFRISE, TRIGOUT_IS_ENDOFFALL, TRIGOUT_IS_HALFRISE, TRIGOUT_IS_TAPCLKOUT};

        // peg.settings.trigout_function = TrigOutOptions[getState<Mapping::EofJackModeAltParam>()];

        // // TODO: check if this mapping is correct
        // static constexpr std::array<CycleJackBehaviors, 3> CycleJackOptions{
        // 	CYCLE_JACK_RISING_EDGE_TOGGLES, CYCLE_JACK_BOTH_EDGES_TOGGLES_QNT, CYCLE_JACK_BOTH_EDGES_TOGGLES};

        // peg.settings.cycle_jack_behavior = CycleJackOptions[getState<Mapping::CycleJackModeAltParam>()];

        // static constexpr std::array<TrigInFunctions, 3> TriggerInOptions{
        // 	TRIGIN_IS_ASYNC, TRIGIN_IS_ASYNC_SUSTAIN, TRIGIN_IS_QNT};

        // peg.settings.trigin_function = TriggerInOptions[getState<Mapping::TrigJackModeAltParam>()];

        // peg.settings.shift_value = getState<Mapping::ShiftAltParam>() * 4095.f;
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

private:
    float timerPhase;
    float timerPhaseIncrement;
};


}
#pragma once

#include "processors/tools/schmittTrigger.h"
#include "util/math.hh"
#include "util/math_tables.hh"

class Envelope {
public:
	enum stage_t {
		ATTACK,
		HOLD,
		DECAY,
		SUSTAIN,
		RELEASE,
		IDLE
	};
private:
	stage_t stage = ATTACK;
	float sampleRate = 48000;
	float phaccu = 0;
	float increment = 0;
	float attackTime = 1000;
	float holdTime = 1000;
	float decayTime = 1000;
	float releaseTime = 1000;
	float sustainLevel = 0.5f;
	float lastSample = 0;
	float envOut = 0;
	float attackCurve = 0;
	float decayCurve = 0;
	float releaseCurve = 0;
	bool holdEnable = true;
	float attackSample = 0;

	bool lastGate;
	SchmittTrigger gateInput;

	float calcRise(float curve) {
		float rise = 0;
		float interpVal = 0.0f;
		if (curve <= 0.5f) {
			auto expoRise = pow9Table.closest(phaccu);
			interpVal = curve * 2.0f;
			rise = MathTools::interpolate(expoRise, phaccu, interpVal);
		} else {
			interpVal = curve * 2.0f - 1.0f;
			auto logRise = 1.0f - pow9Table.closest(1.0f - phaccu);
			rise = MathTools::interpolate(phaccu, logRise, interpVal);
		}

		return (MathTools::map_value(rise, 0.0f, 1.0f, attackSample, 1.0f));
	}

	float calcFall(float fallFrom, float fallTo, float curve) {
		float fall = 0;
		auto linearCurve = MathTools::map_value(phaccu, 0.0f, 1.0f, fallFrom, fallTo);

		float interpVal = 0.0f;
		if (curve <= 0.5f) {
			auto expoFall = MathTools::map_value(pow9Table.closest(1.0f - phaccu), 1.0f, 0.0f, fallFrom, fallTo);
			interpVal = curve * 2.0f;
			fall = MathTools::interpolate(expoFall, linearCurve, interpVal);
		} else {
			interpVal = curve * 2.0f - 1.0f;
			auto logFall = MathTools::map_value(pow9Table.closest(phaccu), 0.0f, 1.0f, fallFrom, fallTo);
			fall = MathTools::interpolate(linearCurve, logFall, interpVal);
		}
		return fall;
	}



public:
	bool sustainEnable = true;

	Envelope() = default;

	stage_t getStage() {
		return stage;
	}

	float update(float input) {
		lastGate = gateInput.output();
		gateInput.update(input);

		// Rising edge
		if (gateInput.output() > lastGate) {
			phaccu = 0;
			stage = ATTACK;
			attackSample = lastSample;
		}

		if (stage == SUSTAIN) {
			envOut = sustainLevel;

			// End Sustain if gate is low
			if (!gateInput.output())
				stage = RELEASE;

		} else if (stage == IDLE) {
			envOut = 0.f;

		} else {

			switch (stage)
			{
			case ATTACK:
				increment = 1000.0f / attackTime / sampleRate;
				break;
			case HOLD:
				increment = 1000.0f / holdTime / sampleRate;
				break;
			case DECAY:
				increment = 1000.0f / decayTime / sampleRate;
				break;
			case RELEASE:
				increment = 1000.0f / releaseTime / sampleRate;
				break;
			default:
				break;
			}		

			phaccu += increment;
			if (phaccu >= 1.0f) {
				if (stage == ATTACK)
					stage = holdEnable ? HOLD : DECAY;
				else if (stage == HOLD)
					stage = DECAY;
				else if (stage == DECAY)
					stage = gateInput.output() ? SUSTAIN : RELEASE;
				else if (stage == SUSTAIN)
					stage = RELEASE;
				else if (stage == RELEASE)
					stage = IDLE;
				else
					stage = IDLE;

				phaccu = 0;
			}

			if (stage == ATTACK)
				envOut = calcRise(attackCurve);

			else if (stage == HOLD)
				envOut = 1.0f;

			else if (stage == DECAY)
				envOut = calcFall(1.0f, sustainLevel, decayCurve);

			else if (stage == RELEASE)
				envOut = calcFall(sustainLevel, 0.0f, releaseCurve);
		}

		lastSample = envOut;
		return envOut;
	}

	void set_envelope_time(stage_t _envStage, float milliseconds) {
		switch (_envStage)
		{
		case ATTACK:
			attackTime = milliseconds;
			break;
		case HOLD:
			holdTime = milliseconds;
			if (holdTime < 0.1f) {
				holdEnable = false;
			} else {
				holdEnable = true;
			}
			break;
		case DECAY:
			decayTime = milliseconds;
			break;
		case RELEASE:
			releaseTime = milliseconds;
			break;
		default:
			break;
		}
	}

	void set_envelope_time(int _envStage, float milliseconds) {
		switch (_envStage)
		{
		case 0:
			attackTime = milliseconds;
			break;
		case 1:
			holdTime = milliseconds;
			if (holdTime < 0.1f) {
				holdEnable = false;
			} else {
				holdEnable = true;
			}
			break;
		case 2:
			decayTime = milliseconds;
			break;
		case 3:
			releaseTime = milliseconds;
			break;
		default:
			break;
		}
	}

	void set_samplerate(float sr) {
		sampleRate = sr;
	}

	void set_sustain(float _sustainLevel) {
		sustainLevel = _sustainLevel;
	}

	void set_attack_curve(float val) {
		attackCurve = val;
	}

	void set_decay_curve(float val) {
		decayCurve = val;
	}

	void set_release_curve(float val) {
		releaseCurve = val;
	}
};

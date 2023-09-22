#pragma once

#include "processors/tools/windowComparator.h"
#include "util/math.hh"
#include "util/math_tables.hh"

class Envelope {
private:
	int stage = 0;
	float sampleRate = 48000;
	float phaccu = 0;
	float increment = 0;
	float envTimes[4] = {1000, 1000, 1000, 1000};
	float sustainLevel = 0.5f;
	float lastSample = 0;
	float envOut = 0;
	float attackCurve = 0;
	float decayCurve = 0;
	float releaseCurve = 0;
	bool holdEnable = true;
	float attackSample = 0;

	bool lastGate;
	WindowComparator gateInput;

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

	int getStage() {
		return stage;
	}

	float update(float input) {
		lastGate = gateInput.output();
		gateInput.update(input);

		// Rising edge
		if (gateInput.output() > lastGate) {
			phaccu = 0;
			stage = Attack;
			attackSample = lastSample;
		}

		if (stage == Sustain) {
			envOut = sustainLevel;

			// End Sustain if gate is low
			if (!gateInput.output())
				stage = Release;

		} else if (stage > Release) {
			envOut = 0.f;

		} else {
			int stageSelect = stage == Release ? 3 : stage;
			increment = 1000.0f / envTimes[stageSelect] / sampleRate;

			phaccu += increment;
			if (phaccu >= 1.0f) {

				if (stage == Attack)
					stage = holdEnable ? Hold : Decay;

				else if (stage == Decay)
					stage = gateInput.output() ? Sustain : Release;

				else
					stage++;

				phaccu = 0;
			}

			if (stage == Attack)
				envOut = calcRise(attackCurve);

			else if (stage == Hold)
				envOut = 1.0f;

			else if (stage == Decay)
				envOut = calcFall(1.0f, sustainLevel, decayCurve);

			else if (stage == Release)
				envOut = calcFall(sustainLevel, 0.0f, releaseCurve);
		}

		lastSample = envOut;
		return envOut;
	}

	void set_envelope_time(int _envStage, float milliseconds) {
		envTimes[_envStage] = milliseconds;
		if (_envStage == Hold) // hold stage
		{
			if (milliseconds < 0.1f) {
				holdEnable = false;
			} else {
				holdEnable = true;
			}
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

	enum {
		Attack = 0,
		Hold = 1,
		Decay = 2,
		Sustain = 3,
		Release = 4,
	};
};

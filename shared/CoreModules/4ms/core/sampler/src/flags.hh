#pragma once
#include <array>
#include <cstdint>

namespace SamplerKit
{
enum class Flag : uint32_t {
	LatchVoltOctCV,
	RevTrig,
	PlayBut,
	PlayTrigDelaying,
	PlayTrig,
	RecBut,
	RecTrig,
	ToggleLooping,
	PlayBuffDiscontinuity,
	ForceFileReload,
	ChangePlaytoPerc,
	PlayBankChanged,
	PlaySampleChanged,
	PlaySampleChangedValid,
	PlaySampleChangedEmpty,
	PlaySampleChangedValidBright,
	PlaySampleChangedEmptyBright,

	RecStartedWithTrigger,

	EnterPlayMode,
	EnterRecordMode,

	EnterCVCalibrateMode,
	StepCVCalibration, // Buttons -> CV Cal
	CVCalibrateAllJacks,
	CVCalibrationSuccess,
	CVCalibrationFail,

	CVCalibrationStep1Animate,
	CVCalibrationStep2Animate,
	CVCalibrationSuccessAnimate,
	CVCalibrationFailAnimate,
	CVCalibrateAllJacksAnimate,

	ToggleStereoMode,
	ToggleStereoModeAnimate,

	EnterLEDCalibrateMode,

	StartFadeUp,   // env_level => 0
	StartFadeDown, // env_level => 1

	EndOutShort,
	EndOutLong,

	BankNext,
	BankPrev,
	BankReleased,

	StartupParsing,
	StartupLoadingIndex,
	StartupNewIndex,
	StartupWritingIndex,
	StartupWritingHTML,
	StartupDone,

	WriteSettingsToSD,
	WriteIndexToSD,

	NUM_FLAGS
};

struct Flags {
	using flag_base_t = uint32_t;
	constexpr static auto NumFlags = static_cast<flag_base_t>(Flag::NUM_FLAGS);

private:
	constexpr static unsigned FlagsPerGroup = sizeof(flag_base_t) * 8;
	constexpr static unsigned NumFlagGroups = (NumFlags - 1) / FlagsPerGroup + 1;

	static constexpr flag_base_t flagnum(Flag flag) {
		return static_cast<flag_base_t>(flag);
	}
	static constexpr unsigned groupnum(Flag flag) {
		return flagnum(flag) / FlagsPerGroup;
	}
	static flag_base_t bit(Flag b) {
		return flag_base_t(1) << (flagnum(b) - (groupnum(b) * FlagsPerGroup));
	}

	flag_base_t &flaggroup(Flag flag) {
		return _flags[groupnum(flag)];
	}

	std::array<flag_base_t, NumFlagGroups> _flags{};

public:
	void set(Flag flag) {
		flaggroup(flag) |= bit(flag);
	}

	void clear(Flag flag) {
		flaggroup(flag) &= ~bit(flag);
	}

	bool read(Flag flag) {
		return flaggroup(flag) & bit(flag);
	}

	bool take(Flag flag) {
		if (read(flag)) {
			clear(flag);
			return true;
		}
		return false;
	}
};
} // namespace SamplerKit


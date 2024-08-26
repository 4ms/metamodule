#pragma once
#include <cstdint>

namespace MetaModule
{

struct STSChanMapping {
	uint8_t PitchKnob;
	uint8_t SampleKnob;
	uint8_t StartPosKnob;
	uint8_t LengthKnob;
	uint8_t PlayButton;
	uint8_t BankButton;
	uint8_t ReverseButton;
	uint8_t PlayTrigIn;
	uint8_t VOctIn;
	uint8_t ReverseTrigIn;
	uint8_t LengthCvIn;
	uint8_t StartPosCvIn;
	uint8_t SampleCvIn;
	uint8_t RecIn;
	uint8_t OutL;
	uint8_t OutR;
	uint8_t EndOut;
	uint8_t PlayLight;
	uint8_t PlayButR;
	uint8_t PlayButG;
	uint8_t PlayButB;
	uint8_t RevButR;
	uint8_t RevButG;
	uint8_t RevButB;
	uint8_t BankButR;
	uint8_t BankButG;
	uint8_t BankButB;
};

} // namespace MetaModule

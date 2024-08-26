#pragma once
#include "util/colors.hh"

struct SamplerColors {
	static constexpr Color off = Color(0, 0, 0);
	static constexpr Color black = Color(0, 0, 0);
	static constexpr Color grey = Color(127, 127, 127);
	static constexpr Color white = Color(255, 255, 255);

	static constexpr Color red = Color(255, 0, 0);
	static constexpr Color pink = Color(0xFF, 0x69, 0xB4);
	static constexpr Color pale_pink = Color(255, 200, 200);
	static constexpr Color tangerine = Color(255, 200, 0);
	static constexpr Color orange = Color(255, 127, 0);
	static constexpr Color yellow = Color(160, 160, 0);
	static constexpr Color green = Color(0, 130, 0);
	static constexpr Color cyan = Color(0, 160, 200);
	static constexpr Color blue = Color(0, 40, 255);
	static constexpr Color purple = Color(255, 0, 255);
	static constexpr Color magenta = Color(200, 0, 100);

	struct Bank {
		static constexpr Color white = Color(220, 220, 220);
		static constexpr Color red = Color(255, 0, 0);
		static constexpr Color orange = Color(255, 127, 0);
		static constexpr Color yellow = Color(200, 255, 0);
		static constexpr Color green = Color(0, 200, 0);
		static constexpr Color cyan = Color(0, 160, 200);
		static constexpr Color blue = Color(0, 0, 255);
		static constexpr Color pink = Color(200, 0, 200);
		static constexpr Color purple = Color(100, 50, 180);
		static constexpr Color grey = Color(100, 140, 120);
	};
};

constexpr inline Color BankColors[] = {
	SamplerColors::Bank::white,
	SamplerColors::Bank::red,
	SamplerColors::Bank::orange,
	SamplerColors::Bank::yellow,
	SamplerColors::Bank::green,
	SamplerColors::Bank::cyan,
	SamplerColors::Bank::blue,
	SamplerColors::Bank::pink,
	SamplerColors::Bank::purple,
	SamplerColors::Bank::grey,
};

#pragma once
#include <cstdint>
#include <array>

struct MMScreenBufferConf {
	static constexpr uint32_t width = 240;
	static constexpr uint32_t height = 240;
	enum Rotation { None, CW90, Flip180, CCW90 };
	static constexpr Rotation rotation = CW90;

	using FrameBufferT = std::array<uint16_t, width * height>;
};


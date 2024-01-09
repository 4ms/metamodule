#pragma once
#include "VCV_adaptor/common.hpp"

namespace rack::engine
{

struct Light {
	float value = 0.f;
	void setBrightness(float brightness) ;

	float getBrightness() ;

	void setBrightnessSmooth(float brightness, float deltaTime, float lambda = 30.f) ;

	void setSmoothBrightness(float brightness, float deltaTime) ;

	DEPRECATED void setBrightnessSmooth(float brightness, int frames = 1) ;
};

} // namespace rack::engine

#pragma once
#include <rack.hpp>

class CenterLabel : public rack::Label {
public:
	CenterLabel() = default;
	void draw(const DrawArgs &args) override;
};

#include <ui/Label.hpp>

namespace rack::ui
{

Label::Label() {
	box.size = math::Vec(40, 13);
	box.pos = math::Vec(0, 0);
	fontSize = 12;
	lineHeight = 1.f; //not used
	color = nvgRGBA(0x00, 0x00, 0x00, 0xFF);
}

void Label::draw(const DrawArgs &args) {
	nvgFontFaceId(args.vg, 0); //default font handle
	nvgFontSize(args.vg, fontSize);

	auto halign = alignment == LEFT_ALIGNMENT	? NVG_ALIGN_LEFT :
				  alignment == RIGHT_ALIGNMENT	? NVG_ALIGN_RIGHT :
				  alignment == CENTER_ALIGNMENT ? NVG_ALIGN_CENTER :
												  NVG_ALIGN_LEFT;
	nvgTextAlign(args.vg, halign | NVG_ALIGN_TOP);

	nvgFillColor(args.vg, color);

	nvgText(args.vg, 6, 4, text.c_str(), nullptr);
}

} // namespace rack::ui

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
				  alignment == CENTER_ALIGNMENT ? NVG_ALIGN_CENTER :
				  alignment == RIGHT_ALIGNMENT	? NVG_ALIGN_RIGHT :
												  NVG_ALIGN_LEFT;
	nvgTextAlign(args.vg, halign | NVG_ALIGN_TOP);

	nvgFillColor(args.vg, color);

	auto x_offset = alignment == LEFT_ALIGNMENT		 ? 6 :
					alignment == CENTER_ALIGNMENT	 ? 6 :
					alignment == RIGHT_ALIGNMENT	 ? 6 :
					alignment == MM_CENTER_ALIGNMENT ? 0 :
					alignment == MM_RIGHT_ALIGNMENT	 ? 0 :
													   0;

	auto y_offset = 4; // TODO: does this depend on anything?

	nvgText(args.vg, x_offset, y_offset, text.c_str(), nullptr);
}

} // namespace rack::ui

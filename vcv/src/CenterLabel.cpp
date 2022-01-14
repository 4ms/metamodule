#include "CenterLabel.hpp"
#include "plugin.hpp"

void CenterLabel::draw(const DrawArgs &args)
{
	if (centralData->isMappingInProgress() && (centralData->getMappingSource().objType == LabelButtonID::Types::Knob)) {
		nvgFillColor(args.vg, rack::color::alpha(rack::color::YELLOW, 0.8f));
	}
	nvgBeginPath(args.vg);
	nvgTextAlign(args.vg, NVGalign::NVG_ALIGN_CENTER | NVGalign::NVG_ALIGN_BOTTOM);
	nvgFillColor(args.vg, nvgRGBA(0, 0, 0, 255));
	nvgFontSize(args.vg, 8.0f);
	nvgText(args.vg, box.size.x / 2.0f, box.size.y * 0.75f, text.c_str(), NULL);
}

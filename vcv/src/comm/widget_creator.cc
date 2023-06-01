#include "widget_creator.hh"

namespace MetaModule
{

template<>
void VCVCreator::createWidget<MomentaryButton>(MomentaryButton element)
{
	num_params++;
}

template<>
void VCVCreator::createWidget<Davies1900hWhiteKnob>(Davies1900hWhiteKnob element)
{
	num_params++;
}

template<>
void VCVCreator::createWidget<Davies1900hRedKnob>(Davies1900hRedKnob element)
{
	num_params++;
}

template<>
void VCVCreator::createWidget<Davies1900hRedKnob>(Davies1900hRedKnob element)
{
	num_params++;
}

} // namespace MetaModule

#include "util/string_compare.hh"
#include <string>
#include <vector>

namespace MetaModule::ModuleTags
{

const std::vector<std::vector<std::string>> vcvTagAliases = {
	{"Arpeggiator"},
	{"Attenuator"},
	{"Blank"},
	{"Chorus"},
	{"Clock", "Clock generator"},
	{"Clock modulator"},
	{"Compressor"},
	{"Controller"},
	{"Delay"},
	{"Digital"},
	{"Distortion"},
	{"Drum", "Drums", "Percussion"},
	{"Dual"},
	{"Dynamics"},
	{"Effect"},
	{"Envelope follower"},
	{"Envelope generator"},
	{"EQ", "Equalizer"},
	{"Expander"},
	{"External"},
	{"Filter", "VCF", "Voltage controlled filter"},
	{"Flanger"},
	{"Function generator"},
	{"Granular"},
	{"Hardware clone", "Hardware"},
	{"Limiter"},
	{"Logic"},
	{"LFO", "Low-frequency oscillator", "Low frequency oscillator"},
	{"Low-pass gate", "Low pass gate", "Lowpass gate"},
	{"MIDI"},
	{"Mixer"},
	{"Multiple"},
	{"Noise"},
	{"VCO", "Oscillator", "Voltage controlled oscillator"},
	{"Panning", "Pan"},
	{"Phaser"},
	{"Physical modeling"},
	{"Polyphonic", "Poly"},
	{"Quad"},
	{"Quantizer"},
	{"Random"},
	{"Recording"},
	{"Reverb"},
	{"Ring modulator"},
	{"Sample and hold", "S&H", "Sample & hold"},
	{"Sampler"},
	{"Sequencer"},
	{"Slew limiter"},
	{"Speech"},
	{"Switch"},
	{"Synth voice"},
	{"Tuner"},
	{"Utility"},
	{"Visual"},
	{"Vocoder"},
	{"VCA", "Voltage-controlled amplifier", "Amplifier", "Voltage controlled amplifier"},
	{"Waveshaper"},
};

int tag_id(std::string_view tag) {
	for (auto tag_id = 0; auto const &tags : vcvTagAliases) {
		for (auto const &alias : tags) {
			if (equal_ci(alias, tag)) {
				return tag_id;
			}
		}
		tag_id++;
	}
	return -1;
}

std::string_view get_tag(int tag_id) {
	if (tag_id >= 0 && tag_id < (int)vcvTagAliases.size())
		return vcvTagAliases[tag_id][0];
	else
		return "";
}

std::string_view normalize_tag(std::string_view tag) {
	if (auto id = tag_id(tag); id >= 0) {
		return get_tag(id);
	} else
		return tag;
}

} // namespace MetaModule::ModuleTags

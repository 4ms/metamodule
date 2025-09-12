#include "CoreModules/elements/base_element.hh"
#include "CoreModules/hub/audio_expander_defs.hh"
#include "midi/midi_message.hh"
#include "patch/patch.hh"
#include <string>

namespace MetaModule
{

std::string get_panel_name(const BaseElement &, uint16_t) {
	return "";
}

std::string get_panel_name(const ParamElement &, uint16_t panel_id) {
	std::string name;
	name.reserve(8);

	auto mk = MappedKnob{.panel_knob_id = (uint16_t)Midi::strip_midi_channel(panel_id),
						 .midi_chan = (uint8_t)Midi::midi_channel(panel_id)};

	if (mk.is_panel_knob())
		name = PanelDef::get_map_param_name(panel_id);

	else if (auto butnum = mk.ext_button()) {
		name = "B1-1";
		name[1] = '1' + unsigned(*butnum / 8);
		name[3] = '1' + unsigned(*butnum % 8);
	}

	else if (mk.is_midi_cc())
	{
		name = "CC" + std::to_string(mk.cc_num());
		if (mk.midi_chan >= 1 && mk.midi_chan <= 16)
			name += " Ch " + std::to_string(mk.midi_chan);
	}

	else if (mk.is_midi_notegate())
	{
		name = MidiMessage::note_name(mk.notegate_num());
		if (mk.midi_chan >= 1 && mk.midi_chan <= 16)
			name += " Ch " + std::to_string(mk.midi_chan);
	}

	return name;
}

std::string get_panel_name(const JackInput &, uint16_t panel_id) {
	std::string name{16};

	if (PanelDef::is_main_panel_input(panel_id)) {
		name = PanelDef::get_map_injack_name(panel_id);
		return name;

	} else if (AudioExpander::is_expander_input(panel_id)) {
		name = AudioExpander::get_map_injack_name(AudioExpander::panel_to_exp_input(panel_id));
		return name;
	}

	auto midi_message = Midi::strip_midi_channel(panel_id);
	auto midi_chan = Midi::midi_channel(panel_id);
	std::string midi_chan_str = (midi_chan >= 1 && midi_chan <= 16) ? " Ch:" + std::to_string(midi_chan) : "";

	if (midi_message >= MidiMonoNoteJack && midi_message <= MidiNote8Jack) {
		std::string id = std::to_string(midi_message + 1 - MidiMonoNoteJack);
		name = "MIDI Note " + id + midi_chan_str;
	}

	else if (midi_message >= MidiMonoGateJack && midi_message <= MidiGate8Jack)
	{
		std::string id = std::to_string(midi_message + 1 - MidiMonoGateJack);
		name = "MIDI Gate " + id + midi_chan_str;
	}

	else if (midi_message >= MidiMonoVelJack && midi_message <= MidiVel8Jack)
	{
		std::string id = std::to_string(midi_message + 1 - MidiMonoVelJack);
		name = "MIDI Vel. " + id + midi_chan_str;
	}

	else if (midi_message >= MidiMonoAftertouchJack && midi_message <= MidiAftertouch8Jack)
	{
		std::string id = std::to_string(midi_message + 1 - MidiMonoAftertouchJack);
		name = "MIDI Aft. " + id + midi_chan_str;
	}

	else if (midi_message >= MidiMonoRetrigJack && midi_message <= MidiRetrig8Jack)
	{
		std::string id = std::to_string(midi_message + 1 - MidiMonoRetrigJack);
		name = "MIDI Ret " + id + midi_chan_str;
	}

	else if (midi_message >= MidiCC0 && midi_message <= MidiCC127)
		name = "MIDI CC " + std::to_string(midi_message - MidiCC0) + midi_chan_str;

	else if (midi_message == MidiPitchWheelJack)
		name = "MIDI Bend" + midi_chan_str;

	else if (midi_message >= MidiGateNote0 && midi_message <= MidiGateNote127)
		name = std::string("MIDI Gate ") + MidiMessage::note_name(midi_message - MidiGateNote0) + midi_chan_str;

	else if (midi_message == MidiClockJack)
		name = "MIDI Clk";

	else if (midi_message >= MidiClockDiv1Jack && midi_message <= MidiClockDiv96Jack)
		name = "MIDI Clk/" + std::to_string(midi_message - MidiClockDiv1Jack + 1);

	else if (midi_message == MidiStartJack)
		name = "MIDI Start";

	else if (midi_message == MidiStopJack)
		name = "MIDI Stop";

	else if (midi_message == MidiContinueJack)
		name = "MIDI Cont.";

	else
		name = "?";

	return name;
}

std::string get_panel_name(const JackOutput &, uint16_t panel_id) {
	std::string name{8};
	if (panel_id < PanelDef::NumUserFacingOutJacks) {
		name = PanelDef::get_map_outjack_name(panel_id);
	} else if (size_t id = panel_id - PanelDef::NumUserFacingOutJacks; id < AudioExpander::NumOutJacks) {
		name = AudioExpander::get_map_outjack_name(id);
	}
	return name;
}

std::string get_panel_brief_name(const JackOutput &, uint16_t panel_id) {
	std::string name{6};

	if (panel_id < PanelDef::NumAudioOut)
		name = std::to_string(panel_id + 1);

	else if (AudioExpander::is_expander_output(panel_id))
		name = "X" + std::to_string(panel_id + 1);

	return name;
}

std::string get_panel_brief_name(const JackInput &, uint16_t panel_id) {
	std::string name{6}; //longest: MG127\0

	if (panel_id < PanelDef::NumAudioIn)
		name = std::to_string(panel_id + 1);

	else if (panel_id < PanelDef::NumUserFacingInJacks)
		name = "G" + std::to_string(panel_id + 1 - PanelDef::NumAudioIn);

	else if (AudioExpander::is_expander_input(panel_id))
		name = "X" + std::to_string(panel_id - 1);

	else if (panel_id >= MidiMonoNoteJack && panel_id <= MidiNote8Jack) {
		std::string id = std::to_string(panel_id + 1 - MidiMonoNoteJack);
		name = "Nt" + id;
	}

	else if (panel_id >= MidiMonoGateJack && panel_id <= MidiGate8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoGateJack);
		name = "Gt" + id;
	}

	else if (panel_id >= MidiMonoVelJack && panel_id <= MidiVel8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoVelJack);
		name = "Ve" + id;
	}

	else if (panel_id >= MidiMonoAftertouchJack && panel_id <= MidiAftertouch8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoAftertouchJack);
		name = "Af" + id;
	}

	else if (panel_id >= MidiMonoRetrigJack && panel_id <= MidiRetrig8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoRetrigJack);
		name = "Rt" + id;
	}

	else if (panel_id >= MidiCC0 && panel_id <= MidiCC127)
		name = "CC" + std::to_string(panel_id - MidiCC0);

	else if (panel_id == MidiPitchWheelJack)
		name = "PW";

	else if (panel_id >= MidiGateNote0 && panel_id <= MidiGateNote127)
		name = "GN" + std::to_string(panel_id - MidiGateNote0); //TODO: C4

	else if (panel_id == MidiClockJack || panel_id == MidiClockDiv1Jack)
		name = "CK";

	else if (panel_id > MidiClockDiv1Jack && panel_id <= MidiClockDiv96Jack)
		name = "CK" + std::to_string(panel_id - MidiClockDiv1Jack + 1);

	else if (panel_id == MidiStartJack)
		name = "Sta";

	else if (panel_id == MidiStopJack)
		name = "Stp";

	else if (panel_id == MidiContinueJack)
		name = "Cnt";

	else
		name = "?";

	return name;
}

} // namespace MetaModule

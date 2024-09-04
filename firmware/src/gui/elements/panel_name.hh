#pragma once
#include "CoreModules/elements/elements.hh"
#include "patch/patch.hh"
#include <string>

//TODO: does this file belong in firmware/src/gui? Seems more closely related to CoreModules/Hub

namespace MetaModule
{

template<typename PanelDef>
std::string get_panel_name(const BaseElement &, uint16_t) {
	return "";
}

template<typename PanelDef>
std::string get_panel_name(const ParamElement &, uint16_t panel_id) {
	std::string name{8};
	auto mk = MappedKnob{.panel_knob_id = panel_id};

	if (mk.is_panel_knob())
		name = PanelDef::get_map_param_name(panel_id);

	else if (mk.is_midi_cc())
		name = "CC" + std::to_string(mk.cc_num());

	return name;
}

template<typename PanelDef>
std::string get_panel_name(const JackInput &, uint16_t panel_id) {
	std::string name{16};

	if (panel_id < PanelDef::NumUserFacingInJacks)
		name = PanelDef::get_map_injack_name(panel_id);

	else if (panel_id >= MidiMonoNoteJack && panel_id <= MidiNote8Jack) {
		std::string id = std::to_string(panel_id + 1 - MidiMonoNoteJack);
		name = "MIDI Note " + id;
	}

	else if (panel_id >= MidiMonoGateJack && panel_id <= MidiGate8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoGateJack);
		name = "MIDI Gate " + id;
	}

	else if (panel_id >= MidiMonoVelJack && panel_id <= MidiVel8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoVelJack);
		name = "MIDI Vel. " + id;
	}

	else if (panel_id >= MidiMonoAftertouchJack && panel_id <= MidiAftertouch8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoAftertouchJack);
		name = "MIDI Aft. " + id;
	}

	else if (panel_id >= MidiMonoRetrigJack && panel_id <= MidiRetrig8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoRetrigJack);
		name = "MIDI Ret " + id;
	}

	else if (panel_id >= MidiCC0 && panel_id <= MidiCC127)
		name = "MIDI CC " + std::to_string(panel_id - MidiCC0);

	else if (panel_id == MidiPitchWheelJack)
		name = "MIDI Bend";

	else if (panel_id >= MidiGateNote0 && panel_id <= MidiGateNote127)
		name = "MIDI Gate " + std::to_string(panel_id - MidiGateNote0); //TODO: C4

	else if (panel_id == MidiClockJack)
		name = "MIDI Clk";

	else if (panel_id >= MidiClockDiv1Jack && panel_id <= MidiClockDiv96Jack)
		name = "MIDI Clk/" + std::to_string(panel_id - MidiClockDiv1Jack + 1);

	else if (panel_id == MidiStartJack)
		name = "MIDI Start";

	else if (panel_id == MidiStopJack)
		name = "MIDI Stop";

	else if (panel_id == MidiContinueJack)
		name = "MIDI Cont.";

	else
		name = "?";

	return name;
}

template<typename PanelDef>
std::string get_panel_name(const JackOutput &, uint16_t panel_id) {
	std::string name{8};
	name = PanelDef::get_map_outjack_name(panel_id);
	return name;
}

template<typename PanelDef>
std::string get_panel_brief_name(const JackInput &, uint16_t panel_id) {
	std::string name{6}; //longest: MG127\0

	if (panel_id < PanelDef::NumAudioIn)
		name = std::to_string(panel_id + 1);

	else if (panel_id < PanelDef::NumUserFacingInJacks)
		name = "G" + std::to_string(panel_id + 1 - PanelDef::NumAudioIn);

	else if (panel_id >= MidiMonoNoteJack && panel_id <= MidiNote8Jack) {
		std::string id = std::to_string(panel_id + 1 - MidiMonoNoteJack);
		name = "MN"; //t" + id;
	}

	else if (panel_id >= MidiMonoGateJack && panel_id <= MidiGate8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoGateJack);
		name = "On"; //"On" + id;
	}

	else if (panel_id >= MidiMonoVelJack && panel_id <= MidiVel8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoVelJack);
		name = "Ve"; // + id;
	}

	else if (panel_id >= MidiMonoAftertouchJack && panel_id <= MidiAftertouch8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoAftertouchJack);
		name = "Af"; // + id;
	}

	else if (panel_id >= MidiMonoRetrigJack && panel_id <= MidiRetrig8Jack)
	{
		std::string id = std::to_string(panel_id + 1 - MidiMonoRetrigJack);
		name = "Re"; // + id;
	}

	else if (panel_id >= MidiCC0 && panel_id <= MidiCC127)
		name = "CC"; // + std::to_string(panel_id - MidiCC0);

	else if (panel_id == MidiPitchWheelJack)
		name = "PW";

	else if (panel_id >= MidiGateNote0 && panel_id <= MidiGateNote127)
		name = "GN"; // + std::to_string(panel_id - MidiGateNote0); //TODO: C4

	else if (panel_id == MidiClockJack || panel_id == MidiClockDiv1Jack)
		name = "CK";

	else if (panel_id > MidiClockDiv1Jack && panel_id <= MidiClockDiv96Jack)
		name = "CK"; ///" + std::to_string(panel_id - MidiClockDiv1Jack + 1);

	else if (panel_id == MidiStartJack)
		name = "Sa";

	else if (panel_id == MidiStopJack)
		name = "Sp";

	else if (panel_id == MidiContinueJack)
		name = "Ct";

	else
		name = "?";

	return name;
}
} // namespace MetaModule

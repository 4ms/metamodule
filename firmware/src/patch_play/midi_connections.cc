#include "patch_play/midi_connections.hh"
#include "pr_dbg.hh"
#include <algorithm>

namespace MetaModule
{

void MidiConnections::clear() {
	for_each_jack_vector([](auto &v) { v.clear(); });
	for_each_knob_map_vector([](auto &v) { v.clear(); });
}

bool MidiConnections::add_jack_conn(uint32_t panel_jack_id, Jack input_jack, CoreProcessor::PolyPortBuffer polybuf) {
	const auto chan = Midi::midi_channel(panel_jack_id);
	const auto ports = Midi::port_mask(panel_jack_id);

	// The 1-4 and 5-8 poly cables share the same connection vectors; poly_base selects
	// which group of MIDI poly channels (0-3 vs 4-7) the cable carries.
	constexpr uint8_t Base5_8 = Midi::MidiPolyCableChanBase;

	if (Midi::midi_note_pitch_poly(panel_jack_id)) {
		update_or_add_poly(poly_pitch_conns, input_jack, chan, ports, polybuf);
		pr_trace("MIDI note poly ch:%u", chan);

	} else if (Midi::midi_note_pitch_poly5_8(panel_jack_id)) {
		update_or_add_poly(poly_pitch_conns, input_jack, chan, ports, polybuf, Base5_8);
		pr_trace("MIDI note poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_gate_poly(panel_jack_id)) {
		update_or_add_poly(poly_gate_conns, input_jack, chan, ports, polybuf);
		pr_trace("MIDI gate poly ch:%u", chan);

	} else if (Midi::midi_note_gate_poly5_8(panel_jack_id)) {
		update_or_add_poly(poly_gate_conns, input_jack, chan, ports, polybuf, Base5_8);
		pr_trace("MIDI gate poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_vel_poly(panel_jack_id)) {
		update_or_add_poly(poly_vel_conns, input_jack, chan, ports, polybuf);
		pr_trace("MIDI vel poly ch:%u", chan);

	} else if (Midi::midi_note_vel_poly5_8(panel_jack_id)) {
		update_or_add_poly(poly_vel_conns, input_jack, chan, ports, polybuf, Base5_8);
		pr_trace("MIDI vel poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_aft_poly(panel_jack_id)) {
		update_or_add_poly(poly_aft_conns, input_jack, chan, ports, polybuf);
		pr_trace("MIDI aft poly ch:%u", chan);

	} else if (Midi::midi_note_aft_poly5_8(panel_jack_id)) {
		update_or_add_poly(poly_aft_conns, input_jack, chan, ports, polybuf, Base5_8);
		pr_trace("MIDI aft poly 5-8 ch:%u", chan);

	} else if (Midi::midi_note_retrig_poly(panel_jack_id)) {
		update_or_add_poly(poly_retrig.conns, input_jack, chan, ports, polybuf);
		pr_trace("MIDI retrig poly ch:%u", chan);

	} else if (Midi::midi_note_retrig_poly5_8(panel_jack_id)) {
		update_or_add_poly(poly_retrig.conns, input_jack, chan, ports, polybuf, Base5_8);
		pr_trace("MIDI retrig poly 5-8 ch:%u", chan);

	} else if (auto num = Midi::midi_note_pitch(panel_jack_id); num.has_value()) {
		update_or_add(note_pitch_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI note (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_gate(panel_jack_id); num.has_value()) {
		update_or_add(note_gate_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI gate (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_vel(panel_jack_id); num.has_value()) {
		update_or_add(note_vel_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI vel (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_aft(panel_jack_id); num.has_value()) {
		update_or_add(note_aft_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI aftertouch (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_note_retrig(panel_jack_id); num.has_value()) {
		update_or_add(note_retrig[num.value()].conns, input_jack, chan, ports);
		pr_trace("MIDI retrig (poly %d) ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_gate(panel_jack_id); num.has_value()) {
		update_or_add(gate_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI note %d gate ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_cc(panel_jack_id); num.has_value()) {
		update_or_add(cc_conns[num.value()], input_jack, chan, ports);
		pr_trace("MIDI CC/PW %d ch:%u", num.value(), chan);

	} else if (auto num = Midi::midi_clk(panel_jack_id); num.has_value()) {
		update_or_add(pulses[TimingEvents::Clock].conns, input_jack, 0, ports);
		pr_trace("MIDI Clk");

	} else if (auto num = Midi::midi_divclk(panel_jack_id); num.has_value()) {
		uint8_t div_event = *num == 0  ? Midi::DivClock1 :
							*num == 1  ? Midi::DivClock2 :
							*num == 2  ? Midi::DivClock3 :
							*num == 5  ? Midi::DivClock6 :
							*num == 11 ? Midi::DivClock12 :
							*num == 23 ? Midi::DivClock24 :
							*num == 47 ? Midi::DivClock48 :
							*num == 95 ? Midi::DivClock96 :
										 0xFF;
		if (div_event == 0xFF) {
			pr_err("Error: Unknown MIDI clock division: %d. Using /24\n", *num);
			div_event = Midi::DivClock24;
		}
		update_or_add(divclk_pulses[div_event].conns, input_jack, 0, ports);
		pr_trace("MIDI Div %d Clk", num.value() + 1);

	} else if (auto num = Midi::midi_transport(panel_jack_id); num.has_value()) {
		update_or_add(pulses[num.value() + TimingEvents::Start].conns, input_jack, 0, ports);
		pr_trace("MIDI %s", num.value() == 0 ? "Start" : num.value() == 1 ? "Stop" : "Cont");

	} else {
		return false;
	}

	return true;
}

void MidiConnections::erase_jack(Jack jack) {
	for_each_jack_vector([&](auto &v) { std::erase(v, jack); });
}

void MidiConnections::erase_module(unsigned module_idx) {
	for_each_jack_vector([=](auto &v) { std::erase_if(v, [=](auto &jack) { return jack.module_id == module_idx; }); });
	for_each_knob_map_vector(
		[=](auto &v) { std::erase_if(v, [=](auto &map) { return map.module_id == module_idx; }); });
}

void MidiConnections::cache_knob_map(MappedKnob const &k) {
	if (k.is_midi_cc()) {
		pr_trace("Midi Map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
		update_or_add(cc_knob_maps[k.cc_num()], k);

	} else if (k.is_midi_notegate()) {
		pr_trace("Midi Map: Note %d to m:%d p:%d\n", k.notegate_num(), k.module_id, k.param_id);
		update_or_add(note_knob_maps[k.notegate_num()], k);

	} else {
		pr_warn("Bad Midi Map: panel_knob_id:%d to m:%d p:%d\n", k.panel_knob_id, k.module_id, k.param_id);
	}
}

void MidiConnections::uncache_knob_map(MappedKnob const &k) {
	if (k.is_midi_cc()) {
		pr_trace("Midi un-map: CC%d to m:%d p:%d\n", k.cc_num(), k.module_id, k.param_id);
		std::erase_if(cc_knob_maps[k.cc_num()], [&k](auto m) { return (k.maps_to_same_as(m)); });

	} else if (k.is_midi_notegate()) {
		pr_trace("Midi un-map: Note %d to m:%d p:%d\n", k.notegate_num(), k.module_id, k.param_id);
		std::erase_if(note_knob_maps[k.notegate_num()], [&k](auto m) { return (k.maps_to_same_as(m)); });

	} else {
		pr_warn("Cannot unmap MIDI: raw panel_knob_id:%d to m:%d p:%d\n", k.panel_knob_id, k.module_id, k.param_id);
	}
}

MappedKnob *MidiConnections::find_knob_map(MappedKnob const &k) {
	auto *maps = k.is_midi_cc()		  ? &cc_knob_maps[k.cc_num()] :
				 k.is_midi_notegate() ? &note_knob_maps[k.notegate_num()] :
										nullptr;
	if (!maps)
		return nullptr;

	auto found = std::ranges::find_if(
		*maps, [&k](auto const &m) { return k.param_id == m.param_id && k.module_id == m.module_id; });

	return found != maps->end() ? &*found : nullptr;
}

bool MidiConnections::any_pulse_conns() const {
	auto any_conns = [](auto const &ps) {
		return std::ranges::any_of(ps, [](auto const &p) { return !p.conns.empty(); });
	};
	return any_conns(pulses) || any_conns(divclk_pulses) || any_conns(note_retrig) || !poly_retrig.conns.empty();
}

void MidiConnections::set_samplerate(float hz) {
	for (auto &mp : pulses)
		mp.pulse.set_update_rate_hz(hz);

	for (auto &mp : divclk_pulses)
		mp.pulse.set_update_rate_hz(hz);

	for (auto &ret : note_retrig)
		ret.pulse.set_update_rate_hz(hz);

	for (auto &p : poly_retrig.pulses)
		p.set_update_rate_hz(hz);
}

// Reset the clock counters on a Start event. Only the port that sent Start:
// another port's clock keeps its own phase.
void MidiConnections::reset_divclocks(uint8_t port) {
	if (port >= Midi::NumPorts)
		return;

	for (auto &mp : divclk_pulses) {
		mp.divclk_ctr[port] = 0;
	}
}

void MidiConnections::reset_divclocks() {
	for (auto &mp : divclk_pulses) {
		mp.divclk_ctr.fill(0);
	}
}

void MidiConnections::set_poly_channel_count(uint32_t poly_num) {
	for_each_poly_vector([poly_num](auto &conns) {
		for (auto &jack : conns) {
			if (jack.buf.channels) {
				uint32_t avail = poly_num > jack.poly_base ? poly_num - jack.poly_base : 0;
				*jack.buf.channels = static_cast<uint8_t>(std::min<uint32_t>(avail, CoreProcessor::MaxPolyChannels));
			}
		}
	});
}

void MidiConnections::zero_poly_buffers() {
	for_each_poly_vector([](auto &conns) {
		for (auto &jack : conns) {
			if (jack.buf.voltages) {
				for (unsigned ch = 0; ch < CoreProcessor::MaxPolyChannels; ch++)
					jack.buf.voltages[ch] = 0.f;
				if (jack.buf.channels)
					*jack.buf.channels = 0;
			}
		}
	});
}

void MidiConnections::update_or_add(std::vector<MappedKnob> &v, const MappedKnob &d) {
	for (auto &el : v) {
		if (el.maps_to_same_as(d)) {
			el = d;
			return;
		}
	}
	v.push_back(d);
}

template<typename T>
void MidiConnections::update_or_add(std::vector<T> &v, const Jack &d, uint32_t midi_chan, uint8_t port_mask)
	requires std::derived_from<T, JackMidi>
{
	for (auto &el : v) {
		if (el.module_id == d.module_id && el.jack_id == d.jack_id) {
			el.midi_chan = midi_chan;
			el.port_mask = port_mask;
			return;
		}
	}
	T entry{};
	static_cast<Jack &>(entry) = d;
	entry.midi_chan = midi_chan;
	entry.port_mask = port_mask;
	v.push_back(entry);
}

void MidiConnections::update_or_add_poly(std::vector<PolyJackMidi> &v,
										 const Jack &d,
										 uint32_t midi_chan,
										 uint8_t port_mask,
										 CoreProcessor::PolyPortBuffer buf,
										 uint8_t poly_base) {
	for (auto &el : v) {
		if (el.module_id == d.module_id && el.jack_id == d.jack_id) {
			el.midi_chan = midi_chan;
			el.port_mask = port_mask;
			el.buf = buf;
			el.poly_base = poly_base;
			return;
		}
	}
	PolyJackMidi entry{};
	static_cast<Jack &>(entry) = d;
	entry.midi_chan = midi_chan;
	entry.port_mask = port_mask;
	entry.buf = buf;
	entry.poly_base = poly_base;
	v.push_back(entry);
}

} // namespace MetaModule

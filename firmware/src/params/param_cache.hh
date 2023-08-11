#pragma once
#include "conf/hsem_conf.hh"
#include "drivers/cache.hh"
#include "drivers/hsem.hh"
#include "params.hh"
#include "util/parameter.hh"

// ParamCache class
// Stores a copy of Params and MetaParams and allows thread-safe R/W access.
//
namespace MetaModule
{

struct ParamsState {
	static constexpr float min_change = 1.5f / 4096.f;

	struct LatchedKnob {
		float val{0};
		bool changed{false};

		bool store_changed(float new_val) {
			if (std::abs(new_val - val) > min_change) {
				val = new_val;
				changed = true;
				return true;
			} else
				return false;
		}

		// Allow LatchedKnob to functionally be a float
		void operator=(float x) {
			val = x;
		}
		operator float() {
			return val;
		}
	};
	std::array<LatchedKnob, PanelDef::NumPot> knobs{};

	std::array<Toggler, PanelDef::NumGateIn> gate_ins{};
	float midi_note;
	bool midi_gate;
	uint32_t jack_senses;

	void clear() {
		for (auto &gate_in : gate_ins)
			gate_in.reset();

		for (auto &knob : knobs)
			knob = {0.f, false};

		midi_note = 0.f;
		midi_gate = false;
		jack_senses = 0;
	}

	void move_from(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			gate_in.copy_state(that_gate_in);

		// Copy values, but clear the changed flag after moving it
		for (auto [knob, that_knob] : zip(knobs, that.knobs)) {
			knob.changed = that_knob.changed;
			knob.val = that_knob.val;
			that_knob.changed = false;
		}

		midi_note = that.midi_note;
		midi_gate = that.midi_gate;
		jack_senses = that.jack_senses;
	}

	void copy_to(ParamsState &that) {
		for (auto [gate_in, that_gate_in] : zip(gate_ins, that.gate_ins))
			that_gate_in.copy_state(gate_in);

		that.midi_note = midi_note;
		that.midi_gate = midi_gate;
		that.jack_senses = jack_senses;
	}
};

struct ParamCache {
	ParamsState p;
	MetaParams m;

	static constexpr uint32_t WriteProcID = 1;
	static constexpr uint32_t ReadProcID = 2;

	ParamCache() {
		clear();
	}

	// Writes the ParamCache
	void write_sync(ParamsState &p_, MetaParams &m_) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.move_from(p_);
			m.update_with(m_);
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}

	// Writes the ParamCache
	bool read_sync(ParamsState &params, MetaParams &metaparams) {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(ReadProcID) == HWSemaphoreFlag::LockedOk) {
			p.copy_to(params);
			metaparams.transfer(m);
			HWSemaphore<ParamCacheLock>::unlock(ReadProcID);
			return true;
		}
		return false;
	}

	void clear() {
		using namespace mdrivlib;
		if (HWSemaphore<ParamCacheLock>::lock(WriteProcID) == HWSemaphoreFlag::LockedOk) {
			p.clear();
			m.clear();
			HWSemaphore<ParamCacheLock>::unlock(WriteProcID);
		}
	}
};

struct ParamCacheSync {
	ParamCache &param_cache;
	ParamBlock &param_block;
	ParamsState &param_state;

	ParamCacheSync(ParamCache &param_cache, ParamsState &param_state, ParamBlock &param_block)
		: param_cache{param_cache}
		, param_block{param_block}
		, param_state{param_state} {
	}

	~ParamCacheSync() {
		param_cache.write_sync(param_state, param_block.metaparams);
		mdrivlib::SystemCache::clean_dcache_by_range(&param_cache, sizeof(ParamCache));
	}
};

} // namespace MetaModule

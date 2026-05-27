#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "console/pr_dbg.hh"
#include "patch/patch.hh"
#include "plugin_module.hh"
#include "util/fixed_vector.hh"
#include <span>

namespace MetaModule
{

template<size_t NumCores>
struct CableCache {
	CableCache() = default;

	void clear() {
		for (auto &cable : samecore_cables) {
			cable.clear();
		}
		for (auto &cable : diffcore_cables) {
			cable.clear();
		}
		for (auto &si : summed_inputs) {
			si.clear();
		}
	}

	template<typename SpanT>
	unsigned find_core(uint16_t module_id, std::array<SpanT, NumCores> const &module_cores) {
		for (auto i = 0u; auto &modules : module_cores) {
			if (std::ranges::find(modules, module_id) != modules.end()) {
				return i;
			}
			i++;
		}
		return NumCores;
	}

	template<typename SpanT>
	void build(std::span<const InternalCable> cables, std::array<SpanT, NumCores> const &module_cores, auto &modules) {
		clear();

		for (auto const &cable : cables) {
			for (auto const &in : cable.ins) {
				add(in, cable.out, module_cores);
			}
		}

		build_summed_inputs(cables, module_cores);
		remove_summed_inputs_from_cables();
		resolve_poly_buffers(modules);
	}

	template<typename SpanT>
	void add(Jack in, Jack out, std::array<SpanT, NumCores> const &module_cores) {
		auto out_core_id = find_core(out.module_id, module_cores);
		if (out_core_id == NumCores)
			return;

		auto in_core_id = find_core(in.module_id, module_cores);
		if (in_core_id == NumCores)
			return;

		auto &_cables = (in_core_id == out_core_id) ? samecore_cables : diffcore_cables;

		bool added = false;
		if (auto found = std::ranges::find(_cables[out_core_id], out, &SingleCable::out);
			found != _cables[out_core_id].end())
		{
			added = found->ins.push_back(in);
		}

		if (!added) {
			_cables[out_core_id].push_back({.out = out});
			_cables[out_core_id][_cables[out_core_id].size() - 1].ins.push_back(in);
		}

		pr_trace("Cable[%u]: m%u j%u -> m%u j%u\n", out_core_id, out.module_id, out.jack_id, in.module_id, in.jack_id);
	}

	struct SingleCable {
		Jack out;
		FixedVector<Jack, 4> ins;

		CoreProcessor::PolyPortBuffer out_buf;
		FixedVector<CoreProcessor::PolyPortBuffer, 4> in_bufs;
	};

	// An input jack that receives from multiple output jacks (cables are summed)
	struct SummedInput {
		Jack in;
		FixedVector<Jack, 8> outs;
		FixedVector<CoreProcessor::PolyPortBuffer, 8> out_bufs;
		CoreProcessor::PolyPortBuffer in_buf;
	};

	// organized by out
	std::array<std::vector<SingleCable>, NumCores> diffcore_cables;
	std::array<std::vector<SingleCable>, NumCores> samecore_cables;

	// Inputs that receive from multiple cables, organized by input's core
	std::array<std::vector<SummedInput>, NumCores> summed_inputs;

private:
	// Remove summed input jacks from samecore_cables and diffcore_cables
	// so that process_outputs_samecore/diffcore don't write to them.
	void remove_summed_inputs_from_cables() {
		for (auto &core_si : summed_inputs) {
			for (auto const &si : core_si) {
				remove_input_from_cable_list(si.in, samecore_cables);
				remove_input_from_cable_list(si.in, diffcore_cables);
			}
		}
	}

	void remove_input_from_cable_list(Jack in, std::array<std::vector<SingleCable>, NumCores> &cable_list) {
		for (auto &core_cables : cable_list) {
			for (auto &cable : core_cables) {
				auto &ins = cable.ins;
				for (size_t i = 0; i < ins.size();) {
					if (ins[i] == in) {
						ins[i] = ins[ins.size() - 1];
						ins.pop_back();
					} else {
						i++;
					}
				}
			}
			std::erase_if(core_cables, [](auto const &cable) { return cable.ins.size() == 0; });
		}
	}

	// Detect inputs that are targets of multiple cables and build summed_inputs entries.
	template<typename SpanT>
	void build_summed_inputs(std::span<const InternalCable> cables, std::array<SpanT, NumCores> const &module_cores) {
		for (auto const &cable : cables) {
			for (auto const &in : cable.ins) {
				// Skip if this input already has a summed entry
				bool already_processed = false;
				for (auto const &core_si : summed_inputs) {
					for (auto const &existing : core_si) {
						if (existing.in == in) {
							already_processed = true;
							break;
						}
					}
					if (already_processed)
						break;
				}
				if (already_processed)
					continue;

				// Collect all outputs that feed this input
				SummedInput si;
				si.in = in;
				for (auto const &other_cable : cables) {
					for (auto const &other_in : other_cable.ins) {
						if (other_in == in) {
							si.outs.push_back(other_cable.out);
						}
					}
				}

				if (si.outs.size() > 1) {
					auto in_core = find_core(si.in.module_id, module_cores);
					if (in_core < NumCores) {
						summed_inputs[in_core].push_back(si);
						pr_trace(
							"SummedInput: m%u j%u <- %zu sources\n", si.in.module_id, si.in.jack_id, si.outs.size());
					}
				}
			}
		}
	}

	void resolve_poly_buffers(auto &modules) {
		auto resolve = [&](std::vector<SingleCable> &cable_list) {
			for (auto &cable : cable_list) {
				cable.out_buf = plugin_module_get_poly_output_buffer(modules[cable.out.module_id], cable.out.jack_id);
				// cable.out_buf = modules[cable.out.module_id]->get_output_poly_buffer(cable.out.jack_id);

				// Optimization: If either voltages or channels is invalid,
				// mark both invalid so we only need to check one in the hot loop
				if (!cable.out_buf.voltages || !cable.out_buf.channels) {
					cable.out_buf.voltages = nullptr;
					cable.out_buf.channels = nullptr;
				}

				pr_trace("%s out m%u j%u -> ",
						 cable.out_buf.voltages ? "Poly" : "Mono",
						 cable.out.module_id,
						 cable.out.jack_id);

				cable.in_bufs.clear();
				for (auto const &in : cable.ins) {
					// auto buf = modules[in.module_id]->get_input_poly_buffer(in.jack_id);
					auto buf = plugin_module_get_poly_input_buffer(modules[in.module_id], in.jack_id);
					if (!buf.voltages || !buf.channels) {
						buf.voltages = nullptr;
						buf.channels = nullptr;
					}
					cable.in_bufs.push_back(buf);
					pr_trace("%s in m%u j%u; ", buf.voltages ? "Poly" : "Mono", in.module_id, in.jack_id);
				}
				pr_trace("\n");
			}
		};

		for (auto &core_cables : samecore_cables)
			resolve(core_cables);

		for (auto &core_cables : diffcore_cables)
			resolve(core_cables);

		for (auto &core_si : summed_inputs) {
			for (auto &si : core_si) {
				si.out_bufs.clear();
				for (auto const &out : si.outs) {
					auto buf = plugin_module_get_poly_output_buffer(modules[out.module_id], out.jack_id);
					if (!buf.voltages || !buf.channels) {
						buf.voltages = nullptr;
						buf.channels = nullptr;
					}
					si.out_bufs.push_back(buf);
				}
				si.in_buf = plugin_module_get_poly_input_buffer(modules[si.in.module_id], si.in.jack_id);
				if (!si.in_buf.voltages || !si.in_buf.channels) {
					si.in_buf.voltages = nullptr;
					si.in_buf.channels = nullptr;
				}
			}
		}
	}
};
} // namespace MetaModule

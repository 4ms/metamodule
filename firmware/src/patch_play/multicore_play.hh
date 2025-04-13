#pragma once
#include "core_a7/smp_api.hh"
#include "drivers/smp.hh"
#include <span>

namespace MetaModule
{

class MulticorePlayer {
public:
	static constexpr unsigned NumCores = mdrivlib::SMPControl::NumCores;

	void assign_modules(std::span<unsigned> module_ids) {
		if constexpr (NumCores > 1) {
			mdrivlib::SMPThread::init();
			mdrivlib::SMPControl::write(SMPRegister::NumModulesInPatch, module_ids.size());

			for (auto i = 2u; auto module_id : module_ids) { // regs 2 and up are the module ids
				mdrivlib::SMPControl::write(i++, module_id);
			}
			mdrivlib::SMPControl::notify<SMPCommand::NewModuleList>();
		}
	}

	void update_modules() {
		if constexpr (NumCores > 1) {
			mdrivlib::SMPThread::split_with_command<SMPCommand::PlayModuleList>();
		}
	}

	void read_patch_gui_elements() {
		if constexpr (NumCores > 1) {
			mdrivlib::SMPThread::split_with_command<SMPCommand::ReadPatchGuiElements>();
		}
	}

	void join() {
		if constexpr (NumCores > 1) {
			mdrivlib::SMPThread::join();
		}
	}
};

} // namespace MetaModule

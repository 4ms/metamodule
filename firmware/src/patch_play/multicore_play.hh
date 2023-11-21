#pragma once
#include "core_a7/smp_api.hh"
#include "drivers/smp.hh"

namespace MetaModule
{

class MulticorePlayer {
public:
	static constexpr unsigned ModuleStride = mdrivlib::SMPControl::NumCores;

	void load_patch(unsigned num_modules) {

		num_modules_ = num_modules;
		//Module 0 is the hub
		//Module 1 is processed by first core
		//Module 2 is processed by second core
		//Module 3 is processed by first core
		//Module 4 is processed by second core
		//... etc
		if constexpr (mdrivlib::SMPControl::NumCores > 1) {
			mdrivlib::SMPThread::init();
			mdrivlib::SMPControl::write<SMPRegister::ModuleID>(2); //first module to process
			mdrivlib::SMPControl::write<SMPRegister::NumModulesInPatch>(num_modules);
			mdrivlib::SMPControl::write<SMPRegister::UpdateModuleOffset>(ModuleStride);
			mdrivlib::SMPControl::notify<SMPCommand::NewModuleList>();
		}
	}

	void update_modules() {
		if constexpr (mdrivlib::SMPControl::NumCores > 1) {
			mdrivlib::SMPThread::split_with_command<SMPCommand::PlayModuleList>();
		}
	}

	void read_patch_state() {
		if constexpr (mdrivlib::SMPControl::NumCores > 1) {
			mdrivlib::SMPThread::split_with_command<SMPCommand::ReadPatchLights>();
		}
	}

	void join() {
		if constexpr (mdrivlib::SMPControl::NumCores > 1) {
			mdrivlib::SMPThread::join();
		}
	}

private:
	unsigned num_modules_ = 0;
};

} // namespace MetaModule

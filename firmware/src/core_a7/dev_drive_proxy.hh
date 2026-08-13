#pragma once
#include "core_intercom/shared_memory.hh"
#include "fs/dev_drive.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// Access to the developer-mode USB drive
struct DevDriveProxy {

	static void register_drive(DevDrive *drive) {
		_drive = drive;
	}

	// Claim the drive's memory, put a filesystem on it, and publish it to the M4.
	static DevDriveStatus enable() {
		if (!_drive) {
			pr_err("DevDrive: unexpected error: no drive registered\n");
			return DevDriveStatus::NotAvailable;
		}

		if (auto status = _drive->enable(); status != DevDriveStatus::Ok)
			return status;

		_drive->hand_to_host();

		if (auto *block = SharedMemoryS::ptrs.dev_drive) {
			auto mem = _drive->memory();
			block->publish(reinterpret_cast<uint32_t>(mem.data()), mem.size());
		}

		return DevDriveStatus::Ok;
	}

	static void disable() {
		// Withdraw before freeing: the M4 must stop serving sectors out of this
		if (auto *block = SharedMemoryS::ptrs.dev_drive)
			block->withdraw();

		if (_drive)
			_drive->disable();
	}

	static bool is_enabled() {
		return _drive && _drive->is_enabled();
	}

private:
	static inline DevDrive *_drive = nullptr;
};

} // namespace MetaModule

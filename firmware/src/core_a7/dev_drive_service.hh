#pragma once
#include "core_intercom/shared_memory.hh"
#include "fs/dev_drive.hh"
#include "gui/notify/queue.hh"
#include "pr_dbg.hh"
#include <string>
#include <vector>

namespace MetaModule
{

// Aux core monitor for ejecct events on the developer drive.
// Checks for .mmplugin files and installs them (TODO).
class DevDriveService {
public:
	DevDriveService(DevDrive &drive, NotificationQueue &notify_queue)
		: drive_{drive}
		, notify_queue_{notify_queue} {
	}

	void process() {
		auto *block = SharedMemoryS::ptrs.dev_drive;
		if (!block || !drive_.is_enabled())
			return;

		// The M4 bumps this from the OTG interrupt on each host eject
		auto count = block->eject_count.load(std::memory_order_acquire);
		if (count == last_eject_count_)
			return;

		last_eject_count_ = count;
		handle_eject(*block);
	}

private:
	void handle_eject(DevDriveBlock &block) {
		pr_info("DevDrive: host ejected, scanning\n");

		drive_.take_from_host();

		// The host rewrote the filesystem, so the mount we did at format time
		// describes a drive that no longer exists
		if (!drive_.files().mount_disk()) {
			pr_err("DevDrive: could not mount after eject\n");
			notify_queue_.put(
				{"Developer drive is unreadable.\nIt will be reformatted.", Notification::Priority::Error, 3000});
			reformat(block);
			return;
		}

		auto plugins = find_plugins();

		if (plugins.empty()) {
			// Nothing to do -- likely an eject without copying anything, or the
			// files went into a subdirectory
			pr_info("DevDrive: no .mmplugin files in the root directory\n");
		} else {
			for (auto const &name : plugins)
				pr_info("DevDrive: found %s\n", name.c_str());

			// TODO: install each plugin here, then move it aside so a remount
			// does not offer to install it again
			notify_queue_.put({"Found " + std::to_string(plugins.size()) + " plugin file(s) on the developer drive",
							   Notification::Priority::Status,
							   3000});
		}

		put_medium_back(block);
	}

	std::vector<std::string> find_plugins() {
		std::vector<std::string> found;

		drive_.files().foreach_file_with_ext(".mmplugin", [&found](std::string_view name, uint32_t, uint32_t size) {
			if (name.starts_with("."))
				return;
			if (size == 0)
				return;

			found.emplace_back(name);
		});

		return found;
	}

	void put_medium_back(DevDriveBlock &block) {
		drive_.hand_to_host();
		block.present.store(1, std::memory_order_release);
		pr_info("DevDrive: medium restored\n");
	}

	void reformat(DevDriveBlock &block) {
		drive_.disable();
		if (drive_.enable() == DevDriveStatus::Ok) {
			drive_.hand_to_host();
			auto mem = drive_.memory();
			block.publish(reinterpret_cast<uint32_t>(mem.data()), mem.size());
		}
	}

	DevDrive &drive_;
	NotificationQueue &notify_queue_;
	uint32_t last_eject_count_ = 0;
};

} // namespace MetaModule

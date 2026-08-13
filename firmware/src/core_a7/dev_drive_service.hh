#pragma once
#include "core_intercom/shared_memory.hh"
#include "dynload/plugin_manager.hh"
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
	DevDriveService(DevDrive &drive, PluginManager &plugin_manager, NotificationQueue &notify_queue)
		: drive_{drive}
		, plugin_manager_{plugin_manager}
		, notify_queue_{notify_queue} {
	}

	void process() {
		// An install already under way owns the drive until it finishes
		if (installing_) {
			process_install();
			return;
		}

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
			put_medium_back(block);
			return;
		}

		for (auto const &name : plugins)
			pr_info("DevDrive: found %s\n", name.c_str());

		// The medium stays away until every install has finished: the loader
		// reads the drive as it works, and a host remounting mid-install would
		// be writing underneath it.
		queue_ = std::move(plugins);
		installing_ = true;
		start_next_install();
	}

	// One install at a time, one step per main-loop pass, so the GUI keeps
	// running while a plugin is unpacked and linked.
	void process_install() {
		auto status = plugin_manager_.process_loading();

		if (!plugin_manager_.is_idle())
			return;

		using enum PluginFileLoaderState;

		if (status.state == Success) {
			pr_info("DevDrive: installed %s\n", current_.c_str());

			// Remove it so the next eject does not install it again. The
			// developer sees an empty drive, which is the confirmation.
			drive_.files().delete_file(current_);

			notify_queue_.put({"Installed " + current_, Notification::Priority::Status, 3000});

		} else {
			auto why = status.error_message.empty() ?
						   ("loader stopped in state " + std::to_string((int)status.state)) :
						   status.error_message;
			pr_err("DevDrive: could not install %s: %s\n", current_.c_str(), why.c_str());
			notify_queue_.put({"Could not install " + current_ + "\n" + why, Notification::Priority::Error, 4000});
		}

		start_next_install();
	}

	void start_next_install() {
		if (queue_.empty()) {
			installing_ = false;
			current_.clear();

			if (auto *block = SharedMemoryS::ptrs.dev_drive)
				put_medium_back(*block);
			return;
		}

		current_ = queue_.front();
		queue_.erase(queue_.begin());

		pr_info("DevDrive: installing %s\n", current_.c_str());

		if (!plugin_manager_.install_local_plugin(drive_.files(), current_)) {
			pr_err("DevDrive: could not start installing %s\n", current_.c_str());
			notify_queue_.put({"Could not install " + current_, Notification::Priority::Error, 3000});
			start_next_install();
		}
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
	PluginManager &plugin_manager_;
	NotificationQueue &notify_queue_;
	uint32_t last_eject_count_ = 0;

	std::vector<std::string> queue_;
	std::string current_;
	bool installing_ = false;
};

} // namespace MetaModule

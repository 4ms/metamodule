#pragma once
#include "core_intercom/shared_memory.hh"
#include "dynload/plugin_manager.hh"
#include "fs/dev_drive.hh"
#include "gui/notify/queue.hh"
#include "patch_play/patch_playloader.hh"
#include "pr_dbg.hh"
#include <string>
#include <vector>

namespace MetaModule
{

// Aux core monitor for ejecct events on the developer drive.
// Checks for .mmplugin files and installs them
class DevDriveService {
public:
	DevDriveService(DevDrive &drive,
					PluginManager &plugin_manager,
					PatchPlayLoader &play_loader,
					NotificationQueue &notify_queue)
		: drive_{drive}
		, plugin_manager_{plugin_manager}
		, play_loader_{play_loader}
		, notify_queue_{notify_queue} {
	}

	uint32_t retries = 10;

	void process(bool should_enable) {
		// An install already under way owns the drive until it finishes
		if (installing_) {
			process_install();
			return;
		}

		if (!should_enable) {
			retries = 10;
			drive_.disable();
			return;
		}

		if (should_enable && !drive_.is_enabled() && retries) {
			if (reformat() != DevDriveStatus::Ok)
				retries--;
		}

		auto *block = SharedMemoryS::ptrs.dev_drive_msgs;
		if (!block || !drive_.is_enabled())
			return;

		// The M4 bumps this each host eject
		auto count = block->eject_count.load(std::memory_order_acquire);
		if (count != last_eject_count_) {
			last_eject_count_ = count;
			pr_info("DevDrive: host ejected\n");
			host_ejected_ = true;
			scan_and_install(*block);
			return;
		}

		// M4 bumps this once per console command
		auto cmd_count = block->command_count.load(std::memory_order_acquire);
		if (cmd_count != last_command_count_) {
			last_command_count_ = cmd_count;
			handle_command(*block, (DevDriveCommand)block->command.load(std::memory_order_relaxed));
		}
	}

private:
	void handle_command(DevDriveBlock &block, DevDriveCommand cmd) {
		switch (cmd) {
			case DevDriveCommand::Install:
				host_ejected_ = false;
				block.present.store(0, std::memory_order_release);
				printf("Installing from the developer drive\n");
				scan_and_install(block);
				break;

			case DevDriveCommand::Eject:
				block.present.store(0, std::memory_order_release);
				printf("Developer drive removed\n");
				break;

			case DevDriveCommand::Mount:
				put_medium_back(block);
				printf("Developer drive restored\n");
				break;

			case DevDriveCommand::Status:
				report_status(block);
				break;

			case DevDriveCommand::None:
				break;
		}
	}

	void report_status(DevDriveBlock &block) {
		printf("Developer drive: %s, medium %s\n",
			   drive_.is_enabled() ? "enabled" : "disabled",
			   block.is_present() ? "present" : "removed");

		if (!drive_.is_enabled())
			return;

		drive_.files().foreach_file_with_ext(".mmplugin", [](std::string_view name, uint32_t, uint32_t size) {
			printf("  %.*s (%u bytes)\n", (int)name.size(), name.data(), (unsigned)size);
		});
	}

	void scan_and_install(DevDriveBlock &block) {
		drive_.take_from_host();

		if (!drive_.files().mount_disk()) {
			pr_err("DevDrive: could not mount after eject\n");
			notify_queue_.put(
				{"Developer drive is unreadable and will be reformatted", Notification::Priority::Error, 3000});
			reformat();
			return;
		}

		auto plugins = find_plugins();

		if (plugins.empty()) {
			pr_info("DevDrive: no .mmplugin files in the root directory\n");
			put_medium_back(block);
			return;
		}

		for (auto const &name : plugins)
			pr_info("DevDrive: found plugin %s\n", name.c_str());

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

			// Remove it so the next eject does not install it again
			drive_.files().delete_file(current_);

			notify_queue_.put({"Installed " + current_, Notification::Priority::Status, 3000});

		} else {
			auto why = status.error_message.empty() ? ("loader stopped in state " + std::to_string((int)status.state)) :
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

			if (auto *block = SharedMemoryS::ptrs.dev_drive_msgs)
				put_medium_back(*block);
			return;
		}

		current_ = queue_.front();
		queue_.erase(queue_.begin());

		pr_info("DevDrive: installing %s\n", current_.c_str());

		auto name = PluginManager::plugin_name_of(current_);
		if (plugin_manager_.is_plugin_loaded(name)) {
			pr_info("DevDrive: unloading %.*s first\n", (int)name.size(), name.data());
			play_loader_.prepare_patch_for_plugin_change(name);
			plugin_manager_.unload_plugin(name);
		}

		if (!plugin_manager_.start_local_install(drive_.files(), current_)) {
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

		if (host_ejected_) {
			// A host that ejected the drive has stopped talking to it.
			// The device has to leave the bus and come back by re-enumerating
			// to get the computer to see it again.
			host_ejected_ = false;
			pr_info("DevDrive: medium restored, re-enumerating so the host sees it\n");
			block.request_reenumerate();
		} else {
			pr_info("DevDrive: medium restored\n");
		}
	}

public:
	DevDriveStatus reformat() {
		auto *block = SharedMemoryS::ptrs.dev_drive_msgs;

		drive_.disable();
		auto status = drive_.enable();
		if (status == DevDriveStatus::Ok) {
			drive_.hand_to_host();
			auto mem = drive_.memory();
			block->publish(reinterpret_cast<uint32_t>(mem.data()), mem.size());
		}
		return status;
	}

private:
	DevDrive &drive_;
	PluginManager &plugin_manager_;
	PatchPlayLoader &play_loader_;
	NotificationQueue &notify_queue_;
	uint32_t last_eject_count_ = 0;
	uint32_t last_command_count_ = 0;
	bool host_ejected_ = false;

	std::vector<std::string> queue_;
	std::string current_;
	bool installing_ = false;
};

} // namespace MetaModule

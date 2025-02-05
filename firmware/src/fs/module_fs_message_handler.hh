#pragma once
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "util/overloaded.hh"
#include <optional>

namespace MetaModule
{

struct ModuleFSMessageHandler {

	ModuleFSMessageHandler(IntercoreModuleFS::Message *shared_message_core0,
						   IntercoreModuleFS::Message *shared_message_core1)
		: intercore_comm_core0{*shared_message_core0}
		, intercore_comm_core1{*shared_message_core1} {
	}

	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreModuleFS::Message, 2> intercore_comm_core0;
	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreModuleFS::Message, 3> intercore_comm_core1;

	void process() {
		auto process_core = [this](auto &comm) {
			auto message = comm.get_new_message();

			if (auto response = handle_fatfs_message(message)) {
				while (!comm.send_message(*response))
					;
			}
		};

		process_core(intercore_comm_core0);
		process_core(intercore_comm_core1);
	}

	std::optional<IntercoreModuleFS::Message> handle_fatfs_message(IntercoreModuleFS::Message &message) {
		bool handled = std::visit(
			overloaded{
				[](auto &msg) { return false; },

				// READING:

				[](IntercoreModuleFS::Open &msg) {
					msg.res = f_open(&msg.fil, msg.path.c_str(), msg.access_mode);
					pr_trace(
						"M4: f_open(%p, %.255s, %d) -> %d\n", &msg.fil, msg.path.c_str(), msg.access_mode, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Close &msg) {
					msg.res = f_close(&msg.fil);
					pr_trace("M4: f_close(%p) -> %d\n", &msg.fil, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Seek &msg) {
					auto pos = msg.file_offset;
					if (msg.whence == IntercoreModuleFS::Seek::Whence::CurrentPos) {
						pos += f_tell(&msg.fil);
					} else if (msg.whence == IntercoreModuleFS::Seek::Whence::End) {
						pos += f_size(&msg.fil);
					}
					msg.res = f_lseek(&msg.fil, pos);
					pr_trace("M4: f_lseek(%p, %llu) -> %d\n", &msg.fil, pos, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Read &msg) {
					UINT bytes_read = 0;
					msg.res = f_read(&msg.fil, msg.buffer.data(), msg.buffer.size(), &bytes_read);
					msg.bytes_read = bytes_read;
					pr_trace("M4: f_read(%p, %p, %zu, -> %u) -> %d\n",
							 &msg.fil,
							 msg.buffer.data(),
							 msg.buffer.size(),
							 bytes_read,
							 msg.res);
					return true;
				},

				[](IntercoreModuleFS::GetS &msg) {
					msg.res = f_gets(msg.buffer.data(), (int)msg.buffer.size(), &msg.fil);
					pr_trace("M4: f_gets(%p, %u, %p)-> %p\n", msg.buffer.data(), msg.buffer.size(), &msg.fil, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Stat &msg) {
					msg.res = f_stat(msg.path, &msg.info);
					pr_trace("M4: f_stat(%.255s, ->{sz=%llu}) -> %d\n", msg.path.c_str(), msg.info.fsize, msg.res);
					return true;
				},

				// DIRS

				[](IntercoreModuleFS::OpenDir &msg) {
					msg.res = f_opendir(&msg.dir, msg.path);
					pr_trace("M4: f_opendir(%p, %.255s) -> %d\n", &msg.dir, msg.path.c_str(), msg.res);
					return true;
				},

				[](IntercoreModuleFS::CloseDir &msg) {
					msg.res = f_closedir(&msg.dir);
					pr_trace("M4: f_closedir(%p) -> %d\n", &msg.dir, msg.res);
					return true;
				},

				[](IntercoreModuleFS::ReadDir &msg) {
					msg.res = f_readdir(&msg.dir, &msg.info);
					pr_trace("M4: f_readdir(%p, ->{name=%.255s}) -> %d\n", &msg.dir, msg.info.fname, msg.res);
					return true;
				},

				[](IntercoreModuleFS::FindFirst &msg) {
					msg.res = f_findfirst(&msg.dir, &msg.info, msg.path.data(), msg.pattern.data());

					pr_trace("M4: f_findfirst(%p, ->{name=%.255s}, %.255s, %.255s) -> %d\n",
							 &msg.dir,
							 msg.info.fname,
							 msg.path.data(),
							 msg.pattern.data(),
							 msg.res);
					return true;
				},

				[](IntercoreModuleFS::FindNext &msg) {
					msg.res = f_findnext(&msg.dir, &msg.info);
					pr_trace("M4: f_findnext(%p, ->{name=%.255s}) -> %d\n", &msg.dir, msg.info.fname, msg.res);
					return true;
				},

				[](IntercoreModuleFS::MkDir &msg) {
					msg.res = f_mkdir(msg.path);
					pr_trace("M4: f_mkdir(%.255s) -> %d\n", msg.path.c_str(), msg.res);
					return true;
				},

				[](IntercoreModuleFS::Write &msg) {
					UINT bytes_written = 0;
					msg.res = f_write(&msg.fil, msg.buffer.data(), msg.buffer.size(), &bytes_written);
					msg.bytes_written = bytes_written;
					pr_trace("M4: f_write(%p, %p, %zu, -> %u) -> %d\n",
							 &msg.fil,
							 msg.buffer.data(),
							 msg.buffer.size(),
							 bytes_written,
							 msg.res);
					return true;
				},

				[](IntercoreModuleFS::Sync &msg) {
					msg.res = f_sync(&msg.fil);
					pr_trace("M4: f_sync(%p) -> %d\n", &msg.fil, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Trunc &msg) {
					msg.res = f_truncate(&msg.fil);
					pr_trace("M4: f_truncate(%p) -> %d\n", &msg.fil, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Puts &msg) {
					msg.bytes_written = f_puts(msg.buffer.data(), &msg.fil);
					pr_trace("M4: f_puts(%p) -> %d\n", &msg.fil, msg.bytes_written);
					return true;
				},

				[](IntercoreModuleFS::Unlink &msg) {
					msg.res = f_unlink(msg.path.data());
					pr_trace("M4: f_unlink(%p) -> %d\n", msg.path.data(), msg.res);
					return true;
				},

				[](IntercoreModuleFS::Rename &msg) {
					msg.res = f_rename(msg.old_path.data(), msg.new_path.data());
					pr_trace("M4: f_rename(%s, %s) -> %d\n", msg.old_path.data(), msg.new_path.data(), msg.res);
					return true;
				},

				[](IntercoreModuleFS::Utime &msg) {
					msg.res = f_utime(msg.path.data(), &msg.info);
					pr_trace(
						"M4: f_utime(%s, %p [tm:%x]) -> %d\n", msg.path.data(), &msg.info, msg.info.ftime, msg.res);
					return true;
				},

			},
			message);

		if (handled) {
			return message;
		} else
			return std::nullopt;
	}
};

} // namespace MetaModule

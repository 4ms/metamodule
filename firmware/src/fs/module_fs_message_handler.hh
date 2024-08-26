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
					pr_trace("M4: f_open(%p, %s, %d) -> %d\n", &msg.fil, msg.path.c_str(), msg.access_mode, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Close &msg) {
					msg.res = f_close(&msg.fil);
					pr_trace("M4: f_close(%p) -> %d\n", msg.fil, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Seek &msg) {
					msg.res = f_lseek(&msg.fil, msg.file_offset);
					pr_trace("M4: f_lseek(%p, %llu) -> %d\n", &msg.fil, msg.file_offset, msg.res);
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
					pr_trace("M4: f_stat(%s, ->{sz=%llu}) -> %d\n", msg.path, msg.info.fsize, msg.res);
					return true;
				},

				// DIRS

				[](IntercoreModuleFS::OpenDir &msg) {
					msg.res = f_opendir(&msg.dir, msg.path);
					pr_trace("M4: f_opendir(%p, %s) -> %d\n", &msg.dir, msg.path, msg.res);
					return true;
				},

				[](IntercoreModuleFS::CloseDir &msg) {
					msg.res = f_closedir(&msg.dir);
					pr_trace("M4: f_closedir(%p) -> %d\n", &msg.dir, msg.res);
					return true;
				},

				[](IntercoreModuleFS::ReadDir &msg) {
					msg.res = f_readdir(&msg.dir, &msg.info);
					pr_trace("M4: f_readdir(%p, ->{name=%s}) -> %d\n", &msg.dir, msg.info.fname, msg.res);
					return true;
				},

				[](IntercoreModuleFS::FindFirst &msg) {
					msg.res = f_findfirst(&msg.dir, &msg.info, msg.path.data(), msg.pattern.data());
					pr_trace("M4: f_findfirst(%p, ->{name=%s}, %s, %s) -> %d\n",
							 &msg.dir,
							 msg.info.fname,
							 msg.path.data(),
							 msg.pattern.data(),
							 msg.res);
					return true;
				},

				[](IntercoreModuleFS::FindNext &msg) {
					msg.res = f_findnext(&msg.dir, &msg.info);
					pr_trace("M4: f_findnext(%p, ->{name=%s}, %s, %s) -> %d\n", &msg.dir, msg.info.fname, msg.res);
					return true;
				},

				[](IntercoreModuleFS::MkDir &msg) {
					msg.res = f_mkdir(msg.path);
					pr_trace("M4: f_mkdir(%s) -> %d\n", msg.path, msg.res);
					return true;
				},

				//TODO:
				//Write
				//Sync
				//Trunc
				//Puts
				//Unlink
				//Rename
				//UTime
				//Expand

			},
			message);

		if (handled) {
			return message;
		} else
			return std::nullopt;
	}
};

} // namespace MetaModule

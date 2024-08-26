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

				[](IntercoreModuleFS::Open &msg) {
					msg.res = f_open(&msg.fil, msg.path.c_str(), msg.access_mode);
					pr_dbg("M4: f_open(%p, %s, %d) -> %d\n", &msg.fil, msg.path.c_str(), msg.access_mode, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Seek &msg) {
					msg.res = f_lseek(&msg.fil, msg.file_offset);
					pr_dbg("M4: f_lseek(%p, %llu) -> %d\n", &msg.fil, msg.file_offset, msg.res);
					return true;
				},

				[](IntercoreModuleFS::Read &msg) {
					UINT bytes_read = 0;
					msg.res = f_read(&msg.fil, msg.buffer.data(), msg.buffer.size(), &bytes_read);
					msg.bytes_read = bytes_read;
					pr_dbg("M4: f_read(%p, %p, %zu, -> %u) -> %d\n",
						   &msg.fil,
						   msg.buffer.data(),
						   msg.buffer.size(),
						   bytes_read,
						   msg.res);
					return true;
				},

				[](IntercoreModuleFS::GetS &msg) {
					auto txt = f_gets(msg.buffer.data(), (int)msg.buffer.size(), &msg.fil);

					msg.res = txt == nullptr ? FR_INT_ERR : FR_OK;

					pr_dbg("M4: f_gets(%p, %zu, %p) -> %p\n", msg.buffer.data(), msg.buffer.size(), &msg.fil, txt);
					return true;
				},

				[](IntercoreModuleFS::Close &msg) {
					msg.res = f_close(&msg.fil);
					pr_dbg("M4: f_close(%p) -> %d\n", msg.fil, msg.res);
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

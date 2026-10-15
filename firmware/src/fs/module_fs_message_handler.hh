#pragma once
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fs_object_table.hh"
#include "util/overloaded.hh"
#include <optional>

namespace MetaModule
{

struct ModuleFSMessageHandler {

	ModuleFSMessageHandler(IntercoreModuleFS::IccMessage *shared_message_core0,
						   IntercoreModuleFS::IccMessage *shared_message_core1)
		: intercore_comm_core0{*shared_message_core0}
		, intercore_comm_core1{*shared_message_core1} {
	}

	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreModuleFS::IccMessage, 2> intercore_comm_core0;
	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreModuleFS::IccMessage, 3> intercore_comm_core1;

	// This core owns all FatFs objects; clients refer to them by FsHandle.
	// Both A7/A35 cores' requests share these tables.
	static constexpr size_t MaxOpenFiles = 16;
	static constexpr size_t MaxOpenDirs = 8;
	FsObjectTable<FIL, MaxOpenFiles> open_files;
	FsObjectTable<DIR, MaxOpenDirs> open_dirs;

	void process() {
		auto process_core = [this](auto &comm) {
			// Shared representation -> std::variant for the business logic, and back
			IntercoreModuleFS::Message message = comm.get_new_message().to_variant();

			if (auto response = handle_fatfs_message(message)) {
				while (!comm.send_message(IntercoreModuleFS::IccMessage{*response}))
					;
			}
		};

		process_core(intercore_comm_core0);
		process_core(intercore_comm_core1);
	}

	static IntercoreModuleFS::FsFileState file_state(FIL &fil) {
		return {
			.fptr = f_tell(&fil),
			.objsize = f_size(&fil),
			.err = fil.err,
		};
	}

	std::optional<IntercoreModuleFS::Message> handle_fatfs_message(IntercoreModuleFS::Message &message) {
		auto &files = open_files;
		auto &dirs = open_dirs;

		// Look up a message's file/dir handle, marking the message failed if invalid
		auto get_file = [&files](auto &msg) -> FIL * {
			if (auto *fil = files.get(msg.fil))
				return fil;
			msg.res = FR_INVALID_OBJECT;
			return nullptr;
		};
		auto get_dir = [&dirs](auto &msg) -> DIR * {
			if (auto *dir = dirs.get(msg.dir))
				return dir;
			msg.res = FR_INVALID_OBJECT;
			return nullptr;
		};

		bool handled = std::visit(
			overloaded{
				[](auto &msg) { return false; },

				// READING:

				[&](IntercoreModuleFS::Open &msg) {
					auto handle = IntercoreModuleFS::InvalidFsHandle;
					if (auto *fil = files.alloc(handle)) {
						msg.res = f_open(fil, msg.path.c_str(), msg.access_mode);
						if (msg.res == FR_OK) {
							msg.fil = handle;
							msg.state = file_state(*fil);
						} else {
							files.free(handle);
							msg.fil = IntercoreModuleFS::InvalidFsHandle;
						}
					} else {
						msg.res = FR_TOO_MANY_OPEN_FILES;
						msg.fil = IntercoreModuleFS::InvalidFsHandle;
					}
					pr_trace("M4: f_open(#%x, %.255s, %d) -> %d\n", msg.fil, msg.path.c_str(), msg.access_mode, msg.res);
					return true;
				},

				[&](IntercoreModuleFS::Close &msg) {
					if (auto *fil = get_file(msg)) {
						msg.res = f_close(fil);
						files.free(msg.fil);
					}
					pr_trace("M4: f_close(#%x) -> %d\n", msg.fil, msg.res);
					return true;
				},

				[&](IntercoreModuleFS::Seek &msg) {
					if (auto *fil = get_file(msg)) {
						auto pos = msg.file_offset;
						if (msg.whence == IntercoreModuleFS::Seek::Whence::CurrentPos) {
							pos += f_tell(fil);
						} else if (msg.whence == IntercoreModuleFS::Seek::Whence::End) {
							pos += f_size(fil);
						}
						msg.res = f_lseek(fil, pos);
						msg.state = file_state(*fil);
						pr_trace("M4: f_lseek(#%x, %llu) -> %d\n", msg.fil, pos, msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::Read &msg) {
					if (auto *fil = get_file(msg)) {
						UINT bytes_read = 0;
						msg.res = f_read(fil, msg.buffer.data(), msg.buffer.size(), &bytes_read);
						msg.bytes_read = bytes_read;
						msg.state = file_state(*fil);
						pr_trace("M4: f_read(#%x, %p, %zu, -> %u) -> %d\n",
								 msg.fil,
								 msg.buffer.data(),
								 msg.buffer.size(),
								 bytes_read,
								 msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::GetS &msg) {
					if (auto *fil = files.get(msg.fil)) {
						auto res = f_gets(msg.buffer.data(), (int)msg.buffer.size(), fil);
						msg.res_ok = (res != nullptr) ? 1 : 0;
						msg.bytes_read = msg.res_ok ? strlen(msg.buffer.data()) : 0;
						msg.state = file_state(*fil);
						pr_trace("M4: f_gets(%p, %u, #%x)-> %d\n", msg.buffer.data(), msg.buffer.size(), msg.fil, msg.res_ok);
					} else {
						msg.res_ok = 0;
					}
					return true;
				},

				[](IntercoreModuleFS::Stat &msg) {
					msg.res = f_stat(msg.path, &msg.info);
					pr_trace("M4: f_stat(%.255s, ->{sz=%llu}) -> %d\n", msg.path.c_str(), msg.info.fsize, msg.res);
					return true;
				},

				// DIRS

				[&](IntercoreModuleFS::OpenDir &msg) {
					auto handle = IntercoreModuleFS::InvalidFsHandle;
					if (auto *dir = dirs.alloc(handle)) {
						msg.res = f_opendir(dir, msg.path);
						if (msg.res == FR_OK) {
							msg.dir = handle;
						} else {
							dirs.free(handle);
							msg.dir = IntercoreModuleFS::InvalidFsHandle;
						}
					} else {
						msg.res = FR_TOO_MANY_OPEN_FILES;
						msg.dir = IntercoreModuleFS::InvalidFsHandle;
					}
					pr_trace("M4: f_opendir(#%x, %.255s) -> %d\n", msg.dir, msg.path.c_str(), msg.res);
					return true;
				},

				[&](IntercoreModuleFS::CloseDir &msg) {
					if (auto *dir = get_dir(msg)) {
						msg.res = f_closedir(dir);
						dirs.free(msg.dir);
					}
					pr_trace("M4: f_closedir(#%x) -> %d\n", msg.dir, msg.res);
					return true;
				},

				[&](IntercoreModuleFS::ReadDir &msg) {
					if (auto *dir = get_dir(msg)) {
						msg.res = f_readdir(dir, &msg.info);
						pr_trace("M4: f_readdir(#%x, ->{name=%.255s}) -> %d\n", msg.dir, msg.info.fname, msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::FindFirst &msg) {
					auto handle = IntercoreModuleFS::InvalidFsHandle;
					if (auto *dir = dirs.alloc(handle)) {
						msg.res = f_findfirst(dir, &msg.info, msg.path.data(), msg.pattern.data());
						if (msg.res == FR_OK) {
							msg.dir = handle;
						} else {
							dirs.free(handle);
							msg.dir = IntercoreModuleFS::InvalidFsHandle;
						}
					} else {
						msg.res = FR_TOO_MANY_OPEN_FILES;
						msg.dir = IntercoreModuleFS::InvalidFsHandle;
					}

					pr_trace("M4: f_findfirst(#%x, ->{name=%.255s}, %.255s, %.255s) -> %d\n",
							 msg.dir,
							 msg.info.fname,
							 msg.path.data(),
							 msg.pattern.data(),
							 msg.res);
					return true;
				},

				[&](IntercoreModuleFS::FindNext &msg) {
					if (auto *dir = get_dir(msg)) {
						msg.res = f_findnext(dir, &msg.info);
						pr_trace("M4: f_findnext(#%x, ->{name=%.255s}) -> %d\n", msg.dir, msg.info.fname, msg.res);
					}
					return true;
				},

				[](IntercoreModuleFS::MkDir &msg) {
					msg.res = f_mkdir(msg.path);
					pr_trace("M4: f_mkdir(%.255s) -> %d\n", msg.path.c_str(), msg.res);
					return true;
				},

				[&](IntercoreModuleFS::Write &msg) {
					if (auto *fil = get_file(msg)) {
						UINT bytes_written = 0;
						msg.res = f_write(fil, msg.buffer.data(), msg.buffer.size(), &bytes_written);
						msg.bytes_written = bytes_written;
						msg.state = file_state(*fil);
						pr_trace("M4: f_write(#%x, %p, %zu, -> %u) -> %d\n",
								 msg.fil,
								 msg.buffer.data(),
								 msg.buffer.size(),
								 bytes_written,
								 msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::Sync &msg) {
					if (auto *fil = get_file(msg)) {
						msg.res = f_sync(fil);
						msg.state = file_state(*fil);
						pr_trace("M4: f_sync(#%x) -> %d\n", msg.fil, msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::Trunc &msg) {
					if (auto *fil = get_file(msg)) {
						msg.res = f_truncate(fil);
						msg.state = file_state(*fil);
						pr_trace("M4: f_truncate(#%x) -> %d\n", msg.fil, msg.res);
					}
					return true;
				},

				[&](IntercoreModuleFS::Puts &msg) {
					if (auto *fil = files.get(msg.fil)) {
						msg.bytes_written = f_puts(msg.buffer.data(), fil);
						msg.state = file_state(*fil);
						pr_trace("M4: f_puts(#%x) -> %d\n", msg.fil, msg.bytes_written);
					} else {
						msg.bytes_written = (uint32_t)-1;
					}
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

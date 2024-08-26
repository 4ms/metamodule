#include "CoreModules/fs_access.hh"
#include "console/pr_dbg.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/inter_core_comm.hh"
#include "static_buffers.hh"
#include "util/padded_aligned.hh"

#include <string_view>

namespace MetaModule
{

using enum IntercoreModuleFSMessage::MessageType;
using FatFsOp = IntercoreModuleFSMessage::FatFsOp;

struct FS::Impl {
	static constexpr uint32_t IPCC_ChanCore0 = 2;
	static constexpr uint32_t IPCC_ChanCore1 = 3;

	using CommModuleFS0 =
		mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, IntercoreModuleFSMessage, IPCC_ChanCore0>;

	using CommModuleFS1 =
		mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, IntercoreModuleFSMessage, IPCC_ChanCore1>;

	static inline CommModuleFS0 comm_core0{StaticBuffers::icc_module_fs_message_core0};
	static inline CommModuleFS1 comm_core1{StaticBuffers::icc_module_fs_message_core1};

	uint32_t last_uid = 0;

public:
	std::string root;
	std::string cwd;

	PaddedAligned<FIL, 64> padded_file;

	Impl(std::string_view root)
		: root{root} {
	}

	uint32_t unique_id() {
		return last_uid++;
	}

	uint32_t core() {
		return __get_MPIDR() & 0b1;
	}

	std::optional<uint32_t> send(IntercoreModuleFSMessage const &message, uint32_t id) {
		if (core() == 1)
			return comm_core1.send_message(message) ? id : std::optional<uint32_t>{};
		else
			return comm_core0.send_message(message) ? id : std::optional<uint32_t>{};
	}

	std::optional<uint32_t> request_close_file(FIL *fil) {
		uint32_t id = unique_id();
		IntercoreModuleFSMessage message{
			.message_type = FatFsOpMessage,
			.fatfs_req_id = id,
			.fatfs_op = FatFsOp::Close,
			.fil = fil,
		};

		return send(message, id);
	}

	std::optional<uint32_t> request_open_file(FIL *fil, std::string_view filename, uint8_t read_mode) {
		uint32_t id = unique_id();
		IntercoreModuleFSMessage message{
			.message_type = NumRequests, //FatFsOpMessage,
			.fatfs_req_id = id,
			.fatfs_op = FatFsOp::Open,
			.fil = fil,
			.mode = read_mode,
		};
		return send(message, id);
	}

	std::optional<uint32_t> request_seek_file(FIL *fil, uint64_t offset) {
		uint32_t id = unique_id();
		IntercoreModuleFSMessage message{
			.message_type = FatFsOpMessage,
			.fatfs_req_id = id,
			.fatfs_op = FatFsOp::Seek,
			.fil = fil,
			.file_offset = offset,
		};

		return send(message, id);
	}

	std::optional<uint32_t> request_read_file(FIL *fil, std::span<char> buffer) {
		uint32_t id = unique_id();
		IntercoreModuleFSMessage message{
			.message_type = FatFsOpMessage,
			.buffer = buffer,
			.fatfs_req_id = id,
			.fatfs_op = FatFsOp::Read,
			.fil = fil,
		};

		return send(message, id);
	}

	IntercoreModuleFSMessage get_message() {
		if (core() == 1)
			return comm_core1.get_new_message();
		else
			return comm_core0.get_new_message();
	}
};

FS::FS(std::string_view root)
	: impl{new Impl(root)} {
}

FS::~FS() = default;

FRESULT FS::f_open(FIL *fp, const char *path, uint8_t mode) {
	std::string fullpath = std::string("1:/") + path;
	// std::string fullpath = impl->root + path;

	pr_dbg("f_open %s, mode:%d\n", fullpath.c_str(), mode);

	// Block until the message sends
	//timeout?
	uint32_t msg_id{};

	auto start = HAL_GetTick();
	while (true) {
		if (auto id = impl->request_open_file(&impl->padded_file.data, fullpath.c_str(), mode); id) {
			// pr_dbg("Sent on core %u ok:\n", impl->core());
			msg_id = *id;
			break;
		} else {
			// pr_dbg("Sent on core %u blocked:\n", impl->core());
		}
		if (HAL_GetTick() - start > 3000) {
			pr_dbg("f_open timed out\n");
			return FR_TIMEOUT;
		}
	}

	// HAL_Delay(10);
	// pr_dbg("f_open sent\n");

	start = HAL_GetTick();
	while (true) {
		auto msg = impl->get_message();
		if (msg.message_type == FatFsOpMessage) {
			if (msg.fatfs_op == FatFsOp::Open && msg.fatfs_req_id == msg_id) {
				if (msg.res == FR_OK) {
					// Copy fp back to caller
					*fp = impl->padded_file.data;
				}
				return msg.res;

			} else {
				pr_dbg("Got unexpected op (%d) or id (%u vs %u)\n", msg.fatfs_op, msg.fatfs_req_id, msg_id);
				return FR_INT_ERR;
			}
		}

		if (HAL_GetTick() - start > 3000) {
			pr_dbg("Waiting for f_open response timed out\n");
			return FR_TIMEOUT;
		}
	}

	return FR_INT_ERR;
}

FRESULT FS::f_close(FIL *fp) {
	pr_dbg("f_close %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_read(FIL *fp, void *buff, unsigned btr, unsigned *br) {
	pr_dbg("f_read %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_write(FIL *fp, const void *buff, UINT btw, UINT *bw) {
	pr_dbg("f_write %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_lseek(FIL *fp, uint64_t ofs) {
	pr_dbg("f_lseek %p, %llu\n", fp, ofs);
	return FR_INT_ERR;
}

FRESULT FS::f_truncate(FIL *fp) {
	return FR_INT_ERR;
}

FRESULT FS::f_sync(FIL *fp) {
	pr_dbg("f_sync %p\n", fp);
	return FR_INT_ERR;
}

FRESULT FS::f_opendir(DIR *dp, const char *path) {
	pr_dbg("f_opendir %p %s\n", dp, path);
	return FR_INT_ERR;
}

FRESULT FS::f_closedir(DIR *dp) {
	pr_dbg("f_closedir %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_readdir(DIR *dp, FILINFO *fno) {
	pr_dbg("f_readdir %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_findfirst(DIR *dp, FILINFO *fno, const TCHAR *path, const TCHAR *pattern) {
	pr_dbg("f_findfirst %p %s %s\n", dp, path, pattern);
	return FR_INT_ERR;
}

FRESULT FS::f_findnext(DIR *dp, FILINFO *fno) {
	pr_dbg("f_findnext %p\n", dp);
	return FR_INT_ERR;
}

FRESULT FS::f_mkdir(const TCHAR *path) {
	pr_dbg("f_mkdir %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_unlink(const TCHAR *path) {
	return FR_INT_ERR;
}

FRESULT FS::f_rename(const TCHAR *path_old, const TCHAR *path_new) {
	return FR_INT_ERR;
}

FRESULT FS::f_stat(const char *path, FILINFO *fno) {
	pr_dbg("f_stat %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_utime(const TCHAR *path, const FILINFO *fno) {
	return FR_INT_ERR;
}

FRESULT FS::f_chdir(const TCHAR *path) {
	pr_dbg("f_chdir %s\n", path);
	return FR_INT_ERR;
}

FRESULT FS::f_getcwd(char *buff, uint32_t len) {
	return FR_INT_ERR;
}

FRESULT FS::f_expand(FIL *fp, FSIZE_t fsz, uint8_t opt) {
	return FR_INT_ERR;
}

int FS::f_putc(TCHAR c, FIL *fp) {
	return FR_INT_ERR;
}

int FS::f_puts(const TCHAR *str, FIL *cp) {
	return FR_INT_ERR;
}

int FS::f_printf(FIL *fp, const TCHAR *str, ...) {
	return FR_INT_ERR;
}

char *FS::f_gets(char *buff, int len, FIL *fp) {
	return nullptr;
}

//FRESULT FS::f_chdrive(const TCHAR *path);
// FRESULT FS::f_getfree(const TCHAR *path, DWORD *nclst, FATFS **fatfs); /* Get number of free clusters on the drive */
// FRESULT FS::f_getlabel(const TCHAR *path, TCHAR *label, DWORD *vsn);   /* Get volume label */
// FRESULT FS::f_setlabel(const TCHAR *label);							   /* Set volume label */
// FRESULT FS::f_mount(FATFS *fs, const TCHAR *path, uint8_t opt); /* Mount/Unmount a logical drive */
// FRESULT FS::f_mkfs (const TCHAR* path, const MKFS_PARM* opt, void* work, UINT len);	/* Create a FAT volume */
// FRESULT FS::f_fdisk(uint8_t pdrv, const LBA_t ptbl[], void *work); /* Divide a physical drive into some partitions */
// FRESULT FS::f_setcp(WORD cp);					  /* Set current code page */
// FRESULT FS::f_forward(FIL *fp, UINT (*func)(const uint8_t *, UINT), UINT btf, UINT *bf); /* Forward data to the stream */

} // namespace MetaModule

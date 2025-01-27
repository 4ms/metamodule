#pragma once
#include <optional>
#include <span>
#include <string_view>

struct FIL;
struct FILINFO;
struct DIR;

struct DiskDevice {

	DiskDevice() = default;
	virtual ~DiskDevice() = default;

	virtual bool mount_disk() = 0;

	// TODO: clarify differnce between these two:
	virtual bool unmount_drive() = 0;
	virtual bool unmount_disk() = 0;

	virtual bool is_mounted() = 0;

	virtual std::string_view volname() = 0;

	virtual bool open(std::string_view path, FIL *fil, uint8_t mode) = 0;
	virtual std::optional<size_t> read(FIL *fil, std::span<char> buffer) = 0;
	virtual void delete_file(std::string_view path) = 0;
	virtual uint64_t seek(FIL *fil, int offset, int whence) = 0;
	virtual int close(FIL *fil) = 0;

	virtual size_t write(FIL *fil, const std::span<const char> data) = 0;
	// virtual size_t write_file(std::string_view path, const std::span<const char> data) = 0;

	virtual bool stat(std::string_view path, FILINFO *info) = 0;
	virtual void set_file_timestamp(std::string_view path, uint32_t tm);

	virtual bool opendir(std::string_view path, DIR *dir) = 0;
	virtual bool readdir(DIR *dir, FILINFO *info) = 0;
	virtual bool closedir(DIR *dir) = 0;
};

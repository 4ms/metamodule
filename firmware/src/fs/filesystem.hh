#pragma once

#include "fat_file_io.hh"
#include "ff.h"
#include <algorithm>

namespace MetaModule
{

class Filesystem {
	static constexpr auto max_open_files = 64;

	static inline std::array<FIL *, max_open_files> descriptors{};
	static inline FatFileIO *mRamdisk{nullptr};

public:
	static void Init(FatFileIO &ramdisk) {
		mRamdisk = &ramdisk;
		for (auto &d : descriptors) {
			d = nullptr;
		}
	}

	static int open(const char *filename) {
		if (mRamdisk == nullptr) {
			return -1;
		}

		FIL fil;
		if (!mRamdisk->open(filename, &fil)) {
			return -1;
		}

		const auto idx = std::find(descriptors.begin(), descriptors.end(), nullptr);

		if (idx == descriptors.end()) {
			pr_err("cannot open any more files, max == %d", max_open_files);
			return -1;
		}

		*idx = new FIL;
		**idx = fil;

		return std::distance(descriptors.begin(), idx);
	}

	static int lseek(int fd, int offset, int whenc) {
		if (mRamdisk == nullptr) {
			return -1;
		}

		if (!fd_is_ok(fd)) {
			return -1;
		}

		FRESULT t{};
		if (whenc == SEEK_SET) {
			t = f_lseek(descriptors[fd], offset);
		} else if (whenc == SEEK_CUR) {
			t = f_lseek(descriptors[fd], f_tell(descriptors[fd]) + offset);
		} else {
			t = f_lseek(descriptors[fd], f_size(descriptors[fd]) + offset);
		}

		if (t != FR_OK) {
			return -1;
		}

		return f_tell(descriptors[fd]);
	}

	static int read(int fd, char *ptr, int len) {
		if (mRamdisk == nullptr) {
			return -1;
		}

		if (!fd_is_ok(fd)) {
			return -1;
		}

		const auto read = mRamdisk->read(descriptors[fd], std::span{ptr, static_cast<uint32_t>(len)});

		return read.value_or(-1);
	}

	static int close(int fd) {
		if (!fd_is_ok(fd)) {
			return -1;
		}

		mRamdisk->close(descriptors[fd]);

		delete descriptors[fd];
		descriptors[fd] = nullptr;

		return 0;
	}

private:
	static bool fd_is_ok(int fd) {
		return (fd >= 0 && fd < max_open_files && descriptors[fd] != nullptr);
	}
};
} // namespace MetaModule

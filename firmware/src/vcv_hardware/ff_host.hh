#pragma once
#include "ff.h"

namespace MetaModule
{

struct File {
	FIL fil{};

	File() {
		reset();
	}

	void reset() {
		fil.obj.fs = nullptr;
	}

	bool is_reset() {
		return fil.obj.fs == nullptr;
	}
};

struct Fileinfo {
	FILINFO filinfo;

	const char *fname() {
		return filinfo.fname;
	}

	bool is_dir() {
		return filinfo.fattrib & AM_DIR;
	}
};

struct Dir {
	DIR dir{};

	Dir() {
		reset();
	}

	void reset() {
		dir.obj.fs = nullptr;
	}

	bool is_reset() {
		return dir.obj.fs == nullptr;
	}
};

} // namespace MetaModule

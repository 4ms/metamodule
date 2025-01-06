#pragma once
#include "host_file_io.hh"

namespace MetaModule::Headless
{

struct FileIO {

	static std::string read_file(std::string_view filename) {
		std::string contents;

		auto file_sz = host_fileio.get_file_size(filename);
		if (file_sz > 0) {
			contents.resize(file_sz);
			auto sz_read = host_fileio.read_file(filename, contents);
			if (sz_read != file_sz) {
				printf("Error: file %s is %llu bytes but %llu read\n", filename.data(), file_sz, sz_read);
			}
		}

		return contents;
	}

	static inline HostFileIO host_fileio{Volume::SDCard, "."};
};

}; // namespace MetaModule::Headless

#pragma once
#include "fs/volumes.hh"
#include <filesystem>
#include <fstream>
#include <span>
#include <string_view>

struct HostFileIO {
	using Volume = MetaModule::Volume;
	const Volume _vol;
	const std::string_view _patch_dir;

	HostFileIO(Volume vol_id, std::string_view patch_dir)
		: _vol{vol_id}
		, _patch_dir{patch_dir} {
	}

	bool foreach_file_with_ext(const std::string_view extension, auto action) {
		namespace fs = std::filesystem;

		printf("Scanning %s for patches...\n", _patch_dir.data());

		for (const auto &entry : fs::directory_iterator(_patch_dir)) {
			auto fn = entry.path();
			if (fn.extension() == fs::path(".yml")) {
				auto last_modif = fs::last_write_time(fn);
				auto timestamp = last_modif.time_since_epoch().count();
				auto sz = (uint32_t)fs::file_size(fn);
				action(fn.c_str(), timestamp, sz);
			}
		}
		return true;
	}

	uint64_t read_file(const std::string_view filename, std::span<char> buffer) {
		std::ifstream ifs(filename.data(), std::ios::in);
		uint64_t sz = 0;
		if (ifs.is_open()) {
			ifs.seekg(0, std::ios::end);
			sz = ifs.tellg();
			ifs.seekg(0, std::ios::beg);
			ifs.read(buffer.data(), buffer.size_bytes());
			ifs.close();
		}
		return sz;
	}

	bool update_or_create_file(const std::string_view filename, const std::span<const char> data) {
		//TODO
		return false;
	}

	bool delete_file(std::string_view filename) {
		//TODO
		return false;
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		//TODO
	}

	std::string_view volname() {
		return "Host";
	}

	Volume vol_id() {
		return _vol;
	}

	bool is_mounted() {
		return true;
	}
};

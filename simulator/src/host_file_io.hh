#pragma once
#include "fs/dir_entry_kind.hh"
#include "fs/volumes.hh"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <span>
#include <string_view>

struct HostFileIO {
	using Volume = MetaModule::Volume;
	const Volume _vol;
	std::filesystem::path _root_dir;

	HostFileIO(Volume vol_id, std::string_view root_dir)
		: _vol{vol_id} {
		_root_dir = std::filesystem::absolute(root_dir);
	}

	bool foreach_file_with_ext(const std::string_view extension, auto action) {
		namespace fs = std::filesystem;

		std::cout << "Scanning " << _root_dir << " for " << extension << " files...\n";

		fs::current_path(_root_dir);

		fs::path full_path{"."};

		try {
			for (const auto &entry : fs::directory_iterator(_root_dir)) {
				auto fn = entry.path();
				if (fn.extension() == fs::path(extension)) {
					auto timestamp = convert_timestamp(fn.string());
					auto sz = (uint32_t)fs::file_size(fn);
					action(fn.string().c_str(), timestamp, sz);
				}
			}
		} catch (const fs::filesystem_error &e) {
			std::cout << "Error: " << e.what() << std::endl;
			return false;
		}

		return true;
	}

	// Returns false if dir cannot be opened
	bool foreach_dir_entry(const std::string_view path, auto action) {
		namespace fs = std::filesystem;

		fs::current_path(_root_dir);

		std::string f_path;

		if (path == "") {
			f_path = ".";
		} else if (path.starts_with("/")) {
			f_path = std::string(".").append(path);
		} else {
			f_path = path;
		}
		fs::path full_path{f_path};

		std::cout << "HostFileIO: foreach_dir_entry() in " << full_path << "\n";

		try {
			for (const auto &entry : fs::directory_iterator(full_path)) {
				auto fn = entry.path();
				auto entry_type = (entry.is_directory()) ? DirEntryKind::Dir : DirEntryKind::File;

				auto timestamp = convert_timestamp(fn.string());

				auto sz = entry.is_directory() ? 0 : (uint32_t)fs::file_size(fn);
				std::string name = fn.filename().string();

				action(std::string_view{name}, (uint32_t)timestamp, (uint32_t)sz, entry_type);
			}
		} catch (const fs::filesystem_error &e) {
			std::cout << "Error: " << e.what() << std::endl;
			return false;
		}

		return true;
	}

	uint64_t read_file(const std::string_view filename, std::span<char> buffer, size_t offset = 0) {
		auto filepath = normalize_path(filename);

		std::cout << "HostFileIO: read " << filepath << "\n";

		std::ifstream ifs(filepath, std::ios::in);
		uint64_t sz = 0;
		if (ifs.is_open()) {
			// Find file size
			ifs.seekg(0, std::ios::end);
			sz = ifs.tellg();

			ifs.seekg(offset, std::ios::beg);
			sz -= offset;

			ifs.read(buffer.data(), buffer.size_bytes());
			ifs.close();
		}
		return sz;
	}

	bool update_or_create_file(const std::string_view filename, const std::span<const char> buffer) {
		auto filepath = normalize_path(filename);

		std::cout << "HostFileIO: write " << filepath << "\n";

		auto ofs = std::ofstream{filepath, std::ios::out};
		uint64_t sz = 0;
		if (ofs.is_open()) {
			ofs.write(buffer.data(), buffer.size_bytes());
			ofs.close();
			sz = buffer.size_bytes();
		}
		return sz;
	}

	bool delete_file(std::string_view filename) {
		auto filepath = normalize_path(filename);

		std::cout << "HostFileIO: delete " << filepath << "\n";

		return std::filesystem::remove(filepath) > 0;
	}

	uint64_t get_file_size(std::string_view filename) {
		auto filepath = normalize_path(filename);

		std::cout << "HostFileIO: get file size " << filepath << "\n";

		std::ifstream ifs(filepath, std::ios::in);
		uint64_t sz = 0;
		if (ifs.is_open()) {
			// Find file size
			ifs.seekg(0, std::ios::end);
			sz = ifs.tellg();
			ifs.close();
		}
		return sz;
	}

	uint32_t get_file_timestamp(std::string_view filename) {
		auto filepath = normalize_path(filename);

		std::cout << "HostFileIO: get file timestamp " << filepath << "\n";

		return convert_timestamp(filepath);
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		//TODO?
	}

	// converts native filesystem timestamp to MM 32-bit timestamp
	uint32_t convert_timestamp(std::string const &filepath) {
		auto tm = std::filesystem::last_write_time(filepath);

		// returns unix timestamp (seconds since 1/1/1970)
		return std::chrono::duration_cast<std::chrono::seconds>(tm.time_since_epoch()).count();
	}

	std::string normalize_path(std::string_view filename) {
		// Interpret "/" root dir as _patch_dir
		std::filesystem::current_path(_root_dir);

		std::string filepath;
		if (filename.starts_with("/"))
			filepath = "." + std::string(filename);
		else
			filepath = filename;

		return filepath;
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

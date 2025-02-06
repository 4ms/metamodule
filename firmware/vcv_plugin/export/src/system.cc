#include "console/pr_dbg.hh"
#include "system/time.hh"
#include <filesystem>
#include <system.hpp>

namespace rack::system
{

namespace fs = std::filesystem;

std::string join(const std::string &path1, const std::string &path2) {
	return (fs::u8path(path1) / fs::u8path(path2)).string();
}

static void appendEntries(std::vector<std::string> &entries, const fs::path &dir, int depth) {
	for (const auto &entry : fs::directory_iterator(dir)) {
		entries.push_back(entry.path().string());
		// Recurse if depth > 0 (limited recursion) or depth < 0 (infinite recursion).
		if (depth != 0) {
			if (entry.is_directory()) {
				appendEntries(entries, entry.path(), depth - 1);
			}
		}
	}
}

std::vector<std::string> getEntries(const std::string &dirPath, int depth) {
	std::vector<std::string> entries;
	appendEntries(entries, fs::u8path(dirPath), depth);
	return entries;
}

bool exists(const std::string &path) {
	return fs::exists(fs::u8path(path));
}

bool isFile(const std::string &path) {
	return fs::is_regular_file(fs::u8path(path));
}

bool isDirectory(const std::string &path) {
	return fs::is_directory(fs::u8path(path));
}

uint64_t getFileSize(const std::string &path) {
	return fs::file_size(fs::u8path(path));
}

bool rename(const std::string &srcPath, const std::string &destPath) {
	// fs is read-only
	return false;
	// fs::rename(fs::u8path(srcPath), fs::u8path(destPath));
	// return true;
}

bool copy(const std::string &srcPath, const std::string &destPath) {
	// fs is read-only
	return false;
	// fs::copy(fs::u8path(srcPath), fs::u8path(destPath), fs::copy_options::recursive | fs::copy_options::overwrite_existing);
	// return true;
}

bool createDirectory(const std::string &path) {
	// fs is read-only
	return false;
	// return fs::create_directory(fs::u8path(path));
}

bool createDirectories(const std::string &path) {
	// fs is read-only
	return false;
	// return fs::create_directories(fs::u8path(path));
}

bool createSymbolicLink(const std::string &target, const std::string &link) {
	// fs is read-only
	return false;
	// fs::create_symlink(fs::u8path(target), fs::u8path(link));
	// return true;
}

bool remove(const std::string &path) {
	// fs is read-only
	return false;
	// return fs::remove(fs::u8path(path));
}

int removeRecursively(const std::string &pathStr) {
	// fs is read-only
	return false;
	// fs::path path = fs::u8path(pathStr);
	// // Make all entries writable before attempting to remove
	// for (auto &entry : fs::recursive_directory_iterator(path)) {
	// 	fs::permissions(entry.path(), fs::perms::owner_write, fs::perm_options::add);
	// }

	// return fs::remove_all(path);
}

std::string getWorkingDirectory() {
	// not supported
	printf("Warning: rack::system::getWorkingDirectory() not supported\n");
	return "";
	// return fs::current_path().string();
}

void setWorkingDirectory(const std::string &path) {
	// not supported
	printf("Warning: rack::system::setWorkingDirectory() not supported\n");
	// fs::current_path(fs::u8path(path));
}

std::string getTempDirectory() {
	// not supported
	printf("Warning: rack::system::getTempDirectory() not supported\n");
	return "";
	// return fs::temp_directory_path().string();
}

std::string getAbsolute(const std::string &path) {
	// TODO: use fatfs to resolve path
	printf("Warning: rack::system::getAbsolute() not supported\n");
	return path;
	// return fs::absolute(fs::u8path(path)).string();
}

std::string getCanonical(const std::string &path) {
	// TODO: use fatfs to resolve path
	printf("Warning: rack::system::getCanonical() not supported\n");
	return path;
	// return fs::canonical(fs::u8path(path)).string();
}

std::string getDirectory(const std::string &path) {
	return fs::u8path(path).parent_path().string();
}

std::string getFilename(const std::string &path) {
	return fs::u8path(path).filename().string();
}

std::string getStem(const std::string &path) {
	return fs::u8path(path).stem().string();
}

std::string getExtension(const std::string &path) {
	return fs::u8path(path).extension().string();
}

//// MetaModule impl:
static FILE *openFile(std::string const &path) {
	FILE *f = std::fopen(path.c_str(), "rb");
	if (!f) {
		pr_err("Cannot open file %s\n", path.c_str());
		return {};
	}

	return f;
}

static size_t getLength(FILE *f) {
	// Get file size so we can make a single allocation
	std::fseek(f, 0, SEEK_END);
	size_t len = std::ftell(f);
	std::fseek(f, 0, SEEK_SET);

	return len;
}

std::vector<uint8_t> readFile(const std::string &path) {
	std::vector<uint8_t> data;

	if (auto f = openFile(path)) {
		auto len = getLength(f);

		data.resize(len);

		std::fread(data.data(), 1, len, f);
		std::fclose(f);
	}

	return data;
}

uint8_t *readFile(const std::string &path, size_t *size) {
	if (auto f = openFile(path)) {
		auto len = getLength(f);

		auto *data = (uint8_t *)std::malloc(len);
		if (!data) {
			pr_err("rack::readFile(%s, sz) failed to allocate %zu bytes\n", path.c_str(), len);
			return data;
		}
		std::fread(data, 1, len, f);
		std::fclose(f);

		if (size)
			*size = len;

		return data;
	} else {
		pr_err("rack::readFile(%s, sz) failed to open\n", path.c_str());
		return nullptr;
	}
}

void writeFile(const std::string &path, const std::vector<uint8_t> &data) {
	// fs is read-only
	return;
	// FILE* f = std::fopen(path.c_str(), "wb");
	// if (!f)
	// 	return;
	// DEFER({
	// 	std::fclose(f);
	// });

	// std::fwrite(data.data(), 1, data.size(), f);
}

void archiveDirectory(const std::string &archivePath, const std::string &dirPath, int compressionLevel) {
	// fs is read-only
}

std::vector<uint8_t> archiveDirectory(const std::string &dirPath, int compressionLevel) {
	// not supported
	return {};
}

void unarchiveToDirectory(const std::string &archivePath, const std::string &dirPath) {
	// not supported
}

void unarchiveToDirectory(const std::vector<uint8_t> &archiveData, const std::string &dirPath) {
	// not supported
}

int getLogicalCoreCount() {
	return 1; // Not supported
}

void setThreadName(const std::string &name) {
	//ignored
}

std::string getStackTrace() {
	return "Stack trace not supported\n";
}

double getTime() {
	auto ticks = get_ticks();
	return (double)ticks / 1000.0;
}

double getUnixTime() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration<double>(duration).count();
}

void sleep(double time) {
	//?
}

std::string getOperatingSystemInfo() {
	return "MetaModule";
}

void openBrowser(const std::string &url) {
	//not supported
}

void openDirectory(const std::string &path) {
	//not supported
}

void runProcessDetached(const std::string &path) {
	// not supported
	// TODO: use async_thread
}

uint32_t getFpuFlags() {
	//not supported
	return 0;
	// uint64_t fpscr;
	// __asm__ volatile("vmrs %0, fpscr" : "=r"(fpscr));
	// return fpscr;
}

void setFpuFlags(uint32_t flags) {
	// not supported: modules cannot change FPU flags
	// uint64_t fpscr = flags;
	// __asm__ volatile("vmsr fpscr, %0" ::"r"(fpscr));
}

void resetFpuFlags() {
	uint32_t flags = getFpuFlags();
	// Set Flush-to-Zero
	// flags |= 1 << 24;
	// ARM64 always uses DAZ
	// Round-to-nearest is default
	// flags &= ~((1 << 22) | (1 << 23));
	setFpuFlags(flags);
}

} // namespace rack::system

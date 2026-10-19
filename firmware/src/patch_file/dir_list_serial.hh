#pragma once
#include "fs/dir_tree.hh"
#include "patch_file/patch_dir_list.hh"
#include <cstdint>
#include <cstring>
#include <span>
#include <string_view>

// Flat form of PatchDirList and DirTree<FileEntry>, for passing them between cores that don't
// share a memory layout. On MP2 the A35 is 64-bit and the M33 is 32-bit, so a std::vector or
// std::string built by one core can't be read (or appended to) by the other.
// MP1 doesn't need this: the M4 copies straight into the A7's PatchDirList.
//
// Format: numbers are uint32_t (both cores are little-endian), strings are a uint32_t length
// followed by the chars (no terminator). A tree is: name, num files, files, num dirs, dirs (recursive).

namespace MetaModule::DirListSerial
{

static constexpr uint32_t PatchDirListMagic = 0x50444C31; // "PDL1"
static constexpr uint32_t FileTreeMagic = 0x46545231;	  // "FTR1"
static constexpr uint32_t NoVolume = 0xFFFF'FFFF;
static constexpr unsigned MaxDepth = 8;

struct Writer {
	std::span<char> buf;
	uint32_t pos = 0;
	bool ok = true;

	void bytes(const void *src, uint32_t n) {
		if (!ok || n > buf.size() - pos) {
			ok = false;
			return;
		}
		std::memcpy(buf.data() + pos, src, n);
		pos += n;
	}

	void u32(uint32_t v) {
		bytes(&v, sizeof v);
	}

	void str(std::string_view s) {
		u32(s.size());
		bytes(s.data(), s.size());
	}
};

struct Reader {
	std::span<const char> buf;
	uint32_t pos = 0;
	bool ok = true;

	void bytes(void *dst, uint32_t n) {
		if (!ok || n > buf.size() - pos) {
			ok = false;
			return;
		}
		std::memcpy(dst, buf.data() + pos, n);
		pos += n;
	}

	uint32_t u32() {
		uint32_t v = 0;
		bytes(&v, sizeof v);
		return v;
	}

	std::string_view str() {
		auto n = u32();
		if (!ok || n > buf.size() - pos) {
			ok = false;
			return {};
		}
		std::string_view s{buf.data() + pos, n};
		pos += n;
		return s;
	}

	// A count of items that each take at least min_item_size bytes: rejects counts that can't fit
	uint32_t count(uint32_t min_item_size) {
		auto n = u32();
		if (ok && n > (buf.size() - pos) / min_item_size)
			ok = false;
		return ok ? n : 0;
	}
};

inline void write_entry(Writer &w, const FileEntry &f) {
	w.str(f.filename);
	w.u32(f.filesize);
	w.u32(f.timestamp);
}

inline void write_entry(Writer &w, const PatchFile &f) {
	w.str(f.filename);
	w.u32(f.filesize);
	w.u32(f.timestamp);
	w.str(f.patchname);
	w.u32(f.link_vol ? static_cast<uint32_t>(*f.link_vol) : NoVolume);
}

inline void read_entry(Reader &r, std::vector<FileEntry> &files) {
	auto filename = r.str();
	auto filesize = r.u32();
	auto timestamp = r.u32();
	if (r.ok)
		files.push_back({std::string(filename), filesize, timestamp});
}

inline void read_entry(Reader &r, std::vector<PatchFile> &files) {
	auto filename = r.str();
	auto filesize = r.u32();
	auto timestamp = r.u32();
	auto patchname = r.str();
	auto link_vol = r.u32();
	if (r.ok)
		files.emplace_back(filename,
						   filesize,
						   timestamp,
						   patchname,
						   link_vol == NoVolume ? std::nullopt : std::optional{static_cast<Volume>(link_vol)});
}

template<typename EntryT>
void write_tree(Writer &w, const DirTree<EntryT> &tree) {
	w.str(tree.name);
	w.u32(tree.files.size());
	for (auto const &file : tree.files)
		write_entry(w, file);
	w.u32(tree.dirs.size());
	for (auto const &dir : tree.dirs)
		write_tree(w, dir);
}

// Appends the files and dirs to tree (doesn't clear it first)
template<typename EntryT>
void read_tree(Reader &r, DirTree<EntryT> &tree, unsigned depth = 0) {
	if (depth > MaxDepth) {
		r.ok = false;
		return;
	}

	tree.name = r.str();

	constexpr uint32_t MinEntrySize = 3 * sizeof(uint32_t); // empty filename, size, timestamp
	for (auto i = r.count(MinEntrySize); i > 0 && r.ok; i--)
		read_entry(r, tree.files);

	constexpr uint32_t MinTreeSize = 3 * sizeof(uint32_t); // empty name, 0 files, 0 dirs
	for (auto i = r.count(MinTreeSize); i > 0 && r.ok; i--)
		read_tree(r, tree.dirs.emplace_back(), depth + 1);
}

// Returns the number of bytes written, or 0 if it doesn't fit in buf
inline uint32_t serialize(const PatchDirList &list, std::span<char> buf) {
	Writer w{buf};
	w.u32(PatchDirListMagic);
	for (auto mounted : list.mounted)
		w.u32(mounted);
	for (auto const &root : list.vol_root)
		write_tree(w, root);
	return w.ok ? w.pos : 0;
}

// Same result as PatchListHelper::copy_patchlist() on MP1: the USB, SD, and NOR flash volumes are
// replaced, and the RamDisk volume (which the A-core manages) is appended to.
inline bool deserialize(std::span<const char> buf, PatchDirList &list) {
	Reader r{buf};
	if (r.u32() != PatchDirListMagic)
		return false;

	list.clear_patches(Volume::USB);
	list.clear_patches(Volume::SDCard);
	list.clear_patches(Volume::NorFlash);

	for (auto &mounted : list.mounted)
		mounted = r.u32();
	for (auto &root : list.vol_root)
		read_tree(r, root);
	return r.ok;
}

// Returns the number of bytes written, or 0 if it doesn't fit in buf
inline uint32_t serialize(const DirTree<FileEntry> &tree, std::span<char> buf) {
	Writer w{buf};
	w.u32(FileTreeMagic);
	write_tree(w, tree);
	return w.ok ? w.pos : 0;
}

// Replaces the contents of tree
inline bool deserialize(std::span<const char> buf, DirTree<FileEntry> &tree) {
	Reader r{buf};
	if (r.u32() != FileTreeMagic)
		return false;

	tree.files.clear();
	tree.dirs.clear();
	read_tree(r, tree);
	return r.ok;
}

} // namespace MetaModule::DirListSerial

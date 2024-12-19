#include "console/pr_dbg.hh"
#include "gui/fonts/fonts.hh"
#include <algorithm>
#include <map>
#include <string>

extern "C" {

struct FONScontext {
	struct FontEntry {
		std::string name{};
	};
	std::map<unsigned, FontEntry> font_handles{};

	FONScontext() {
		pr_dbg("Creating FONScontext\n");
	}

	~FONScontext() {
		pr_dbg("Destroying FONScontext\n");
	}

	int get_handle_from_name(std::string const &name) {
		for (auto const &entry : font_handles) {
			if (entry.second.name == name)
				return entry.first;
		}
		return -1;
	}

	std::string_view get_name_from_handle(int handle) {
		if (handle < 0)
			return "";

		for (auto const &entry : font_handles) {
			if (entry.first == (unsigned)handle)
				return entry.second.name;
		}
		return "";
	}

	unsigned new_handle() {
		unsigned handle = 0;
		for (auto const &entry : font_handles) {
			handle = std::max(handle, entry.first);
		}
		return handle + 1;
	}
};

// TODO: This should load the file and put it in the ttf_cache
// our fons cache is just a map from ttf_cache entries to int
int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex) {
	if (MetaModule::load_ttf(name, path)) {
		auto handle = s->new_handle();
		s->font_handles[handle] = FONScontext::FontEntry{.name = name};
		pr_dbg("FONS: Adding font %s with handle %d\n", name, handle);
		return handle;

	} else {
		pr_warn("FONS: failed to load ttf for %s\n", name);
		return -1;
	}
}

int fonsAddFontMem(FONScontext *s, const char *name, unsigned char *data, int ndata, int freeData, int fontIndex) {
	pr_err("Adding font from memory not supported (yet?)\n");
	return -1;
}

int fonsGetFontByName(FONScontext *s, const char *name) {
	return s->get_handle_from_name(name);
}

const char *fonsGetFontNameByHandle(FONScontext *s, int handle) {
	return s->get_name_from_handle(handle).data();
}

static FONScontext *get_fonscontext() {
	static FONScontext fonscontext;
	return &fonscontext;
}

FONScontext *fonsCreateInternal() {
	return get_fonscontext();
}

void fonsDeleteInternal(FONScontext *s) {
}

void fonsResetFallbackFont(FONScontext *stash, int base) {
}

int fonsAddFallbackFont(FONScontext *stash, int base, int fallback) {
	return -1;
}

} //extern C

#include "console/pr_dbg.hh"
#include "gui/fonts/fonts.hh"
#include <algorithm>
#include <map>
#include <string>

extern "C" {

struct FONScontext {
	struct FontEntry {
		void const *ptr{nullptr};
		std::string name{};
	};
	std::map<unsigned, FontEntry> font_handles{};

	FONScontext() {
		pr_dbg("Creating FONScontext\n");
	}

	~FONScontext() {
		pr_dbg("Destroying FONScontext\n");
	}

	int get_handle_from_font(void const *font) {
		for (auto const &entry : font_handles) {
			if (entry.second.ptr == font) {
				pr_dbg("Found font ptr for %s in handles at %d\n", entry.second.name.c_str(), entry.first);
				return entry.first;
			}
		}
		return -1;
	}

	int get_handle_from_name(std::string const &name) {
		for (auto const &entry : font_handles) {
			if (entry.second.name == name)
				return entry.first;
		}
		return -1;
	}

	void const *get_ptr_from_handle(int handle) {
		if (handle < 0)
			return "";

		for (auto const &entry : font_handles) {
			if (entry.first == (unsigned)handle)
				return entry.second.ptr;
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

int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex) {
	if (auto font = MetaModule::get_font(name, path)) {

		auto handle = s->get_handle_from_font(font);

		if (handle < 0) {
			handle = s->new_handle();
			s->font_handles[handle] = FONScontext::FontEntry{.ptr = font, .name = name};
			pr_dbg("Adding font %s with handle %d\n", name, handle);
		}
		return handle;

	} else {
		pr_err("Font %s at path %s could not be loaded\n", name, path);
		return -1;
	}
}

int fonsAddFontMem(FONScontext *s, const char *name, unsigned char *data, int ndata, int freeData, int fontIndex) {
	// Check if it's already in the cache OR if we can load it by name
	if (auto font = MetaModule::get_font(name)) {
		auto handle = s->get_handle_from_font(font);
		s->font_handles[handle] = FONScontext::FontEntry{.ptr = font, .name = name};
		return handle;

	} else {
		pr_err("Adding font from memory not supported yet\n");
		return -1;
	}
}

int fonsGetFontByName(FONScontext *s, const char *name) {
	return s->get_handle_from_name(name);
}

void const *fonsGetFontByHandle(FONScontext *s, int handle) {
	return s->get_ptr_from_handle(handle);
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

#include "console/pr_dbg.hh"
#include "gui/fonts/ttf.hh"
#include <algorithm>
#include <map>
#include <string>

extern "C" {

struct FONScontext {
	struct FontEntry {
		std::string name{};
	};
	std::map<unsigned, FontEntry> font_handles{};

	static constexpr unsigned DefaultFontHandle = 0;

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
		unsigned handle = DefaultFontHandle;
		for (auto const &entry : font_handles) {
			handle = std::max(handle, entry.first);
		}
		return handle + 1;
	}

	void set_default_font(std::string_view name) {
		font_handles[DefaultFontHandle] = {.name = std::string(name)};
	}
};

int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex) {
	auto res = MetaModule::Fonts::load_ttf(name, path);

	if (res == MetaModule::Fonts::TTFLoadResult::Added) {
		auto handle = s->new_handle();
		s->font_handles[handle] = FONScontext::FontEntry{.name = name};
		pr_dbg("FONS: Adding font %s with handle %d\n", name, handle);
		return handle;

	} else if (res == MetaModule::Fonts::TTFLoadResult::Error) {
		pr_warn("FONS: failed to load ttf for %s, using default\n", name);
		return s->DefaultFontHandle;

	} else {
		// Already Exists
		return s->get_handle_from_name(name);
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
	auto s = get_fonscontext();
	s->set_default_font(MetaModule::Fonts::default_ttf_name());
	return s;
}

void fonsDeleteInternal(FONScontext *s) {
}

void fonsResetFallbackFont(FONScontext *stash, int base) {
}

int fonsAddFallbackFont(FONScontext *stash, int base, int fallback) {
	return -1;
}

} //extern C

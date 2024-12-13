#include "console/pr_dbg.hh"
#include "gui/fonts/fonts.hh"

extern "C" {

struct FONScontext {
	//not needed
	int _{};
};

int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex) {
	if (auto font = MetaModule::get_font(name)) {
		return MetaModule::get_handle_from_font(font);

	} else
		return -1;
}

int fonsAddFontMem(FONScontext *s, const char *name, unsigned char *data, int ndata, int freeData, int fontIndex) {
	// Check if it's already in the cache OR if we can load it by name
	if (auto font = MetaModule::get_font(name)) {
		return MetaModule::get_handle_from_font(font);

	} else {
		pr_err("Adding font from memory not supported by LVGL\n");
		return -1;
	}
}

int fonsGetFontByName(FONScontext *s, const char *name) {
	return MetaModule::get_handle_from_name(name);
}

void fonsDeleteInternal(FONScontext *s) {
}

void fonsResetFallbackFont(FONScontext *stash, int base) {
}

int fonsAddFallbackFont(FONScontext *stash, int base, int fallback) {
	return -1;
}
}

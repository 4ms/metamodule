extern "C" {

struct FONScontext {
	int _;
};

int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex) {
	return -1;
}

int fonsAddFontMem(FONScontext *s, const char *name, unsigned char *data, int ndata, int freeData, int fontIndex) {
	return -1;
}

int fonsGetFontByName(FONScontext *s, const char *name) {
	return -1;
}

const char *fonsGetFontNameByHandle(FONScontext *s, int handle) {
	return nullptr;
}

static FONScontext *get_fonscontext() {
	static FONScontext fonscontext;
	return &fonscontext;
}

FONScontext *fonsCreateInternal() {
	auto s = get_fonscontext();
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

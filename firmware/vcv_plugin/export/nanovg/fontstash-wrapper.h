#pragma once

typedef struct FONScontext FONScontext;

int fonsAddFont(FONScontext *s, const char *name, const char *path, int fontIndex);
int fonsAddFontMem(FONScontext *s, const char *name, unsigned char *data, int ndata, int freeData, int fontIndex);
int fonsGetFontByName(FONScontext *s, const char *name);

void fonsDeleteInternal(FONScontext *s);
void fonsResetFallbackFont(FONScontext *stash, int base);
int fonsAddFallbackFont(FONScontext *stash, int base, int fallback);

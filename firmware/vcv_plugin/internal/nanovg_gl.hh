#pragma once

struct NVGcontext;
struct NVGLUframebuffer;

NVGcontext *nvgCreatePixelBufferContext(void *canvas);
void nvgBindFrameBuffer(NVGcontext *, void *);

// void nvgluBindFramebuffer(NVGLUframebuffer *);
// NVGLUframebuffer *nvgluCreateFramebuffer(NVGcontext *ctx, int w, int h, int imageFlags);
// void nvgluDeleteFramebuffer(NVGLUframebuffer *fb);

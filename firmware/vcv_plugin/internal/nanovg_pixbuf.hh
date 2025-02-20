#pragma once

struct NVGcontext;
NVGcontext *nvgCreatePixelBufferContext(void *canvas, unsigned height);
void nvgDeletePixelBufferContext(NVGcontext *ctx);

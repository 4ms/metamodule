#pragma once

struct NVGcontext;
NVGcontext *nvgCreatePixelBufferContext(void *canvas);
void nvgDeletePixelBufferContext(NVGcontext *ctx);

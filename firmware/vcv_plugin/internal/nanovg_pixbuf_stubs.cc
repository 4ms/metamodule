#include <cstdint>
#include <span>

struct NVGcontext;

NVGcontext *
nvgCreatePixelBufferContext(void *canvas, std::span<uint32_t> buffer, uint32_t buffer_width, uint32_t px_per_3U) {
	return nullptr;
}

void nvgDeletePixelBufferContext(NVGcontext *ctx) {
}

// Registers the app's unwind tables (.eh_frame) with libgcc's unwinder, so C++ exceptions work.
// Normally crtbegin.o does this, but the A35 app links without the startup files (-nostartfiles).
// See the .eh_frame section in system/linker/stm32mp2xx_ca35.ld.

extern "C" {
extern const char __eh_frame_start[];
void __register_frame_info(const void *begin, void *object);
}

namespace
{
// libgcc's struct object (unwind-dw2-fde.h), which it fills in: 6 pointers on AArch64, with room to spare
void *eh_frame_object[16];

// Before any other constructors run, since they could throw
__attribute__((constructor(101))) void register_eh_frame() {
	__register_frame_info(__eh_frame_start, eh_frame_object);
}
} // namespace

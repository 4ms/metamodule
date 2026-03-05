#include "CoreModules/CoreProcessor.hh"
#include "concurrent_buffer.hh"
#include "midi/rotocontrol/messages.hh"
#include "patch/patch_data.hh"
#include <memory>

namespace MetaModule
{

class RotoControlSerializer {
	ConcurrentBuffer *cdc_buffer;
	RotoControlMessage msg;
	unsigned max_switch_pos = 3;

public:
	RotoControlSerializer(ConcurrentBuffer *buffer);

	// Flip and Slide switches with num_pos <= max_pos will be configured as Roto switches (buttons).
	// num_pos > max_pos will be configured as Roto knobs
	void config_max_switch_position(unsigned max_pos);

	void update_from_patch(PatchData const &pd, std::span<const std::unique_ptr<CoreProcessor>> modules);

	void ensure_startup_commands();
};

} // namespace MetaModule

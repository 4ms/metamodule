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
	bool startup_written = false;

public:
	RotoControlSerializer(ConcurrentBuffer *buffer);

	void update_from_patch(PatchData const &pd, std::span<const std::unique_ptr<CoreProcessor>> modules);

	void ensure_startup_commands();
};

} // namespace MetaModule

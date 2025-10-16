#pragma once
#include <cstdint>

namespace MetaModule
{

// Controls whether to apply suggested audio params from patch files
struct PatchSuggestedAudioSettings {
    bool apply_samplerate{true};
    bool apply_blocksize{true};

    void make_valid() {
        // Booleans are inherently valid; keep for symmetry/forward-compat
    }
};

} // namespace MetaModule


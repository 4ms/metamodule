#pragma once
#include "patch_play/patch_mod_queue.hh"

namespace MetaModule
{
class PatchPlayer;
class PatchPlayLoader;
class FileStorageProxy;
class OpenPatchManager;

// The objects core 0 makes that core 1 uses (MP1: A7SharedMemoryS)
struct AuxCoreObjects {
	PatchPlayer &patch_player;
	PatchPlayLoader &patch_playloader;
	FileStorageProxy &file_storage;
	OpenPatchManager &open_patch_manager;
	PatchModQueue &patch_mod_queue;
};

// Starts the second A35 core, which runs the GUI and plays its share of the patch's modules (see
// aux_core.cc). Returns once it's ready for the audio to start: the GUI is up, the plugins set to
// preload are loaded, and it's ready to play modules. Returns false if it didn't start.
bool start_aux_core(AuxCoreObjects const &objects);

} // namespace MetaModule

#pragma once

namespace MetaModule
{
class PatchPlayer;
class Ui;

// Starts the second A35 core, which plays its share of the patch's modules (see aux_core.cc).
// Must be called before any patch is loaded or audio starts.
bool start_aux_core(PatchPlayer &patch_player, Ui &ui);

} // namespace MetaModule

#include "patch_player.hh"
#include "patchlist.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchLoader {
	static inline uint32_t initial_patch = 7;

	PatchLoader(PatchList &patchlist, PatchPlayer &patchplayer)
		: patch_list{patchlist}
		, player{patchplayer} {
	}

	void load_initial_patch() {
		load_patch(initial_patch);
	}

	void load_patch(uint32_t patchid) {
		patch_list.set_cur_patch_index(patchid);

		auto patchname = patch_list.get_patch_name(patchid);
		printf_("Attempting load patch #%d, %s\n", patchid, patchname.data());

		bool ok = player.load_patch(patch_list.get_patch(patchid));
		if (!ok)
			printf_("Failed to load patch\n");
		else
			printf_("Loaded patch\r\n");
	}

private:
	PatchList &patch_list;
	PatchPlayer &player;
};
} // namespace MetaModule

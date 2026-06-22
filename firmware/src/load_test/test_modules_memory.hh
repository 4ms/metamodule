#pragma once
#include "general_io.hh"
#include "gui/slsexport/meta5/ui.h"
#include "load_test/test_modules.hh"
#include <cstdlib>

#ifdef MM_LOADTEST_MEASURE_MEMORY
#include "load_test/memory_tester.hh"
#include "system/alloc_watch.hh"
#include <map>
#endif

#ifndef SIMULATOR
#include <malloc.h>
#endif

namespace MetaModule::LoadTest
{

#ifndef SIMULATOR
inline size_t cur_uordblks() {
	return (size_t)mallinfo().uordblks;
}
#else
inline size_t cur_uordblks() {
	return 0;
}
#endif

#ifdef MM_LOADTEST_MEASURE_MEMORY
// Construct+destruct a single module once with the AllocationWatcher armed, then
// print a histogram (size -> count) of every operator-new block that was NOT freed.
// The widget tree is built with C++ new, so the leak shows up here by size, which
// maps directly to a type. (malloc/calloc/realloc are NOT tracked - if the histogram
// is empty but uordblks still grew, the leak is in C-style allocation instead.)
inline void dump_unfreed_blocks(std::string_view slug, auto append_file) {
	static AllocationWatcher w; // ~96KB; static to keep it off the stack

	w.reset();
	watch = &w;
	{
		auto module = ModuleFactory::create(slug);
		if (module) {
			plugin_module_init(module);
			module->set_samplerate(48000.f);
			module->update();
			plugin_module_deinit(module);
		}
	} // module (and its module_widget) destroyed here
	watch = nullptr; // stop tracking before we allocate anything for reporting

	std::map<size_t, unsigned> hist;
	size_t total = 0;
	size_t count = 0;
	for (auto const &b : w.allocs) {
		if (!b.dealloced) {
			hist[b.size]++;
			total += b.size;
			count++;
		}
	}

	printf("=== Unfreed operator-new blocks after 1 cycle of %.*s: %zu blocks, %zu bytes ===\n",
		   (int)slug.size(),
		   slug.data(),
		   count,
		   total);
	append_file("unfreed_size,count,subtotal\n");
	for (auto const &[sz, n] : hist) {
		char buf[64];
		snprintf(buf, sizeof buf, "%zu,%u,%zu\n", sz, n, sz * n);
		append_file(buf);
		printf("  %zu B x %u = %zu B\n", sz, n, sz * n);
	}
	if (w.too_many_allocs)
		printf("  WARNING: >4096 allocs in one cycle - histogram is incomplete\n");
}
#endif

// Leak-slope diagnostic.
//
// Repeatedly creates and destroys a single module while sampling uordblks
// (in-use heap bytes) after every cycle. The slope tells the two cases apart:
//   - slope flattens after cycle 0  => one-time per-TYPE allocation (e.g. a
//     lazily-built static lookup table). Permanent, but bounded per module type.
//   - slope stays positive          => per-INSTANCE leak: something allocated on
//     each create/onAdd is not freed on destroy/onRemove. Accumulates without bound.
//
// Two phases isolate where it comes from:
//   "module-only" : ModuleFactory::create -> onAdd -> update -> onRemove -> dtor.
//                   Isolates the module/rack adaptor. No PatchPlayer involved. Fast.
//   "full-load"   : player.load_patch -> update -> unload_patch. Matches the real
//                   load-test path; ~100ms/cycle due to the thread-resume delay in
//                   load_patch, so use a smaller iteration count for this phase.
inline void test_module_leak_slope(std::string_view slug, unsigned iterations, auto append_file) {
	if (iterations < 2)
		iterations = 2;

	std::string slugstr{slug};
	printf("=== Leak slope test: %s, %u iterations ===\n", slugstr.c_str(), iterations);
	lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Leak test %s", slugstr.c_str());

	if (!ModuleFactory::isValidSlug(slug)) {
		printf("Leak test: module '%s' not found\n", slugstr.c_str());
		append_file("error,module-not-found\n");
		lv_label_set_text(ui_MainMenuNowPlaying, "Leak test: module not found");
		return;
	}

#ifdef MM_LOADTEST_MEASURE_MEMORY
	// Pinpoint the leak: dump the sizes of blocks left unfreed after one cycle.
	dump_unfreed_blocks(slug, append_file);
#endif

	append_file("phase,iter,uordblks,delta_prev,delta_base\n");

	auto run_loop = [&](const char *phase, unsigned iters, auto &&cycle) {
		printf("--- %s (%u cycles) ---\n", phase, iters);
		size_t base = cur_uordblks();
		size_t prev = base;
		size_t first_after = base;

		for (unsigned i = 0; i < iters; i++) {
			cycle();

			size_t now = cur_uordblks();
			if (i == 0)
				first_after = now;

			char buf[96];
			snprintf(
				buf, sizeof buf, "%s,%u,%zu,%ld,%ld\n", phase, i, now, (long)now - (long)prev, (long)now - (long)base);
			append_file(buf);
			printf("%s", buf);

			prev = now;
			send_heartbeat();
		}

		long first_delta = (long)first_after - (long)base;
		long steady = ((long)prev - (long)first_after) / (long)(iters - 1);
		long total = (long)prev - (long)base;

		printf("%s SUMMARY: base=%zu  first-cycle=%+ld B  steady=%+ld B/cycle  total=%+ld B over %u cycles\n",
			   phase,
			   base,
			   first_delta,
			   steady,
			   total,
			   iters);

		if (steady > 64)
			printf("  --> PER-INSTANCE leak: ~%ld bytes not freed every create/destroy\n", steady);
		else if (first_delta > 1024)
			printf("  --> ONE-TIME per-type allocation (~%ld B); permanent but does not accumulate\n", first_delta);
		else
			printf("  --> clean: no significant growth\n");
	};

	// Phase A: module only -- isolates the rack module (onAdd/onRemove + ctor/dtor).
	run_loop("module-only", iterations, [&] {
		auto module = ModuleFactory::create(slug);
		if (!module)
			return;
		plugin_module_init(module);
		module->set_samplerate(48000.f);
		module->update();
		module->update();
		plugin_module_deinit(module);
	});

	// Phase B: full load/unload through the PatchPlayer (matches the real test path).
	// load_patch has a 100ms thread-resume delay, so cap this phase's cycle count.
	PatchPlayer player;
	PatchData patch;
	patch.blank_patch(slug);
	patch.add_module(slug);

	run_loop("full-load", std::min(iterations, 40u), [&] {
		auto res = player.load_patch(patch);
		if (res.success) {
			player.update_patch_singlecore();
			player.update_patch_singlecore();
		}
		if (player.is_loaded)
			player.unload_patch();
	});

	lv_label_set_text(ui_MainMenuNowPlaying, "Leak test finished");
	printf("=== Leak slope test complete: %s ===\n", slugstr.c_str());
}

} // namespace MetaModule::LoadTest

#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/moduleFactory.hh"
#include <array>
#include <cstdio>
#include <string_view>
#if defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__linux__)
#include <malloc.h>
#endif

namespace MetaModule::Headless
{

// Bytes of heap in use (0 if unknown on this host)
inline size_t heap_in_use() {
#if defined(__APPLE__)
	malloc_statistics_t stats{};
	malloc_zone_statistics(nullptr, &stats);
	return stats.size_in_use;
#elif defined(__linux__)
	return mallinfo2().uordblks;
#else
	return 0;
#endif
}

// Prints a module's elements, as the module view would see them
inline int dump_elements(std::string_view combined_slug) {
	// Same order as the Element variant
	constexpr std::array<std::string_view, std::variant_size_v<Element>> type_names{
		"Null",			  "Image",			  "Param",		  "Knob",		   "Slider",
		"SliderLight",	  "FlipSwitch",		  "SlideSwitch",  "MomentaryButton", "MomentaryButtonLight",
		"MomentaryButtonRGB", "LatchingButton", "Encoder",	  "EncoderRGB",	   "JackInput",
		"JackOutput",	  "MonoLight",		  "DualLight",	  "RgbLight",	   "TextDisplay",
		"DynamicTextDisplay", "DynamicGraphicDisplay", "AltParamContinuous", "AltParamChoice",
		"AltParamChoiceLabeled", "AltParamAction", "KnobSnapped"};
	static_assert(type_names.back() == "KnobSnapped" && type_names.size() == 27, "Update type_names to match Element");

	if (!ModuleFactory::isValidSlug(combined_slug)) {
		printf("Error: %.*s is not a registered module\n", (int)combined_slug.size(), combined_slug.data());
		return 1;
	}

	// A VCV-ported module's elements aren't final until it's been created
	auto heap_before = heap_in_use();
	auto module = ModuleFactory::create(combined_slug);
	auto heap_after = heap_in_use();
	if (!module)
		printf("Warning: could not create %.*s\n", (int)combined_slug.size(), combined_slug.data());
	else {
		// The first instance can include one-time allocations, so also measure a second one
		auto second = ModuleFactory::create(combined_slug);
		auto heap_second = heap_in_use();
		printf("Heap used by creating the module (host): first %zu kB, second %zu kB\n",
			   (heap_after - heap_before) / 1024,
			   (heap_second - heap_after) / 1024);
	}

	auto info = ModuleFactory::getModuleInfo(combined_slug);
	printf("%.*s: %zu elements, faceplate '%.*s'\n",
		   (int)combined_slug.size(),
		   combined_slug.data(),
		   info.elements.size(),
		   (int)ModuleFactory::getModuleFaceplate(combined_slug).size(),
		   ModuleFactory::getModuleFaceplate(combined_slug).data());

	for (unsigned i = 0; auto const &el : info.elements) {
		auto base = base_element(el);
		auto index = info.indices[i];
		auto type = el.index() < type_names.size() ? type_names[el.index()] : "?";

		printf("[%3u] %-21.*s x=%6.2f y=%6.2f w=%5.2f h=%5.2f \"%.*s\"",
			   i,
			   (int)type.size(),
			   type.data(),
			   base.x_mm,
			   base.y_mm,
			   base.width_mm,
			   base.height_mm,
			   (int)base.short_name.size(),
			   base.short_name.data());

		if (index.param_idx != index.NoElementMarker)
			printf(" param=%u", (unsigned)index.param_idx);
		std::visit(
			[](auto const &e) {
				if constexpr (std::is_base_of_v<Pot, std::decay_t<decltype(e)>>)
					printf(" default=%.4f", e.default_value);
			},
			el);
		if (index.input_idx != index.NoElementMarker)
			printf(" input=%u", (unsigned)index.input_idx);
		if (index.output_idx != index.NoElementMarker)
			printf(" output=%u", (unsigned)index.output_idx);
		if (index.light_idx != index.NoElementMarker)
			printf(" light=%u", (unsigned)index.light_idx);
		printf("\n");
		i++;
	}

	return 0;
}

} // namespace MetaModule::Headless

#pragma once
#include "CoreModules/moduleFactory.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "memory_tester.hh"
#include "tester.hh"

namespace MetaModule::LoadTest
{

struct ModuleEntry {
	static constexpr std::array<unsigned, 5> blocksizes{32, 64, 128, 256, 512};
	std::string slug;
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> isolated;
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> patched;
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> cv_modulated;
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> audio_modulated;
	std::array<ModuleLoadTester::Measurements, blocksizes.size()> knob_tweak;

	ModuleMemoryTester::Measurements mem_usage{};
};

std::vector<ModuleEntry> test_all_modules() {

	std::vector<ModuleEntry> res;

	lv_show(ui_MainMenuNowPlayingPanel);
	lv_show(ui_MainMenuNowPlaying);

	auto brands = ModuleFactory::getAllBrands();
	for (auto brand : brands) {
		auto slugs = ModuleFactory::getAllSlugs(brand);
		for (auto slug : slugs) {
			ModuleEntry entry;
			entry.slug = brand + ":" + slug;
			pr_info("Testing %s\n", slug.c_str());
			lv_label_set_text_fmt(ui_MainMenuNowPlaying, "Testing %s", entry.slug.c_str());

			auto mem_tester = ModuleMemoryTester{entry.slug};
			entry.mem_usage = mem_tester.run_test(ModuleMemoryTester::TestType::FirstRun);

			for (auto i = 0u; auto blocksize : ModuleEntry::blocksizes) {
				ModuleLoadTester tester(entry.slug);

				pr_trace("Block size %u\n", blocksize);

				pr_trace("Running all unpatched test\n");
				entry.isolated[i] = tester.run_test(blocksize, KnobTestType::AllStill, JackTestType::NonePatched);

				pr_trace("Running Zero'ed inputs test\n");
				entry.patched[i] = tester.run_test(blocksize, KnobTestType::AllStill, JackTestType::AllInputsZero);

				pr_trace("Running LFO test\n");
				entry.cv_modulated[i] = tester.run_test(blocksize, KnobTestType::AllStill, JackTestType::AllInputsLFO);

				pr_trace("Running audio-rate test\n");
				entry.audio_modulated[i] =
					tester.run_test(blocksize, KnobTestType::AllStill, JackTestType::AllInputsAudio);

				i++;
			}

			res.emplace_back(entry);
		}
	}

	lv_label_set_text(ui_MainMenuNowPlaying, "");

	return res;
}

std::string entries_to_csv(std::vector<ModuleEntry> const &entries) {
	constexpr float sampletime = 1'000'000.f / 48000.f;

	std::string s;

	// Header
	s = "Module, ";
	pr_info("Module, ");

	for (unsigned int blocksize : ModuleEntry::blocksizes) {
		s += "Isolated-" + std::to_string(blocksize) + ", ";
		pr_info("Isolated-%u, ", blocksize);
	}

	for (unsigned int blocksize : ModuleEntry::blocksizes) {
		s += "InputsZero-" + std::to_string(blocksize) + ", ";
		pr_info("InputsZero-%u, ", blocksize);
	}

	for (unsigned int blocksize : ModuleEntry::blocksizes) {
		s += "InputsLFOs-" + std::to_string(blocksize) + ", ";
		pr_info("InputsLFOs-%u, ", blocksize);
	}

	for (unsigned int blocksize : ModuleEntry::blocksizes) {
		s += "InputsAudio-" + std::to_string(blocksize) + ", ";
		pr_info("InputsAudio-%u, ", blocksize);
	}

	s += "PeakStartupMem, PeakRunningMem, LeakedMem, DoubleFree?";
	pr_info("PeakStartupMem, PeakRunningMem, LeakedMem, DoubleFree?, Valid");

	s += "\n";
	pr_info("\n");

	// Body
	for (auto const &entry : entries) {
		s += entry.slug + ", ";
		pr_info("%s, ", entry.slug.c_str());

		auto report_cpu = [&s](auto entryitem) {
			char buf[8];
			snprintf(buf, 8, "%.3f, ", entryitem.average_run_time / sampletime);
			s += buf;
			pr_info("%.3f, ", entryitem.average_run_time / sampletime);
		};

		for (auto i = 0u; i < ModuleEntry::blocksizes.size(); i++) {
			report_cpu(entry.isolated[i]);
		}

		for (auto i = 0u; i < ModuleEntry::blocksizes.size(); i++) {
			report_cpu(entry.patched[i]);
		}

		for (auto i = 0u; i < ModuleEntry::blocksizes.size(); i++) {
			report_cpu(entry.cv_modulated[i]);
		}

		for (auto i = 0u; i < ModuleEntry::blocksizes.size(); i++) {
			report_cpu(entry.audio_modulated[i]);
		}

		if (entry.mem_usage.results_invalid) {
			s += "CAN'T MEASURE, , , ";
		} else {
			s += std::to_string(entry.mem_usage.peak_mem_startup) + ", ";
			s += std::to_string(entry.mem_usage.peak_running_mem) + ", ";
			s += std::to_string(entry.mem_usage.mem_leaked) + ", ";
			s += entry.mem_usage.double_free ? "YES" : "n";
		}
		pr_info("%zu, %zu, %lld, %d, %s\n",
				entry.mem_usage.peak_mem_startup,
				entry.mem_usage.peak_running_mem,
				entry.mem_usage.mem_leaked,
				entry.mem_usage.double_free,
				entry.mem_usage.results_invalid ? "TOOMANYALLOCS" : "ok");

		s += "\n";
		pr_info("\n");
	}

	return s;
}

} // namespace MetaModule::LoadTest

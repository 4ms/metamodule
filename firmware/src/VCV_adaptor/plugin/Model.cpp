#include "Model.hpp"
#include "util/overloaded.hh"

namespace rack::plugin
{

// Transfer ownership of a model's strings from the Module and ModuleWidget (as VCV does) to the Model/Pluin (which is what MetaModule wants)
// This is done by copying the strings that elements[] string_views point to, and putting the copy in strings[] (which is a member of Model)
// Then point the elements[] string_views to strings[].

void Model::move_strings() {
	using namespace MetaModule;

	for (auto &element : elements) {
		std::visit(
			[this](BaseElement &el) {
				el.short_name = strings.emplace_back(el.short_name);
				el.long_name = strings.emplace_back(el.long_name);
			},
			element);

		std::visit(overloaded{[](BaseElement &el) {},
							  [this](ImageElement &el) {
								  el.image = strings.emplace_back(el.image);
							  }},
				   element);

		std::visit(overloaded{[](BaseElement &el) {},
							  [this](Slider &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);
							  }},
				   element);

		std::visit(overloaded{[](BaseElement &el) {},
							  [this](FlipSwitch &el) {
								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);

								  for (auto &frame : el.frames) {
									  frame = strings.emplace_back(frame);
								  }
							  }},
				   element);

		std::visit(overloaded{[](BaseElement &el) {},
							  [this](SlideSwitch &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);

								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);
							  }},
				   element);
	}
}

std::string_view Model::add_string(std::string_view str) {
	return strings.emplace_back(str);
}

inline void inspect_sv(std::string_view const &sv) {
	printf("%.*s %p(+%u)\n", (int)sv.size(), sv.data(), sv.data(), sv.size());
}

void Model::debug_dump_strings() {
	using namespace MetaModule;

	for (auto const &s : strings)
		printf("strtab: %p %s\n", s.data(), s.c_str());

	printf("Dumping element strings: (%zu)\n", elements.size());
	for (auto &element : elements) {
		printf("Type %zu\n", element.index());
		auto el = base_element(element);
		printf("el.short_name: %.*s: %p\n", (int)el.short_name.size(), el.short_name.data(), el.short_name.data());

		std::visit(overloaded{[](BaseElement const &el) {},
							  [](ImageElement const &el) {
								  printf("image: ");
								  inspect_sv(el.image);
							  }},
				   element);

		std::visit(overloaded{[](BaseElement const &el) {},
							  [](Slider const &el) { inspect_sv(el.image_handle); },
							  [](SlideSwitch const &el) {
								  for (auto &pos_name : el.pos_names) {
									  printf("slide switch el.pos_names[]: ");
									  inspect_sv(pos_name);
								  }
								  inspect_sv(el.image_handle);
							  },
							  [](FlipSwitch const &el) {
								  for (auto &pos_name : el.pos_names) {
									  printf("flip switch el.pos_names[]: ");
									  inspect_sv(pos_name);
								  }
							  }},
				   element);
	}

	printf("\n");
}

} // namespace rack::plugin

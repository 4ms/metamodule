#include <rack.hpp>

inline void load_ext_builtin_plugins(std::list<rack::plugin::Plugin> &internal_plugins) {
	extern void init_Venom(rack::plugin::Plugin *);
	init_Venom(&internal_plugins.emplace_back("Venom"));
}

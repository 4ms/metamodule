#include <cstdint>

namespace MetaModule
{

void peg_task_to_core(uint32_t module_id, uint32_t core_id) {
}

void pause_module_threads() {
}

void pause_module_threads(unsigned) {
}

void resume_module_threads() {
}

void resume_module_threads(unsigned) {
}

bool is_any_thread_executing() {
	return false;
}

} // namespace MetaModule


namespace MetaModule
{

static constexpr unsigned NUM_PROCESSES = 8;

enum class Processes {
	Core0Main = 0, // startup
	Core0AsyncThread = 1,
	Core0Audio = 2, // AudioStream

	Core1Main = 3, // GUI
	Core1AsyncThread = 4,
	Core1ReadPatchElements = 5,
	Core1Audio = 6, // AuxPlayer

	Unknown,
};

Processes get_current_proc();
int get_current_proc_id();

} // namespace MetaModule

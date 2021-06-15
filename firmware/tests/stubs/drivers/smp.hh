#include <cstdint>
#include <functional>
struct SMPControl {
	static void notify(uint32_t) {}

	static void write(uint32_t) {}
	static uint32_t read()
	{
		return 0;
	}
};

struct SMPThread {
	static void run(std::function<void()> entry) {}

	static void join() {}
};

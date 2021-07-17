#pragma once
template<int dummy>
struct DebugPin {
	static void high();
	static void low();
};

struct Debug {
	using Pin0 = DebugPin<0>;
	using Pin1 = DebugPin<0>;
	using Pin2 = DebugPin<0>;
	using Pin3 = DebugPin<0>;
};

#pragma once
struct PinStub {
	static void high() {}
	static void low() {}
};

struct Debug {
	using Pin0 = PinStub;
	using Pin1 = PinStub;
	using Pin2 = PinStub;
	using Pin3 = PinStub;
	using red_LED1 = PinStub;
	using red_LED2 = PinStub;
	using green_LED1 = PinStub;
	using green_LED2 = PinStub;
};

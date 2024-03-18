#pragma once
#include <rack.hpp>

struct CommJack {
protected:
	rack::Port &port;
	unsigned idx;

public:
	CommJack(rack::Port &port, unsigned idx)
		: port{port}
		, idx{idx} {
	}

	float getId() {
		return idx;
	}

	bool isConnected() {
		return port.isConnected();
	}
};

struct CommInputJack : CommJack {
	CommInputJack(rack::Input &port, unsigned idx)
		: CommJack{port, idx} {
	}

	float getValue() {
		return port.getVoltage();
	}
};

struct CommOutputJack : CommJack {
	CommOutputJack(rack::Output &port, unsigned idx)
		: CommJack{port, idx} {
	}

	void setValue(float val) {
		return port.setVoltage(val);
	}
};

#pragma once
#include "audio.hh"

class Controls {

};

class Params {
private:
	Controls controls_;

public:
	void read();
	void update();
};


class Ui {
public:
	Params params;
	Audio audio;

public:
	Ui() {}
};

#pragma once
#include <string>
namespace rack::app
{
struct PortWidget {};
} // namespace rack::app

struct NVGcolor {
	union {
		float rgba[4];
		struct {
			float r, g, b, a;
		};
	};
};
typedef struct NVGcolor NVGcolor;

static NVGcolor dummyColor;
inline NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) { return dummyColor; }

namespace rack
{
struct ParamHandle {
	int moduleId = -1;
	int paramId = 0;
	int *module = NULL;

	std::string text;
	NVGcolor color;
};

} // namespace rack

struct _Engine {
	void removeParamHandle(rack::ParamHandle *) {}
	void removeParamHandle_NoLock(rack::ParamHandle *) {}
	rack::ParamHandle *getParamHandle(int, int) { return {}; }
	void updateParamHandle(rack::ParamHandle *, int, int, bool) {}
	void updateParamHandle_NoLock(rack::ParamHandle *, int, int, bool) {}
	void addParamHandle(rack::ParamHandle *) {}
};

struct _APP {
	_Engine *engine;
};

static _APP oAPP;

// export to tests:
_APP *APP = &oAPP;

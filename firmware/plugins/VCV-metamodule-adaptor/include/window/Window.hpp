#pragma once

#include <map>
#include <memory>

#include <common.hpp>
#include <math.hpp>
#include <window/Svg.hpp>

#define GLEW_STATIC
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#define NANOVG_GL2
#include <nanovg_gl.h>
// #include <nanovg_gl_utils.h>

namespace rack::window
{

// Constructing these directly will load from the disk each time. Use the load() functions to load from disk and cache them as long as the shared_ptr is held.

struct Font {
	NVGcontext *vg{};
	int handle = -1;

	std::string filename;

	void loadFile(const std::string &filename, NVGcontext *vg) {
		this->filename = filename;
	}
};

struct Image {
	NVGcontext *vg{};
	int handle = -1;

	std::string filename;

	void loadFile(const std::string &filename, NVGcontext *vg) {
		this->filename = filename;
	}
};

struct Window {
	GLFWwindow *win = nullptr;
	NVGcontext *vg = nullptr;
	NVGcontext *fbVg = nullptr;
	float pixelRatio = 1.f;
	float windowRatio = 1.f;
	std::shared_ptr<Font> uiFont;

	// clang-format off
	math::Vec getSize(){ return {}; }
	void setSize(math::Vec size){}
	void close(){}
	void cursorLock(){}
	void cursorUnlock(){}
	bool isCursorLocked(){ return {}; }
	int getMods(){ return {}; }
	void setFullScreen(bool fullScreen){}
	bool isFullScreen(){ return {}; }
	double getMonitorRefreshRate(){ return {}; }
	double getFrameTime(){ return {}; }
	double getLastFrameDuration(){ return {}; }
	double getFrameDurationRemaining(){ return {}; }

	std::shared_ptr<Font> loadFont(const std::string &filename){ return {}; }
	std::shared_ptr<Image> loadImage(const std::string &filename){ return {}; }
	std::shared_ptr<Svg> loadSvg(const std::string &filename) { return Svg::load(filename); }
	// clang-format on
};

} // namespace rack::window

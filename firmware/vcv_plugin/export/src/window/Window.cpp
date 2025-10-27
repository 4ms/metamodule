#include "window/Window.hpp"
#include "console/pr_dbg.hh"
#include <asset.hpp>
#include <context.hpp>
#include <system.hpp>

namespace rack::window
{

Font::~Font() = default;

void Font::loadFile(const std::string &filename, NVGcontext *vg) {
	if (vg)
		this->vg = vg;

	auto name = filename;
	if (auto pos = filename.find_last_of("."); pos != std::string::npos) {
		name = name.substr(0, pos);
	}
	if (auto pos = filename.find_last_of("/"); pos != std::string::npos) {
		name = name.substr(pos + 1);
	}

	auto path = rack::asset::system(filename);

	handle = nvgCreateFont(vg, name.c_str(), path.c_str());
	if (handle < 0) {
		pr_err("Failed to load font %s (%s)\n", filename.c_str(), name.c_str());
		return;
	}

	pr_dbg("Loaded font %s, with handle %d\n", filename.c_str(), handle);
}

std::shared_ptr<Font> Font::load(const std::string &filename) {
	return rack::contextGet()->window->loadFont(filename);
}

///////////////

void Image::loadFile(const std::string &filename, NVGcontext *vg) {
	std::vector<uint8_t> data = system::readFile(filename);

	// Don't use nvgCreateImage because it doesn't properly handle UTF-8 filenames on Windows.
	handle = nvgCreateImageMem(vg, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY, data.data(), data.size());

	if (handle <= 0)
		pr_err("Failed to load image %s", filename.c_str());

	pr_dbg("Loaded image %s", filename.c_str());
}

std::shared_ptr<Image> Image::load(const std::string &filename) {
	return rack::contextGet()->window->loadImage(filename);
}

Image::~Image() = default;

///////////////

struct Window::Internal {
	std::map<std::string, std::shared_ptr<Font>> fontCache;
	std::map<std::string, std::shared_ptr<Image>> imageCache;

	bool fbdirty_subpx{};
	int fb_count{};
};

Window::Window()
	: internal{std::make_unique<Internal>()} {
	uiFont = std::make_shared<Font>();
}

Window::~Window() = default;

std::shared_ptr<Font> Window::loadFont(const std::string &filename) {
	const auto &pair = internal->fontCache.find(filename);
	if (pair != internal->fontCache.end())
		return pair->second;

	// Load font
	auto font = std::make_shared<Font>();
	font->loadFile(filename, vg);
	internal->fontCache[filename] = font;

	return font;
}

std::shared_ptr<Image> Window::loadImage(const std::string &filename) {
	const auto &pair = internal->imageCache.find(filename);
	if (pair != internal->imageCache.end())
		return pair->second;

	// Load image
	auto image = std::make_shared<Image>();
	image->loadFile(filename, vg);
	internal->imageCache[filename] = image;

	return image;
}

math::Vec Window::getSize() {
	return {};
}
void Window::setSize(math::Vec size) {
}
void Window::run() {
}
void Window::step() {
}
void Window::screenshot(const std::string &screenshotPath) {
}
void Window::screenshotModules(const std::string &screenshotsDir, float zoom) {
}
void Window::close() {
}
void Window::cursorLock() {
}
void Window::cursorUnlock() {
}
bool Window::isCursorLocked() {
	return true;
}
int Window::getMods() {
	return 0;
}
void Window::setFullScreen(bool fullScreen) {
}
bool Window::isFullScreen() {
	return false;
}
double Window::getMonitorRefreshRate() {
	return 1;
}
double Window::getFrameTime() {
	return 1;
}
double Window::getLastFrameDuration() {
	return 1;
}
double Window::getFrameDurationRemaining() {
	return 0;
}
bool &Window::fbDirtyOnSubpixelChange() {
	return internal->fbdirty_subpx;
}
int &Window::fbCount() {
	return internal->fb_count;
}

} // namespace rack::window

#include "window/Window.hpp"
#include "console/pr_dbg.hh"
// #include "gui/fonts/fonts.hh"
#include <asset.hpp>
#include <context.hpp>
#include <system.hpp>

namespace rack::window
{

Font::~Font() = default;

void Font::loadFile(const std::string &filename, NVGcontext *vg) {
	this->vg = vg;

	auto name = filename;
	if (auto pos = filename.find_last_of("."); pos != std::string::npos) {
		name = name.substr(0, pos);
	}
	if (auto pos = filename.find_last_of("/"); pos != std::string::npos) {
		name = name.substr(pos + 1);
	}

	auto path = rack::asset::system(filename);

	size_t size = 0;
	auto data = rack::system::readFile(path, &size);

	if (size > 0 && data) {
		// Transfer ownership of font data to font object
		handle = nvgCreateFontMem(vg, name.c_str(), data, size, 0);
		if (handle < 0) {
			std::free(data);
			pr_err("Failed to load font %s (%s)", filename.c_str(), name.c_str());
		}
	} else {
		pr_err("Failed to open font file %s", filename.c_str());
	}

	pr_dbg("Loaded font %s", filename.c_str());
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
};

Window::Window()
	: internal{std::make_unique<Internal>()} {
}

Window::~Window() = default;

std::shared_ptr<Font> Window::loadFont(const std::string &filename) {
	const auto &pair = internal->fontCache.find(filename);
	if (pair != internal->fontCache.end())
		return pair->second;

	// Load font
	std::shared_ptr<Font> font;
	font = std::make_shared<Font>();
	font->loadFile(filename, vg);
	internal->fontCache[filename] = font;

	return font;
}

std::shared_ptr<Image> Window::loadImage(const std::string &filename) {
	const auto &pair = internal->imageCache.find(filename);
	if (pair != internal->imageCache.end())
		return pair->second;

	// Load image
	std::shared_ptr<Image> image;
	image = std::make_shared<Image>();
	image->loadFile(filename, vg);
	internal->imageCache[filename] = image;

	return image;
}

} // namespace rack::window

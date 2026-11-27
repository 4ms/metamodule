#include "doctest.h"
#include "gui/elements/svg_file.hh"

using namespace MetaModule;

TEST_CASE("SVG file for an image name") {
	CHECK(SvgFile::path_for("A:ram:/4ms/comp/knob_x.png") == "A:ram:/4ms/comp/knob_x.svg");
	CHECK(SvgFile::path_for("rack-lib/PJ301M-dark.png") == "rack-lib/PJ301M-dark.svg");
	CHECK(SvgFile::path_for("Brand/panel.svg") == "Brand/panel.svg");
	CHECK(SvgFile::path_for("Brand/v1.2/panel") == "Brand/v1.2/panel.svg");
}

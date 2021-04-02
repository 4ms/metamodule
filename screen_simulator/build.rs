fn main() {
    // pkg_config::Config::new()
    //     .atleast_version("1.2")
    //     .probe("z")
    //     .unwrap();

    let src = ["mms/mms.cc", "../H7/lib/adafruit_gfx/Adafruit_GFX_Library/Adafruit_GFX.cpp", "../H7/lib/adafruit_gfx/arduino/Print.cpp", "../H7/src/patchlist.cc" ];
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(true)
        .files(src.iter())
        .include("../shared")
        .include("../shared/patch")
        .include("../H7/src")
        .include("../H7/lib/adafruit_gfx")
        .include("../H7/lib/adafruit_gfx/arduino")
        .include("mms")
        .include("mms/stubs")
        .flag("-std=c++2a")
        .flag("-Wno-unused-parameter");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

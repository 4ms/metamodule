fn main() {
    println!("cargo:rerun-if-changed=../H7/src/pages/sim_test_page.hh");
    let src = [
        "mms/mms.cc",
        "../H7/lib/adafruit_gfx/arduino/Print.cpp",
        "../H7/src/patchlist.cc",
        "../H7/src/pages/fonts.cc",
        "../H7/src/pages/page_manager.cc",
    ];
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
        .flag("-DSIMULATOR")
        .flag("-std=c++2a")
        .flag("-Wno-unused-parameter");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

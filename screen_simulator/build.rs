fn main() {
    // pkg_config::Config::new()
    //     .atleast_version("1.2")
    //     .probe("z")
    //     .unwrap();

    let src = ["mms/mms.cc"];
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(true)
        .files(src.iter())
        .include("../H7/src")
        .include("../shared")
        .include("mms")
        .flag("-std=c++2a")
        .flag("-Wno-unused-parameter");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

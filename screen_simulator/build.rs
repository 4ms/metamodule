fn main() {
    println!("cargo:rerun-if-changed=../firmware/src/pages/");
    println!("cargo:rerun-if-changed=mms/mms.cc");

    //
    // Build mcufont library
    //
    let mut mcufont_src: Vec<String> = Vec::new();
    mcufont_src.push(String::from("../firmware/lib/mcufont/decoder/mf_font.c"));
    mcufont_src.push(String::from("../firmware/lib/mcufont/decoder/mf_kerning.c"));
    mcufont_src.push(String::from("../firmware/lib/mcufont/decoder/mf_bwfont.c"));
    mcufont_src.push(String::from("../firmware/lib/mcufont/decoder/mf_rlefont.c"));
    mcufont_src.push(String::from(
        "../firmware/lib/mcufont/decoder/mf_scaledfont.c",
    ));
    mcufont_src.push(String::from(
        "../firmware/lib/mcufont/decoder/mf_wordwrap.c",
    ));
    mcufont_src.push(String::from(
        "../firmware/lib/mcufont/decoder/mf_encoding.c",
    ));
    mcufont_src.push(String::from("../firmware/lib/mcufont/decoder/mf_justify.c"));
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(false)
        .files(mcufont_src.iter())
        .include("../firmware/lib/mcufont/decoder")
        .include("../firmware/lib/mcufont/fonts")
        .flag("-Wno-unused-parameter");
    build.compile("mcufont");

    //
    // Build mms app
    //
    let mut src: Vec<String> = Vec::new();
    src.push(String::from("mms/mms.cc"));
    src.push(String::from("../firmware/lib/printf/printf.c"));
    src.push(String::from("../firmware/src/print.cc"));
    src.push(String::from("../firmware/src/patchlist.cc"));
    src.push(String::from("../firmware/src/pages/page_manager.cc"));
    src.push(String::from("../shared/util/math_tables.cc"));

    use glob::glob;
    for entry in glob("../shared/CoreModules/*.cpp").expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            src.push(format!("{}", f_name));
        }
    }

    println!("cargo:rerun-rustc-link-lib=mcufont");
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(true)
        .files(src.iter())
        .flag("--includestubs/sys/alloc_buffer.hh")
        .include("../firmware/lib/printf")
        .include("mms")
        .include("mms/stubs")
        .include("../shared")
        .include("../shared/util")
        .include("../shared/patch")
        .include("../firmware/src")
        .include("../firmware/lib/mcufont/decoder")
        .include("../firmware/lib/mcufont/fonts")
        .flag("-DSIMULATOR")
        .flag("-std=c++2a")
        .flag("-Wno-unused-parameter");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

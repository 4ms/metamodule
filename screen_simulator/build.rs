fn main() {
    println!("cargo:rerun-if-changed=../firmware/lib/lvgl/lv_conf.h");
    println!("cargo:rerun-if-changed=../firmware/src/pages/");
    println!("cargo:rerun-if-changed=mms/lvgl_driver.hh");
    println!("cargo:rerun-if-changed=mms/mms.cc");

    use glob::glob;

    //
    // Build lvgl library
    //
    let mut lvgl_src: Vec<String> = Vec::new();
    for entry in glob("../firmware/lib/lvgl/lvgl/src/**/*.c").expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            lvgl_src.push(format!("{}", f_name));
        }
    }
    lvgl_src.push(String::from("mms/stubs/hal_tick.c"));
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(false)
        .files(lvgl_src.iter())
        .include("mms/stubs")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl")
        .flag("-Wno-deprecated-anon-enum-enum-conversion");
    build.compile("lvgl");

    //
    // Build mms app
    //
    let mut src: Vec<String> = Vec::new();
    src.push(String::from("mms/mms.cc"));
    src.push(String::from("mms/stubs/hal_tick.c"));
    src.push(String::from("../firmware/src/patchlist.cc"));
    src.push(String::from("../firmware/src/pages/page_manager.cc"));
    src.push(String::from(
        "../firmware/src/pages/gui-guider/setup_scr_Main_Example.c",
    ));
    src.push(String::from(
        "../firmware/src/pages/gui-guider/setup_scr_symbol_sketches.c",
    ));
    src.push(String::from("../shared/util/math_tables.cc"));
    src.push(String::from("../shared/axoloti-wrapper/axoloti_math.cpp"));

    for entry in glob("../shared/CoreModules/*.cpp").expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            src.push(format!("{}", f_name));
        }
    }
    //fonts
    for entry in glob("../firmware/src/pages/fonts/*.c").expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            src.push(format!("{}", f_name));
        }
    }

    println!("cargo:rerun-rustc-link-lib=lvgl");
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(true)
        .files(src.iter())
        .flag("--includestubs/sys/alloc_buffer.hh")
        .include("mms")
        .include("mms/stubs")
        .include("../shared")
        .include("../shared/util")
        .include("../shared/patch")
        .include("../firmware/src")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl/src/lv_font")
        .flag("-DSIMULATOR")
        .flag("-std=c++2a")
        .flag("-Wno-unused-parameter");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

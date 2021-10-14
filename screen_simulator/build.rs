fn add_glob_files(globpath: &str, path_vec: &mut Vec<String>) {
    use glob::glob;
    for entry in glob(globpath).expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            path_vec.push(format!("{}", f_name));
        }
    }
}

fn main() {
    println!("cargo:rerun-if-changed=../firmware/lib/lvgl/lv_conf.h");
    println!("cargo:rerun-if-changed=../firmware/src/pages/");
    println!("cargo:rerun-if-changed=mms/lvgl_driver.hh");
    println!("cargo:rerun-if-changed=mms/mms.cc");
    //println!("cargo:rustc-env=RANLIB=ranlib"); //doesn't work, the idea is to suppress ranlib
    //warnings by setting ranlib to be a script that runs `ranlib -no_warning_for_no_symbols`

    //
    // Build lvgl library
    //
    let mut lvgl_src: Vec<String> = Vec::new();
    add_glob_files("../firmware/lib/lvgl/lvgl/src/**/*.c", &mut lvgl_src);
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
    src.push(String::from("../shared/util/math_tables.cc"));
    src.push(String::from("../shared/axoloti-wrapper/axoloti_math.cpp"));
    add_glob_files("../shared/CoreModules/*.cpp", &mut src);
    add_glob_files("../firmware/src/pages/fonts/*.c", &mut src);
    add_glob_files("../firmware/src/pages/gui-guider/*.c", &mut src);

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

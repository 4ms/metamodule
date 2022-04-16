fn main() {
    println!("cargo:rerun-if-changed=../firmware/lib/lvgl/lv_conf.h");
    println!("cargo:rerun-if-changed=../firmware/src/pages/");
    println!("cargo:rerun-if-changed=../firmware/src/pages/images");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/patch_selector.hh");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/module_view.hh");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/page_manager.cc");
    println!("cargo:rerun-if-changed=../firmware/src/pages/gui-guider");
    println!("cargo:rerun-if-changed=../firmware/src/patchlist.cc");
    println!("cargo:rerun-if-changed=mms/lvgl_driver.hh");
    println!("cargo:rerun-if-changed=mms/mms.cc");
    //println!("cargo:rustc-env=RANLIB=ranlib"); //doesn't work, the idea is to suppress ranlib
    //warnings by setting ranlib to be a script that runs `ranlib -no_warning_for_no_symbols`

    //
    // Build lvgl + display library
    //
    let mut lvgl_src: Vec<String> = Vec::new();
    add_glob_files("../firmware/lib/lvgl/lvgl/src/**/*.c", &mut lvgl_src);
    add_glob_files("../firmware/src/pages/images/*.c", &mut lvgl_src);
    add_glob_files("../firmware/src/pages/images/ui/*.c", &mut lvgl_src);
    add_glob_files("../firmware/src/pages/images/components/*.c", &mut lvgl_src);
    add_glob_files("../firmware/src/pages/fonts/*.c", &mut lvgl_src);
    add_glob_files("../firmware/src/pages/gui-guider/*.c", &mut lvgl_src);
    lvgl_src.push(String::from("mms/stubs/hal_tick.c"));

    let mut builder = cc::Build::new();
    let build = builder
        .cpp(false)
        .files(lvgl_src.iter())
        .include("mms/stubs")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl")
        .flag("-Wno-deprecated-anon-enum-enum-conversion")
        .flag("-Wno-unused-but-set-variable");
    build.compile("lvgl");

    //
    // Build mms app
    //
    let mut src: Vec<String> = Vec::new();
    src.push(String::from("mms/mms.cc"));
    src.push(String::from("mms/stubs/hal_tick.c"));
    src.push(String::from("../firmware/src/patchlist.cc"));
    src.push(String::from("../firmware/src/pages/page_manager.cc"));
    src.push(String::from("../shared/cpputil/util/math_tables.cc"));
    src.push(String::from("../shared/axoloti-wrapper/axoloti_math.cpp"));
    add_glob_files("../shared/CoreModules/*.cc", &mut src);


    // Patch convert
    src.push(String::from("../shared/patch_convert/ryml/ryml_serial.cc"));
    src.push(String::from("../shared/patch_convert/yaml_to_patch.cc"));
    add_glob_files("../shared/patch_convert/ryml/rapidyaml/src/c4/yml/*.cpp", &mut src);
    add_glob_files("../shared/patch_convert/ryml/rapidyaml/ext/c4core/src/c4/*.cpp", &mut src);

    println!("cargo:rerun-rustc-link-lib=lvgl");
    let mut builder = cc::Build::new();
    let build = builder
        .cpp(true)
        .files(src.iter())
        .flag("--includestubs/sys/alloc_buffer.hh")
        .include("mms")
        .include("mms/stubs")
        .include("../shared/etl/include")
        .include("../shared")
        .include("../shared/cpputil")
        .include("../shared")
        .include("../shared/patch")
        .include("../shared/patch_convert")
        .include("../shared/patch_convert/ryml/rapidyaml/src")
        .include("../shared/patch_convert/ryml/rapidyaml/ext/c4core/src")
        .include("../firmware/src")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl/src/lv_font")
        .flag("-DSIMULATOR")
        .flag("-std=c++20")
        .flag("-Wno-unused-parameter")
        .flag("-Wno-unused-but-set-variable")
        .flag("-Wno-unused-const-variable")
        .flag("-Wno-deprecated-anon-enum-enum-conversion");
    build.compile("metamodulescreen");

    // CXXFLAGS=-std=c++11 cargo build
}

fn add_glob_files(globpath: &str, path_vec: &mut Vec<String>) {
    use glob::glob;
    for entry in glob(globpath).expect("Bad glob pattern") {
        if let Ok(path) = entry {
            let f_name = String::from(path.to_string_lossy());
            path_vec.push(format!("{}", f_name));
        }
    }
}

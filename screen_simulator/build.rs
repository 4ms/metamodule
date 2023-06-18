fn main() {
    let use_fewer_modules = true;

    println!("cargo:rerun-if-changed=../firmware/lib/lvgl/lv_conf.h");
    println!("cargo:rerun-if-changed=../firmware/src/pages/");
    println!("cargo:rerun-if-changed=../firmware/src/pages/images");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/patch_selector.hh");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/module_view.hh");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/patch_view.hh");
    println!("cargo:rerun-if-chnaged=../firmware/src/pages/page_manager.cc");
    println!("cargo:rerun-if-changed=../firmware/src/pages/gui-guider");
    println!("cargo:rerun-if-changed=../firmware/src/patchlist.cc");
    println!("cargo:rerun-if-changed=mms/lvgl_driver.hh");
    println!("cargo:rerun-if-changed=mms/mms.cc");
    println!("cargo:rerun-if-changed=mms/stubs/patch_storage_proxy.hh");
    //println!("cargo:rustc-env=RANLIB=ranlib"); //doesn't work, the idea is to suppress ranlib
    //warnings by setting ranlib to be a script that runs `ranlib -no_warning_for_no_symbols`

    //
    // Build lvgl + display library
    //
    let mut lvgl_src: Vec<String> = Vec::new();
    add_glob_files("../firmware/lib/lvgl/lvgl/src/**/*.c", &mut lvgl_src);
    lvgl_src.push(String::from("mms/stubs/hal_tick.c"));
    lvgl_src.push(String::from("../firmware/src/pages/slsexport/ui.c"));
    lvgl_src.push(String::from("../firmware/src/pages/slsexport/ui_helpers.c"));
    add_glob_files("../firmware/src/pages/slsexport/ui_font_*.c", &mut lvgl_src);

    let fontdir: String = "../firmware/src/pages/fonts".to_owned();
    lvgl_src.push(format!("{}{}", fontdir, "/MuseoSansRounded_500_12.c",));
    lvgl_src.push(format!("{}{}", fontdir, "/MuseoSansRounded_700_12.c"));
    lvgl_src.push(format!("{}{}", fontdir, "/MuseoSansRounded_700_14.c"));
    lvgl_src.push(format!("{}{}", fontdir, "/MuseoSansRounded_700_16.c"));
    lvgl_src.push(format!("{}{}", fontdir, "/MuseoSansRounded_700_18.c"));

    add_glob_files("../firmware/src/pages/images/components/*.c", &mut lvgl_src);

    if use_fewer_modules {
        let artdir: String = "../firmware/src/pages/images/modules".to_owned();
        lvgl_src.push(format!("{}{}", artdir, "/Djembe_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Djembe_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/EnOsc_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/EnOsc_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Freeverb_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Freeverb_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/HPF_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/HPF_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/InfOsc_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/InfOsc_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/KPLS_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/KPLS_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/MultiLFO_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/MultiLFO_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/PEG_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/PEG_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/PitchShift_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/PitchShift_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/SMR_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/SMR_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Seq8_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Seq8_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/StMix_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/StMix_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/DualAtenuverter_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/DualAtenuverter_artwork_240.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Braids_artwork_120.c"));
        lvgl_src.push(format!("{}{}", artdir, "/Braids_artwork_240.c"));
    } else {
        add_glob_files("../firmware/src/pages/images/modules/*.c", &mut lvgl_src);
    }

    let mut builder = cc::Build::new();
    let build = builder
        .cpp(false)
        .files(lvgl_src.iter())
        .include("mms/stubs")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl")
        .include("../src/pages/slsexport")
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

    if use_fewer_modules {
        src.push(String::from("../shared/CoreModules/modules/DjembeCore.cc"));
        src.push(String::from("../shared/CoreModules/modules/StMixCore.cc"));
        src.push(String::from("../shared/CoreModules/modules/PEGCore.cc"));
        src.push(String::from("../shared/CoreModules/modules/SMRCore.cc"));
        src.push(String::from(
            "../shared/CoreModules/modules/MultiLFOCore.cc",
        ));
        src.push(String::from(
            "../shared/CoreModules/modules/PitchShiftCore.cc",
        ));
        src.push(String::from("../shared/CoreModules/modules/HPFCore.cc"));
        src.push(String::from("../shared/CoreModules/modules/InfOscCore.cc"));
        src.push(String::from(
            "../shared/CoreModules/modules/FreeverbCore.cc",
        ));
        src.push(String::from("../shared/CoreModules/modules/KPLSCore.cc"));
        src.push(String::from("../shared/CoreModules/modules/Seq8Core.cc"));
        src.push(String::from("../shared/CoreModules/modules/EnOscCore.cc"));
        src.push(String::from(
            "../shared/CoreModules/Befaco/DualAtenuverterCore.cc",
        ));
        src.push(String::from(
            "../shared/CoreModules/AudibleInstruments/BraidsCore.cc",
        ));
        src.push(String::from(
            "../shared/CoreModules/meta-module-hub/panel_medium.cc",
        ));
    } else {
        add_glob_files("../shared/CoreModules/*.cc", &mut src);
    }
    add_glob_files("../shared/CoreModules/modules/*.cc", &mut src);
    add_glob_files("../shared/CoreModules/Befaco/*.cc", &mut src);
    add_glob_files("../shared/CoreModules/AudibleInstruments/*.cc", &mut src);
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/stmlib/utils/random.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/stmlib/dsp/atan.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/stmlib/dsp/units.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/braids/analog_oscillator.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/braids/digital_oscillator.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/braids/macro_oscillator.cc",
    ));
    src.push(String::from(
        "../shared/CoreModules/AudibleInstruments/braids/resources.cc",
    ));

    src.push(String::from("../shared/CoreModules/modules/enosc/data.cc"));
    src.push(String::from(
        "../shared/CoreModules/modules/enosc/dynamic_data.cc",
    ));

    // Patch convert
    src.push(String::from("../shared/patch_convert/ryml/ryml_serial.cc"));
    src.push(String::from("../shared/patch_convert/yaml_to_patch.cc"));
    add_glob_files(
        "../shared/patch_convert/ryml/rapidyaml/src/c4/yml/*.cpp",
        &mut src,
    );
    add_glob_files(
        "../shared/patch_convert/ryml/rapidyaml/ext/c4core/src/c4/*.cpp",
        &mut src,
    );

    println!("cargo:rerun-rustc-link-lib=lvgl");
    let mut builder = cc::Build::new();
    let mut build = builder
        .cpp(true)
        .files(src.iter())
        .flag("--includestubs/sys/alloc_buffer.hh")
        .include("mms")
        .include("mms/stubs")
        .include("../shared")
        .include("../shared/cpputil")
        .include("../shared")
        .include("../shared/patch")
        .include("../shared/patch_convert")
        .include("../shared/patch_convert/ryml/rapidyaml/src")
        .include("../shared/patch_convert/ryml/rapidyaml/ext/c4core/src")
        .include("../shared/CoreModules")
        .include("../shared/CoreModules/modules")
        .include("../shared/CoreModules/AudibleInstruments")
        .include("../shared/CoreModules/Befaco")
        .include("../firmware/src")
        .include("../firmware/lib/lvgl")
        .include("../firmware/lib/lvgl/lvgl/src/lv_font")
        .flag("-DSIMULATOR")
        .flag("-std=c++20")
        .flag("-Wno-unused-parameter")
        .flag("-Wno-unused-but-set-variable")
        .flag("-Wno-unused-const-variable")
        .flag("-Wno-deprecated-anon-enum-enum-conversion");
    if use_fewer_modules {
        build = build.flag("-DUSE_FEWER_MODULES");
    }
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

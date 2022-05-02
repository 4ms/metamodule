extern crate libc;
extern crate timer;

extern crate chrono;

use minifb::{Key, ScaleMode, Window, WindowOptions, KeyRepeat};


const WIDTH: usize = 320;
const HEIGHT: usize = 240;

#[link(name = "metamodulescreen")]
extern "C" {
    fn init_screen() -> bool;
    fn get_pixel(x: u16, y: u16) -> u16;
    fn update_ui() -> ();
    fn rotary_back() -> ();
    fn rotary_fwd() -> ();
    fn rotary_push_back() -> ();
    fn rotary_push_fwd() -> ();
    fn rotary_press() -> ();
    fn rotary_release() -> ();
    fn button_press() -> ();
    fn button_release() -> ();
    fn lv_timer_handler() -> ();
    fn fake_HAL_IncTick() -> ();
    fn set_knob(knobid : u32, val: f32) -> ();
}

fn get_ext_color(x: usize, y: usize) -> u32 {
    let rgb565 = unsafe { get_pixel(x as u16, y as u16) };
    let r_ = ((rgb565 & 0xf800) >> 8) as u32;
    let g_ = ((rgb565 & 0x07e0) >> 3) as u32;
    let b_ = ((rgb565 & 0x001f) << 3) as u32;

    (r_ << 16) | (g_ << 8) | b_
}

trait Control {
    fn new() -> Self;
    fn inc(&mut self) -> f32;
    fn dec(&mut self) -> f32;
}

struct Knob {
    val : f32,
}

impl Default for Knob {
    fn default() -> Self {
        Knob{val: 0.0}
    }
}

impl Control for Knob {
    fn new() -> Knob {
        Knob{val: 0.5}
    }
    fn inc(&mut self) -> f32 {
        self.val = self.val + 0.1;
        self.val
    }
    fn dec(&mut self) -> f32 {
        self.val = self.val - 0.1;
        self.val
    }
}

fn main() {
    println!("Starting...");
    let loaded_ok;
    unsafe {
        loaded_ok = init_screen();
    };
    if !loaded_ok {
        panic!("Cannot load patch");
    }

    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];

    let wo = WindowOptions {
        borderless: false,
        title: true,
        resize: true,
        scale: minifb::Scale::X1,
        scale_mode: ScaleMode::AspectRatioStretch,
        topmost: false,
        transparency: false,
        none: false,
    };

    let mut window = Window::new("MetaModule", WIDTH, HEIGHT, wo).unwrap_or_else(|e| {
        panic!("{}", e);
    });

    let lv_timer = timer::Timer::new();
    let _guard = lv_timer.schedule_repeating(chrono::Duration::milliseconds(3), move || {
        unsafe {
            lv_timer_handler();
        };
    });

    let inc_timer = timer::Timer::new();
    let _guard = inc_timer.schedule_repeating(chrono::Duration::milliseconds(1), move || {
        unsafe {
            fake_HAL_IncTick();
        };
    });


    let mut knobs : [Knob; 12] = Default::default();

    //33Hz refresh rate (matches hardware)
    window.limit_update_rate(Some(std::time::Duration::from_micros(33300)));

    while window.is_open() && !window.is_key_pressed(Key::Escape, KeyRepeat::No) {

        window.get_keys_pressed(KeyRepeat::No).map(|keys| {
            for t in keys {
                match t {
                    Key::L => unsafe { rotary_fwd(); }
                    Key::H => unsafe { rotary_back(); }
                    Key::J => unsafe { rotary_press(); }
                    Key::K => unsafe { button_press(); }

                    Key::Right => unsafe { rotary_fwd(); }
                    Key::Left => unsafe { rotary_back(); }
                    Key::Down => unsafe { rotary_press(); }

                    Key::Comma => unsafe { rotary_push_back(); }
                    Key::Period => unsafe { rotary_push_fwd(); }

                    Key::Key1 => unsafe { set_knob(0, knobs[0].dec());println!("{}", knobs[0].val); }
                    Key::F1 => unsafe { set_knob(0, knobs[0].inc()); println!("{}", knobs[0].val); }

                    Key::Key2 => unsafe { set_knob(1, knobs[1].dec()); }
                    Key::F2 => unsafe { set_knob(1, knobs[1].inc()); }

                    Key::Key3 => unsafe { set_knob(2, knobs[2].dec()); }
                    Key::F3 => unsafe { set_knob(2, knobs[2].inc()); }

                    Key::Key4 => unsafe { set_knob(3, knobs[3].dec()); }
                    Key::F4 => unsafe { set_knob(3, knobs[3].inc()); }

                    Key::Key5 => unsafe { set_knob(4, knobs[4].dec()); }
                    Key::F5 => unsafe { set_knob(4, knobs[4].inc()); }

                    Key::Key6 => unsafe { set_knob(5, knobs[5].dec()); }
                    Key::F6 => unsafe { set_knob(5, knobs[5].inc()); }

                    Key::Key7 => unsafe { set_knob(6, knobs[6].dec()); }
                    Key::F7 => unsafe { set_knob(6, knobs[6].inc()); }

                    Key::Key8 => unsafe { set_knob(7, knobs[7].dec()); }
                    Key::F8 => unsafe { set_knob(7, knobs[7].inc()); }

                    Key::Key9 => unsafe { set_knob(8, knobs[8].dec()); }
                    Key::F9 => unsafe { set_knob(8, knobs[8].inc()); }

                    Key::Key0 => unsafe { set_knob(9, knobs[9].dec()); }
                    Key::F10 => unsafe { set_knob(9, knobs[9].inc()); }

                    Key::Minus => unsafe { set_knob(10, knobs[10].dec()); }
                    Key::F11 => unsafe { set_knob(10, knobs[10].inc()); }

                    Key::Equal=> unsafe { set_knob(11, knobs[11].dec()); }
                    Key::F12 => unsafe { set_knob(11, knobs[11].inc()); }
                    _ => (),
                }
            }
        });

        window.get_keys_released().map(|keys| {
            for t in keys {
                match t {
                    Key::J => unsafe { rotary_release(); }
                    Key::K => unsafe { button_release(); }

                    Key::Down => unsafe { rotary_release(); }
                    _ => (),
                }
            }
        });

        unsafe { update_ui() };

        let mut x: usize = 0;
        let mut y: usize = 0;
        for i in buffer.iter_mut() {
            *i = get_ext_color(x, y); //0..319, 0..239
            x = x + 1;
            if x == WIDTH {
                x = 0;
                y = y + 1;
            }
        }

        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}

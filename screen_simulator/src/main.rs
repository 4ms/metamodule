extern crate libc;
use minifb::{Key, Window, WindowOptions};

const WIDTH: usize = 320;
const HEIGHT: usize = 240;

#[link(name = "metamodulescreen")]
extern "C" {
    fn init_screen() -> bool;
    fn get_pixel(x: u16, y: u16) -> u16;
    fn refresh() -> ();
    fn rotary_back() -> ();
    fn rotary_fwd() -> ();
    fn rotary_push_back() -> ();
    fn rotary_push_fwd() -> ();
    fn rotary_press() -> ();
    fn rotary_release() -> ();
}

fn get_ext_color(x: usize, y: usize) -> u32 {
    let rgb565 = unsafe { get_pixel(x as u16, y as u16) };
    let r_ = ((rgb565 & 0xf800) >> 8) as u32;
    let g_ = ((rgb565 & 0x07e0) >> 3) as u32;
    let b_ = ((rgb565 & 0x001f) << 3) as u32;

    (r_ << 16) | (g_ << 8) | b_
}

struct KeyHandler<'a> {
    key: Key,
    is_pressed: bool,
    action: &'a dyn Fn() -> (),
}

fn main() {
    let loaded_ok;
    unsafe {
        loaded_ok = init_screen();
    };
    if !loaded_ok {
        panic!("Cannot load patch");
    }

    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];

    let mut window = Window::new("MetaModule", WIDTH, HEIGHT, WindowOptions::default())
        .unwrap_or_else(|e| {
            panic!("{}", e);
        });

    let mut keys: [KeyHandler; 6] = [
        KeyHandler {
            key: Key::Right,
            is_pressed: false,
            action: &|| unsafe { rotary_fwd() },
        },
        KeyHandler {
            key: Key::Left,
            is_pressed: false,
            action: &|| unsafe { rotary_back() },
        },
        KeyHandler {
            key: Key::Down,
            is_pressed: false,
            action: &|| unsafe { rotary_press() },
        },
        KeyHandler {
            key: Key::Up,
            is_pressed: false,
            action: &|| unsafe { rotary_release() },
        },
        KeyHandler {
            key: Key::Comma,
            is_pressed: false,
            action: &|| unsafe { rotary_push_back() },
        },
        KeyHandler {
            key: Key::Period,
            is_pressed: false,
            action: &|| unsafe { rotary_push_fwd() },
        },
    ];

    //33Hz refresh rate (matches hardware)
    window.limit_update_rate(Some(std::time::Duration::from_micros(33300)));

    while window.is_open() && !window.is_key_down(Key::Escape) {
        for k in keys.iter_mut() {
            if window.is_key_down(k.key) {
                if !k.is_pressed {
                    (k.action)();
                }
                k.is_pressed = true;
            } else {
                k.is_pressed = false;
            }
        }

        unsafe { refresh() };

        let mut x: usize = 0;
        let mut y: usize = 0;
        for i in buffer.iter_mut() {
            *i = get_ext_color(x, y);
            x = x + 1;
            if x == WIDTH {
                x = 0;
                y = y + 1;
            }
        }

        window.update_with_buffer(&buffer, WIDTH, HEIGHT).unwrap();
    }
}

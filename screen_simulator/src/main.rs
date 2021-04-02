extern crate libc;
use minifb::{Key, Window, WindowOptions};

const WIDTH: usize = 240;
const HEIGHT: usize = 240;

#[link(name = "metamodulescreen")]
extern "C" {
    fn get_pixel(x: u16, y: u16) -> u16;
}

fn get_ext_color(x: usize, y: usize) -> u32 {
    let rgb565 = unsafe { get_pixel(x as u16, y as u16) };
    let r_ = ((rgb565 & 0xf800) >> 8) as u32;
    let g_ = ((rgb565 & 0x07e0) >> 3) as u32;
    let b_ = ((rgb565 & 0x001f) << 3) as u32;

    (r_ << 16) | (g_ << 8) | b_
}

fn main() {
    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];

    let mut window = Window::new("Test window", WIDTH, HEIGHT, WindowOptions::default())
        .unwrap_or_else(|e| {
            panic!("{}", e);
        });

    window.limit_update_rate(Some(std::time::Duration::from_micros(16600)));
    while window.is_open() && !window.is_key_down(Key::Escape) {
        // let mut color: u32 = 0;
        // if window.is_key_down(Key::Space) {
        //     color = 0xff00ffee;
        // }

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

// use raqote::*;

// use minifb::{MouseMode, Scale, ScaleMode, Window, WindowOptions};

// fn main() {
//     let mut dt = DrawTarget::new(400, 400);

//     let mut pb = PathBuilder::new();
//     pb.move_to(100., 10.);
//     pb.cubic_to(150., 40., 175., 0., 200., 10.);
//     pb.quad_to(120., 100., 80., 200.);
//     pb.quad_to(150., 180., 300., 300.);
//     pb.close();
//     let path = pb.finish();

//     let gradient = Source::new_radial_gradient(
//         Gradient {
//             stops: vec![
//                 GradientStop {
//                     position: 0.2,
//                     color: Color::new(0xff, 0, 0xff, 0),
//                 },
//                 GradientStop {
//                     position: 0.8,
//                     color: Color::new(0xff, 0xff, 0xff, 0xff),
//                 },
//                 GradientStop {
//                     position: 1.,
//                     color: Color::new(0xff, 0xff, 0, 0xff),
//                 },
//             ],
//         },
//         Point::new(150., 150.),
//         128.,
//         Spread::Pad,
//     );
//     dt.fill(&path, &gradient, &DrawOptions::new());

//     let mut pb = PathBuilder::new();
//     pb.move_to(100., 100.);
//     pb.line_to(300., 300.);
//     pb.line_to(200., 300.);
//     let path = pb.finish();

//     dt.stroke(
//         &path,
//         &Source::Solid(SolidSource {
//             r: 0x0,
//             g: 0x0,
//             b: 0x80,
//             a: 0x80,
//         }),
//         &StrokeStyle {
//             cap: LineCap::Round,
//             join: LineJoin::Round,
//             width: 10.,
//             miter_limit: 2.,
//             dash_array: vec![10., 18.],
//             dash_offset: 16.,
//         },
//         &DrawOptions::new(),
//     );

//     dt.write_png("example.png");
// }

// use font_kit::family_name::FamilyName;
// use font_kit::properties::Properties;
// use font_kit::source::SystemSource;
// use minifb::{MouseMode, Scale, ScaleMode, Window, WindowOptions};
// use raqote::{
//     DrawOptions, DrawTarget, PathBuilder, Point, SolidSource, Source, StrokeStyle, Transform,
// };
// const WIDTH: usize = 400;
// const HEIGHT: usize = 400;

// fn main() {
//     let mut window = Window::new(
//         "Raqote",
//         WIDTH,
//         HEIGHT,
//         WindowOptions {
//             ..WindowOptions::default()
//         },
//     )
//     .unwrap();
//     let font = SystemSource::new()
//         .select_best_match(&[FamilyName::SansSerif], &Properties::new())
//         .unwrap()
//         .load()
//         .unwrap();

//     let size = window.get_size();
//     let mut dt = DrawTarget::new(size.0 as i32, size.1 as i32);
//     loop {
//         dt.clear(SolidSource::from_unpremultiplied_argb(
//             0xff, 0xff, 0xff, 0xff,
//         ));
//         let mut pb = PathBuilder::new();
//         if let Some(pos) = window.get_mouse_pos(MouseMode::Clamp) {
//             pb.rect(pos.0, pos.1, 100., 130.);
//             let path = pb.finish();
//             dt.fill(
//                 &path,
//                 &Source::Solid(SolidSource::from_unpremultiplied_argb(0xff, 0, 0xff, 0)),
//                 &DrawOptions::new(),
//             );

//             let pos_string = format!("{:?}", pos);
//             dt.draw_text(
//                 &font,
//                 36.,
//                 &pos_string,
//                 Point::new(0., 100.),
//                 &Source::Solid(SolidSource::from_unpremultiplied_argb(0xff, 0, 0, 0)),
//                 &DrawOptions::new(),
//             );

//             window
//                 .update_with_buffer(dt.get_data(), size.0, size.1)
//                 .unwrap();
//         }
//     }
// }

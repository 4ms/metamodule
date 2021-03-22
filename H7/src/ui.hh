#pragma once
#include "Adafruit_GFX_Library/Fonts/FreeMono12pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSans9pt7b.h"
#include "Adafruit_GFX_Library/Fonts/FreeSansBold18pt7b.h"
#include "audio.hh"
#include "bouncing_ball.hh"
#include "conf/hsem_conf.hh"
#include "debug.hh"
#include "drivers/hsem.hh"
#include "drivers/i2c.hh"
#include "drivers/interrupt.hh"
#include "drivers/memory_transfer.hh"
#include "leds.hh"
#include "m7/hsem_handler.hh"
#include "params.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"
#include "sys/alloc_buffer.hh"
#include "sys/mem_usage.hh"

constexpr bool ENABLE_BOUNCING_BALL_DEMO = false;

namespace MetaModule
{
template<unsigned AnimationUpdateRate = 100>
class Ui {
public:
	PatchList &patch_list;
	PatchPlayer &player;
	LedFrame<AnimationUpdateRate> &leds;
	Params &params;
	ScreenFrameBuffer screen;

public:
	static constexpr uint32_t Hz_i = AnimationUpdateRate / led_update_freq_Hz;
	static constexpr uint32_t Hz = static_cast<float>(Hz_i);

	Ui(PatchList &pl,
	   PatchPlayer &pp,
	   LedFrame<AnimationUpdateRate> &l,
	   Params &p,
	   MMScreenConf::FrameBufferT &screenbuf)
		: patch_list{pl}
		, player{pp}
		, leds{l}
		, params{p}
		, screen{screenbuf}
	{}

	Color bgcolor = Colors::pink;
	Color patch_fgcolor = Colors::blue.blend(Colors::black, 0.5f);
	Color load_fgcolor = Colors::blue;
	Color pots_fgcolor = Colors::black;

	BouncingBall balls[3] = {
		{60, {220, 30}, {-1, 1}, {239, 239}},
		{50, {20, 10}, {2, -1}, {239, 239}},
		{40, {10, 220}, {2, 3}, {239, 239}},
	};

	Color ball_colors[3] = {
		Colors::red,
		Colors::black,
		Colors::orange,
	};

	void start()
	{
		screen.init();
		screen.fill(bgcolor);

		leds.but[0].set_background(Colors::grey);
		leds.but[1].set_background(Colors::grey);
		leds.clockLED.set_background(Colors::blue.blend(Colors::black, 0.5f));
		leds.rotaryLED.set_background(Colors::green);

		// Todo: led animation rate depends on I2C rate... not easy to set  maybe we can have it self-calibrate against
		// the SysTick?
		// Otherwise we can use this: but we'd have to make it thread-safe we could just have
		// update_animation() just update the TriOsc and fade (but not write actual color to the framebuffer)
		// led_update_task.init(led_update_animation_task_conf, [this]() { leds.update_animation(); });
		// led_update_task.start();
		HWSemaphoreCoreHandler::register_channel_ISR<LEDFrameBufLock>([&]() { update_led_states(); });
		HWSemaphore<LEDFrameBufLock>::enable_channel_ISR();

		screen_draw_task.init(
			{
				.TIMx = TIM5,
				.period_ns = 1000000000 / 33, // =  33Hz
				.priority1 = 3,
				.priority2 = 3,

			},
			[&]() { refresh_screen(); });
		screen_draw_task.start();
	}

	void refresh_screen()
	{
		Debug::Pin3::high();
		HWSemaphore<ScreenFrameBuf1Lock>::lock();
		screen.fill(bgcolor);
		if constexpr (ENABLE_BOUNCING_BALL_DEMO)
			draw_bouncing_ball();
		draw_audio_load();
		draw_pot_values();
		draw_patch_name();
		draw_jack_senses();
		draw_knob_map();
		screen.flush_cache();
		Debug::Pin3::low();
		HWSemaphore<ScreenFrameBuf1Lock>::unlock();
	}

private:
	Timekeeper screen_draw_task;

	void update_led_states()
	{
		if (params.buttons[0].is_pressed())
			leds.but[0].set_background(Colors::red);
		else
			leds.but[0].set_background(Colors::green);

		if (params.buttons[1].is_pressed())
			leds.but[1].set_background(Colors::blue);
		else
			leds.but[1].set_background(Colors::orange);

		if (params.rotary_button.is_pressed())
			leds.rotaryLED.set_background(Colors::blue);
		else
			leds.rotaryLED.set_background(Colors::green);

		leds.rotaryLED.breathe(Colors::magenta, 1);
		leds.clockLED.breathe(Colors::green, 0.75f);
		leds.but[0].breathe(Colors::blue, 0.5f);
		leds.but[1].breathe(Colors::white, 0.1f);

		leds.update_animation();
	}

	void draw_knob_map()
	{
		screen.setFont(&FreeSans9pt7b);
		screen.setTextSize(1);
		screen.setTextWrap(false);
		const uint16_t line_height = 16;
		const char knob_name[8][2] = {"A", "B", "C", "D", "a", "b", "c", "d"};
		auto &cur_patch = patch_list.cur_patch();

		for (int i = 0; i < cur_patch.num_mapped_knobs; i++) {
			auto &knob = cur_patch.mapped_knobs[i];

			screen.setTextColor(Colors::black.Rgb565());
			screen.setCursor(2, 50 + line_height * i);
			screen.print(knob_name[knob.panel_knob_id]);
			screen.print(" = ");

			screen.setTextColor(Colors::white.blend(Colors::black, 0.25f).Rgb565());
			screen.print(ModuleFactory::getModuleTypeName(cur_patch.modules_used[knob.module_id]));
			screen.print(" #");
			screen.print(knob.module_id);

			screen.setTextColor(Colors::blue.blend(Colors::black, 0.5f).Rgb565());
			if (player.is_loaded) {
				screen.print(": ");
				screen.print(player.modules[knob.module_id]->knob_name(knob.param_id));
			}
		}
	}

	void draw_patch_name()
	{
		screen.setFont(&FreeSansBold18pt7b);
		screen.setTextColor(patch_fgcolor.Rgb565());
		screen.setTextSize(1);
		screen.setCursor(2, 30);
		screen.setTextWrap(false);
		screen.print(patch_list.cur_patch().patch_name);
	}

	void draw_audio_load()
	{
		screen.setTextColor(load_fgcolor.Rgb565());
		screen.setTextSize(2);
		screen.setFont(NULL);
		screen.setCursor(200, 225);
		screen.print(patch_list.audio_load, 10);
		screen.print("% ");
		screen.setTextSize(1);
		screen.setCursor(175, 224);
		screen.print(get_heap_size() / 1024, 10);
		screen.print("kb ");
		screen.setCursor(175, 232);
		screen.print(BigAlloc<Ui>::get_memory_usage() / 1024, 10);
		screen.print("kb   ");
	}

	void draw_pot_values()
	{
		screen.setTextColor(pots_fgcolor.Rgb565());
		screen.setTextSize(1);
		screen.setFont(NULL);
		int y = 214;
		const int box_height = 15;
		const int box_width = 30;
		for (int i = 0; i < 12; i++) {
			screen.setCursor((i & 0b111) * box_width + 3, y);
			if (i >= 8)
				screen.print((int16_t)(params.cvjacks[i - 8] * 100));
			else
				screen.print((int16_t)(params.knobs[i] * 100));
			screen.print(" ");
			if (i == 7)
				y += box_height;
		}
	}

	void draw_jack_senses()
	{
		screen.setTextColor(Colors::white.Rgb565());
		screen.setTextSize(1);
		screen.setFont(NULL);

		const uint16_t yoffset = 180;
		const uint16_t box_height = 15;
		const uint16_t box_width = 240 / 8;
		const float box_alpha = 0.85f;

		const unsigned pin_order[15] = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 4, 5, 14};
		const char names[15][5] = {"CVA",
								   "CVB",
								   "CVC",
								   "CVD",
								   "Lin",
								   "Rin",
								   "Lout",
								   "Rout",
								   "Gt1",
								   "Gt2",
								   "CkIn",
								   "CkO",
								   "CVO1",
								   "CVO2",
								   "Pat"};
		for (unsigned i = 0; i < 15; i++) {
			auto pin = pin_order[i];
			bool plugged = params.jack_senses & (1 << pin);
			bool works = (pin != 4 && pin != 5 && pin != 8 && pin != 9 && pin != 13);
			uint16_t xpos = (i & 0b0111) * box_width;
			uint16_t ypos = i > 7 ? yoffset + box_height : yoffset;
			auto color = works ? (plugged ? Colors::yellow : Colors::grey) : Colors::black;
			screen.blendRect(xpos, ypos, box_width, box_height, color.Rgb565(), box_alpha);
			screen.setCursor(xpos + 3, ypos + 4);
			screen.print(names[i]);
		}
	}

	void draw_bouncing_ball()
	{
		int i = 0;
		for (auto &ball : balls) {
			ball.update();
			auto pos = ball.get_pos();
			screen.fillCircle(pos.x, pos.y, ball.get_radius(), ball_colors[i].Rgb565());
			i++;
		}
	}

	void draw_test_squares()
	{
		// Should see a 1-pixel border around the 4-square, and a 1-pixel gap between squares
		screen.fillRect(0, 0, 44, 44, Colors::purple.Rgb565());
		screen.fillRect(1, 1, 20, 20, Colors::red.Rgb565());
		screen.fillRect(1, 23, 20, 20, Colors::green.Rgb565());
		screen.fillRect(23, 1, 20, 20, Colors::orange.Rgb565());
		screen.fillRect(23, 23, 20, 20, Colors::grey.Rgb565());

		screen.fillRect(196, 196, 44, 44, Colors::white.Rgb565());
		screen.fillRect(219, 219, 20, 20, Colors::yellow.Rgb565());
		screen.fillRect(197, 219, 20, 20, Colors::purple.Rgb565());
		screen.fillRect(197, 197, 20, 20, Colors::pink.Rgb565());
		screen.fillRect(219, 197, 20, 20, Colors::cyan.Rgb565());
	}
};
} // namespace MetaModule

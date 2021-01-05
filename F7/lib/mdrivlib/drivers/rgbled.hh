#pragma once
#include "colors.hh"
#include "oscs.hh"

//MixedRgbLed: each color element can have a different
//LED driver (e.g. PWM, DAC, external chip)
//Todo: use concepts to ensure LedT all have .set();
template<typename RLedT, typename GLedT, typename BLedT>
struct MixedRgbLed {

	MixedRgbLed(RLedT r_LED, GLedT g_LED, BLedT b_LED)
		: r_(r_LED)
		, g_(g_LED)
		, b_(b_LED)
	{
	}

	void set_background(Color const &col)
	{
		background_color_ = col;
	}
	void blend_background(Color const col)
	{
		background_color_ = background_color_.blend(col);
	}
	void add_background(Color const col)
	{
		background_color_ = background_color_ + col;
	}
	//void set_solid(Color const &col) { solid_color_ = col; }

	void flash(Color const &c, uint32_t const flash_freq = 100)
	{
		flash_color_ = c;
		flash_phase_ = 0xFFFFFFFF;
		flash_freq_ = flash_freq; // divided by update_rate?
	}

	// freq in secs
	void set_glow(Color const &c, uint32_t const freq = 0x00FFFFFF)
	{
		glow_color_ = c;
		fader_.set_frequency(freq); //divided by update_rate?
	}

	constexpr void set_color(Color const &col) const
	{
		r_.set(col.red());
		g_.set(col.green());
		b_.set(col.blue());
	}
	void set_color(Color const &col, uint8_t const brightness) const
	{
		r_.set((col.red() * brightness) >> 8);
		g_.set((col.green() * brightness) >> 8);
		b_.set((col.blue() * brightness) >> 8);
	}
	void set_color(Color const &col, float const brightness) const
	{
		r_.set(col.red() * brightness);
		g_.set(col.green() * brightness);
		b_.set(col.blue() * brightness);
	}

	//Todo: don't waste cycles updating if nothing's changed
	void refresh()
	{
		Color c = background_color_;
		// if (solid_color_ != Colors::off) c = solid_color_;
		// c = c.blend(glow_color_, fader_.Process());
		// c = c.blend(flash_color_, flash_phase_);
		// c = c.adjust(color_cal_);
		set_color(c);
		if (flash_phase_ > flash_freq_)
			flash_phase_ -= flash_freq_;
		else
			flash_phase_ = 0;
	}

private:
	const RLedT r_;
	const GLedT g_;
	const BLedT b_;
	TriangleOscillator<89478> fader_;
	Color background_color_ = Colors::off;
	Color solid_color_ = Colors::off;
	Color flash_color_ = Colors::white;
	Color glow_color_ = Colors::red;
	uint32_t flash_freq_ = 100;
	uint32_t flash_phase_ = 0;
	//    Color::Adjustment& color_cal_;
};

//"Normal" RGB LED where each element has the same type of LED driver
template<typename LedType>
using RgbLed = MixedRgbLed<LedType, LedType, LedType>;


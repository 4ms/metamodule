#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

namespace MetaModule
{

// Moves modules around a grid of rows, one encoder click at a time.
// Units are the same as a patch's stored positions: x in HP, y in whole rows.
//
// Turning moves a module along its row: first it closes any gap, then it swaps with
// the neighbour it's touching, and at the end of a row it moves to the next/previous row.
// Moving onto a row where there are already modules pushes them rightwards to make space.
struct ModuleRearrange {
	struct Slot {
		uint16_t module_id{};
		int32_t x{};
		int32_t row{};
		int32_t width{};

		int32_t right() const {
			return x + width;
		}
	};

	static constexpr int32_t GapStepHP = 2;

	// canvas_width: where rows end, for closing gaps and moving between rows.
	// max_width, max_row: nothing may be moved or pushed past these
	ModuleRearrange(std::vector<Slot> slots,
					int32_t canvas_width,
					int32_t max_width,
					int32_t max_row = std::numeric_limits<int32_t>::max())
		: slots_{std::move(slots)}
		, max_width_{max_width}
		, max_row_{max_row} {
		width_ = canvas_width;
		for (auto const &s : slots_)
			width_ = std::max(width_, s.right());
	}

	std::vector<Slot> const &slots() const {
		return slots_;
	}

	int32_t canvas_width() const {
		return width_;
	}

	Slot const *find(uint16_t module_id) const {
		auto it = std::ranges::find(slots_, module_id, &Slot::module_id);
		return it == slots_.end() ? nullptr : &*it;
	}

	// dir > 0 moves right, dir < 0 moves left. Returns true if anything moved
	bool step_horiz(uint16_t module_id, int dir) {
		return try_move(module_id, [&](Slot &m) { dir > 0 ? step_right(m) : step_left(m); });
	}

	// dir > 0 moves down a row, dir < 0 moves up. Returns true if anything moved
	bool step_vert(uint16_t module_id, int dir) {
		return try_move(module_id, [&](Slot &m) {
			if (dir > 0) {
				// Moving down from the last row makes a new row, unless it would just leave an empty row behind
				if (m.row == last_row() && is_alone_on_row(m))
					return;
				m.row++;
			} else {
				if (m.row == 0)
					return;
				m.row--;
			}
			push_row(m);
		});
	}

private:
	std::vector<Slot> slots_;
	int32_t width_{};
	int32_t max_width_{};
	int32_t max_row_{};

	// Applies a move, undoing it if it pushed anything off the edge of the canvas
	template<typename F>
	bool try_move(uint16_t module_id, F &&move) {
		auto it = std::ranges::find(slots_, module_id, &Slot::module_id);
		if (it == slots_.end())
			return false;

		auto before = slots_;
		auto before_width = width_;

		move(*it);

		for (auto const &s : slots_)
			width_ = std::max(width_, s.right());

		if (width_ > max_width_ || last_row() > max_row_) {
			slots_ = std::move(before);
			width_ = before_width;
			return false;
		}

		return !std::ranges::equal(before, slots_, [](Slot const &a, Slot const &b) {
			return a.x == b.x && a.row == b.row;
		});
	}

	void step_right(Slot &m) {
		// Nearest module to the right on the same row
		Slot *next = nullptr;
		for (auto &o : slots_) {
			if (&o != &m && o.row == m.row && o.x >= m.right() && (!next || o.x < next->x))
				next = &o;
		}

		auto gap = (next ? next->x : width_) - m.right();

		if (gap > 0) {
			m.x += std::min(GapStepHP, gap);

		} else if (next) {
			// Trade places, keeping the pair in the same span
			next->x = m.x;
			m.x = next->right();

		} else {
			// Off the right end: start of the next row, or back to the top after the last row
			m.row = (m.row >= last_row()) ? 0 : m.row + 1;
			m.x = 0;
			push_row(m);
		}
	}

	void step_left(Slot &m) {
		// Nearest module to the left on the same row
		Slot *prev = nullptr;
		for (auto &o : slots_) {
			if (&o != &m && o.row == m.row && o.right() <= m.x && (!prev || o.x > prev->x))
				prev = &o;
		}

		auto gap = m.x - (prev ? prev->right() : 0);

		if (gap > 0) {
			m.x -= std::min(GapStepHP, gap);

		} else if (prev) {
			m.x = prev->x;
			prev->x = m.right();

		} else {
			// Off the left end: end of the previous row, or the last row if we were at the top
			m.row = (m.row == 0) ? last_row() : m.row - 1;

			int32_t row_end = 0;
			for (auto const &o : slots_) {
				if (&o != &m && o.row == m.row)
					row_end = std::max(row_end, o.right());
			}

			m.x = std::max(width_ - m.width, row_end);
		}
	}

	// Pushes anything on m's row that overlaps it, or overlaps a module pushed by it, rightwards
	void push_row(Slot const &m) {
		std::vector<Slot *> row;
		for (auto &o : slots_) {
			if (&o != &m && o.row == m.row && o.right() > m.x)
				row.push_back(&o);
		}
		std::ranges::sort(row, {}, [](Slot const *s) { return s->x; });

		auto cursor = m.right();
		for (auto *o : row) {
			if (o->x < cursor)
				o->x = cursor;
			cursor = o->right();
		}
	}

	int32_t last_row() const {
		int32_t last = 0;
		for (auto const &s : slots_)
			last = std::max(last, s.row);
		return last;
	}

	bool is_alone_on_row(Slot const &m) const {
		return std::ranges::none_of(slots_, [&](Slot const &o) { return &o != &m && o.row == m.row; });
	}
};

} // namespace MetaModule

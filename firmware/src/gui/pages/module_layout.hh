#pragma once
#include <algorithm>
#include <cstdint>
#include <optional>
#include <span>
#include <vector>

namespace MetaModule
{

// Figures out where each module goes on the PatchView canvas
//
// Modules that have a position in the patch file are placed first.
// Next, remaining modules are put into free spaces
struct ModuleLayout {

	// LVGL canvases are images with 11 bits per dimension, so nothing may reach past this
	static constexpr int32_t MaxCanvasDim = 2047;

	struct Coord {
		int32_t x{};
		int32_t y{};

		bool operator==(Coord const &) const = default;
	};

	struct Box {
		int32_t width{};
		int32_t height{};

		// Where the patch specifies this module should go
		std::optional<Coord> wanted{};
	};

	struct Result {
		std::vector<std::optional<Coord>> positions;
		unsigned num_unplaced{};
		int32_t width{}; // extent of everything that was placed
		int32_t height{};
	};

	// width_bound: x coord where modules wrap
	// row_pitch: y distance from one row of modules to the next
	static Result
	arrange(std::span<const Box> boxes, int32_t width_bound, int32_t row_pitch, bool use_wanted_positions) {
		Result result;
		result.positions.resize(boxes.size());

		if (row_pitch <= 0)
			row_pitch = 1;

		// Make sure the rack is wide enough for the widest module to fit
		for (auto const &box : boxes)
			width_bound = std::max(width_bound, box.width);

		width_bound = std::min(width_bound, MaxCanvasDim);

		std::vector<Rect> placed;
		placed.reserve(boxes.size());

		auto commit = [&](size_t i, Coord at, Box const &box) {
			result.positions[i] = at;
			placed.push_back({at.x, at.y, box.width, box.height});
			result.width = std::max(result.width, at.x + box.width);
			result.height = std::max(result.height, at.y + box.height);
		};

		// First pass: Place modules according to the patch file
		// Skip invalid coords (overlapping modules, outside the canvas)
		// Process modules left->right and top->bottom, not in patch order,
		// to make it easier to correct for pixel-rounding drift

		Coord cursor{0, 0};

		// Normalize in X and Y directions, so top modules is at 0, and leftmost module is at 0
		auto shift = Coord{};

		if (use_wanted_positions) {
			shift = origin_of(boxes);

			std::vector<size_t> order;
			for (auto i = 0u; i < boxes.size(); i++) {
				if (boxes[i].wanted.has_value())
					order.push_back(i);
			}

			std::ranges::sort(order, [&boxes](size_t a, size_t b) {
				auto const &pa = *boxes[a].wanted;
				auto const &pb = *boxes[b].wanted;
				return pa.y != pb.y ? pa.y < pb.y : pa.x < pb.x;
			});

			int32_t row_y = 0;
			bool row_started = false;
			int32_t prev_ideal_right = 0;
			int32_t prev_actual_right = 0;

			for (auto i : order) {
				auto const &box = boxes[i];
				Coord ideal{box.wanted->x - shift.x, box.wanted->y - shift.y};

				if (!row_started || ideal.y != row_y) {
					row_y = ideal.y;
					row_started = false;
				}

				auto x = ideal.x;

				if (row_started) {
					// A module is drawn at its faceplate image's width, scaled and truncated to whole pixels,
					// but its position is snapped to the HP grid. The two units disagree by a fraction of a pixel
					// per module, which shows up as a hairline gap at some zoom levels.
					// Correct this by checking if a module lands within SnapTolerancePx of its
					// neighbour's right edge, and pull it flush if so.
					auto shift = prev_actual_right - prev_ideal_right;
					auto candidate = ideal.x + shift;
					auto gap = candidate - prev_actual_right;

					x = (gap >= -SnapTolerancePx && gap <= SnapTolerancePx) ? prev_actual_right : candidate;
				}

				Rect r{x, ideal.y, box.width, box.height};
				if (r.x < 0 || r.y < 0)
					continue;
				if (r.x + r.w > MaxCanvasDim || r.y + r.h > MaxCanvasDim)
					continue;
				if (first_overlap(placed, r))
					continue;

				commit(i, {r.x, r.y}, box);
				cursor = {r.x + r.w, r.y};

				row_started = true;
				row_y = ideal.y;
				prev_ideal_right = ideal.x + box.width;
				prev_actual_right = r.x + r.w;
			}
		}

		// Second pass: carry on from where the last module landed
		for (auto i = 0u; i < boxes.size(); i++) {
			if (result.positions[i].has_value())
				continue;

			if (auto at = find_free_spot(placed, boxes[i], cursor, width_bound, row_pitch)) {
				commit(i, *at, boxes[i]);
				cursor = {at->x + boxes[i].width, at->y};
			}
		}

		// Third pass: back to the top left, dropping modules into any gap they fit in
		for (auto i = 0u; i < boxes.size(); i++) {
			if (result.positions[i].has_value())
				continue;

			if (auto at = find_free_spot(placed, boxes[i], {0, 0}, width_bound, row_pitch))
				commit(i, *at, boxes[i]);
			else
				result.num_unplaced++;
		}

		return result;
	}

private:
	static constexpr int32_t SnapTolerancePx = 2;

	struct Rect {
		int32_t x{}, y{}, w{}, h{};

		bool overlaps(Rect const &o) const {
			return x < o.x + o.w && o.x < x + w && y < o.y + o.h && o.y < y + h;
		}
	};

	// Top-left corner of the bounding box of every stored position
	static Coord origin_of(std::span<const Box> boxes) {
		Coord origin{};
		bool found = false;

		for (auto const &box : boxes) {
			if (!box.wanted.has_value())
				continue;

			if (!found) {
				origin = *box.wanted;
				found = true;
			} else {
				origin.x = std::min(origin.x, box.wanted->x);
				origin.y = std::min(origin.y, box.wanted->y);
			}
		}

		return origin;
	}

	static const Rect *first_overlap(std::vector<Rect> const &placed, Rect const &r) {
		for (auto const &p : placed) {
			if (r.overlaps(p))
				return &p;
		}
		return nullptr;
	}

	// Scans right along each row and then down, starting at `from`, for the first spot the box
	// fits without touching anything already placed.
	static std::optional<Coord> find_free_spot(
		std::vector<Rect> const &placed, Box const &box, Coord from, int32_t width_bound, int32_t row_pitch) {
		if (box.width <= 0 || box.height <= 0)
			return {};

		// A module too wide for the canvas can never be placed
		if (box.width > width_bound)
			return {};

		for (auto y = from.y; y + box.height <= MaxCanvasDim; y += row_pitch) {
			auto x = (y == from.y) ? from.x : 0;

			while (x + box.width <= width_bound) {
				Rect r{x, y, box.width, box.height};

				auto blocker = first_overlap(placed, r);
				if (!blocker)
					return Coord{x, y};

				// Jump past whatever is in the way rather than crawling a pixel at a time
				x = blocker->x + blocker->w;
			}
		}

		return {};
	}
};

} // namespace MetaModule

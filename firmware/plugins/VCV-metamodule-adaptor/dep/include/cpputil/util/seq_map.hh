#pragma once
#include <array>
#include <cstddef>
#include <span>

template<typename KeyT, typename ValT, size_t MaxSize>
struct SeqMap {
	std::array<KeyT, MaxSize> keys;
	std::array<ValT, MaxSize> vals;
	size_t sz = 0;
	size_t oldest = 0;

	bool insert(KeyT key, const ValT &val) {
		if (sz >= MaxSize)
			return false;
		keys[sz] = key;
		vals[sz] = val;
		sz++;
		return true;
	}

	ValT *overwrite(KeyT key, const ValT &val) {
		// overwrite existing key
		auto active_keys = std::span<const KeyT>{keys}.subspan(0, sz);
		for (size_t i = 0; auto k : active_keys) {
			if (k == key) {
				vals[i] = val;
				return &vals[i];
			}
			i++;
		}

		// Overwrite oldest value if full, otherwise append
		size_t index = sz;
		if (sz >= MaxSize) {
			index = oldest;
			oldest++;
			if (oldest >= MaxSize)
				oldest = 0;
		} else
			sz++;

		keys[index] = key;
		vals[index] = val;
		return &vals[index];
	}

	ValT *get(KeyT key) {
		auto active_keys = std::span<const KeyT>{keys}.subspan(0, sz);
		for (size_t i = 0; auto k : active_keys) {
			if (k == key)
				return &vals[i];
			i++;
		}
		return nullptr;
	}

	void remove_last() {
		if (sz > 0)
			sz--;
	}

	bool key_exists(KeyT key) const {
		auto active_keys = std::span<const KeyT>{keys}.subspan(0, sz);
		for (auto &k : active_keys) {
			if (k == key)
				return true;
		}
		return false;
	}

	size_t size() const {
		return sz;
	}
};

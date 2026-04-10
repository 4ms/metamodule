#pragma once
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct NotificationSettings {
	enum class Amount : uint8_t { All = 0, Fewer = 1, OnlyCritical = 2 };

	static constexpr auto DefaultAmount = Amount::All;

	struct Option {
		Amount value;
		std::string_view label;
	};
	static constexpr std::array ValidAmountOptions = {
		Option{Amount::All, "All"},
		Option{Amount::Fewer, "Fewer"},
		Option{Amount::OnlyCritical, "Only Critical"},
	};

	Amount amount = DefaultAmount;
	bool animation = true;

	void make_valid() {
		bool valid = false;
		for (auto o : ValidAmountOptions) {
			if (amount == o.value)
				valid = true;
		}
		if (!valid)
			amount = DefaultAmount;
	}
};

} // namespace MetaModule

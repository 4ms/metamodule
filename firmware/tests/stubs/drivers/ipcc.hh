#pragma once
// #include "drivers/interrupt.hh"
// #include "drivers/ipcc_regs.hh"
#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace mdrivlib
{
template<unsigned N>
struct IPCC_ {
	static_assert(N == 1 || N == 2, "IPCC has Core = 1 and Core = 2 only");
	static inline bool flags[6]{};
	static inline bool tx_isr_masks[6]{};
	static inline bool rx_isr_masks[6]{};
	static inline bool global_txisr_enabled = false;
	static inline bool global_rxisr_enabled = false;

	static void reset() {
		// printf("Reset Core %d\n", N);
		for (auto &f : flags)
			f = false;
		for (auto &m : tx_isr_masks)
			m = true;
		for (auto &m : rx_isr_masks)
			m = true;
		global_rxisr_enabled = false;
		global_txisr_enabled = false;
	}

	// Set/Clear the IPCC Flag:
	// Note: Clearing acts upon the other core's flag
	// and reading the rx occupied flag requires reading the other Core's flags
	template<uint32_t C>
	static void set_flag() {
		// printf("Core %d set flag %d\n", N, C);
		flags[C] = true;
	}
	template<uint32_t C>
	static void clear_flag() {
		// printf("Core %d cleared flag %d\n", N, C);
		// Note: Clearing acts upon the other core's flag
		IPCC_<3 - N>::flags[C] = false;
	}
	template<uint32_t C>
	static bool is_tx_free() {
		// printf("Core %d read flag %d as %d\n", N, C, flags[C]);
		return flags[C] == false;
	}
	template<uint32_t C>
	static bool is_rx_occupied() {
		// printf("Core %d read flag %d as %d\n", N, C, flags[C]);
		return IPCC_<3 - N>::flags[C] == true;
	}
	template<uint32_t C>
	static bool is_other_rx_occupied() {
		// printf("Core %d read Core %d flag %d as %d\n", N, 3 - N, C, IPCC_<3 - N>::flags[C]);
		return flags[C] == true;
	}

	// TXFree:
	template<uint32_t C>
	static void enable_chan_txfree_isr() {
		tx_isr_masks[C] = false;
		// IPCCRegs::Core<N>::template Chan<C>::FreeISRMasked::clear(); //enable = clear a mask bit (unmask)
	}
	template<uint32_t C>
	static void enable_chan_txfree_isr(uint32_t pri, uint32_t subpri, auto &&callback) {
		// IPCCRegs::Core<N>::TXFreeISREnable::set();
		global_txisr_enabled = true;
		enable_chan_txfree_isr<C>();
		// InterruptManager::register_and_start_isr(N == 1 ? IPCC_TX0_IRQn : IPCC_TX1_IRQn, pri, subpri, callback);
	}
	template<uint32_t C>
	static void disable_chan_txfree_isr() {
		// IPCCRegs::Core<N>::template Chan<C>::FreeISRMasked::set();
		tx_isr_masks[C] = true;
	}
	static void disble_all_txfree_isr() {
		// IPCCRegs::Core<N>::TXFreeISREnable::clear();
		global_txisr_enabled = false;
	}

	// RXOccupied:
	template<uint32_t C>
	static void enable_chan_rxocc_isr() {
		// IPCCRegs::Core<N>::template Chan<C>::OccISRMasked::clear(); //enable = clear a mask bit (unmask)
		rx_isr_masks[C] = false;
	}
	template<uint32_t C>
	static void enable_chan_rxocc_isr(uint32_t pri, uint32_t subpri, auto &&callback) {
		// IPCCRegs::Core<N>::RXOccISREnable::set();
		global_rxisr_enabled = true;
		enable_chan_rxocc_isr<C>();
		// InterruptManager::register_and_start_isr(N == 1 ? IPCC_RX0_IRQn : IPCC_RX1_IRQn, pri, subpri, callback);
	}
	template<uint32_t C>
	static void disable_chan_rxocc_isr() {
		rx_isr_masks[C] = true;
		// IPCCRegs::Core<N>::template Chan<C>::OccISRMasked::set(); //disable = set a mask bit
	}
	static void disble_all_rxocc_isr() {
		// IPCCRegs::Core<N>::RXOccISREnable::clear(); //disable = clear an enable bit
		global_rxisr_enabled = false;
	}

	//Half Duplex mode:
	template<uint32_t C>
	struct HalfDuplexMode {
		static auto is_my_turn() {
			if constexpr (N == 1)
				return is_tx_free<C>();
			else
				return is_rx_occupied<C>();
		}

		static void enable_chan_isr(uint32_t pri, uint32_t subpri, auto &&callback) {
			if constexpr (N == 1)
				enable_chan_txfree_isr<C>(pri, subpri, callback);
			else
				enable_chan_rxocc_isr<C>(pri, subpri, callback);
		}

		static auto notify_other() {
			if constexpr (N == 1)
				set_flag<C>();
			else
				clear_flag<C>();
		}

		static auto enable_chan_isr() {
			if constexpr (N == 1)
				enable_chan_txfree_isr<C>();
			else
				enable_chan_rxocc_isr<C>();
		}

		static auto disable_chan_isr() {
			if constexpr (N == 1)
				disable_chan_txfree_isr<C>();
			else
				disable_chan_rxocc_isr<C>();
		}
	};
};

} // namespace mdrivlib

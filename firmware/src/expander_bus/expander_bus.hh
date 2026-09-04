#pragma once

namespace MetaModule
{

// Shared vocabulary between ControlExpanderManager, which owns the aux I2C bus,
// and the expander types that take turns on it.

// XferResult: result of the last xfer this expander started on the last turn.
// `None` means the xfer has not progressed yet.
enum class XferResult {
	None,
	Ok,
	Failed,
};

// What an expander asks of the bus at the end of its turn
struct BusRequest {
	bool started_xfer = false; // an interrupt-driven transfer is now in flight
	bool turn_done = false;	   // finished with the bus for this cycle
	bool reset_bus = false;	   // too many errors: reset the peripheral and back off
};

} // namespace MetaModule

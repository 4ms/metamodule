#pragma once
#include <cstdint>

class ICodec {
public:
	virtual void set_txrx_buffers(uint8_t *tx_buf_ptr, uint8_t *rx_buf_ptr, uint32_t block_size_) = 0;
	virtual void start() = 0;
};


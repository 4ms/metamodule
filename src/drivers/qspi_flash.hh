#pragma GCC push_options
#pragma GCC optimize ("Os")

#pragma once

#define QSPI_FLASH_SIZE_BYTES            0x40000 	// 256 KBytes
#define QSPI_64KBLOCK_SIZE               0x10000  	// 64 KBytes, hence the name "64K Block" :)
#define QSPI_32KBLOCK_SIZE               0x8000   	// 32 KBytes, hence the name "32K Block" :)
#define QSPI_SECTOR_SIZE                 0x1000   	// 4 KBytes sectors
#define QSPI_PAGE_SIZE                   0x100    	// 256 Byte pages
#define QSPI_PAGE_ADDRESS_BITS           8    		// 8 bits = 256 addresses per page

class QSpiFlash {

public:

  enum ErasableSizes {
    SECTOR,
    BLOCK_32K,
    BLOCK_64K,
    ENTIRE_CHIP
  };

  enum FlashStatus {
    STATUS_READY,
    STATUS_WIP,
    STATUS_RXING,
    STATUS_RX_COMPLETE,
    STATUS_TXING,
    STATUS_TX_COMPLETE
  };

  enum UseInterruptFlags {
    EXECUTE_FOREGROUND,
    EXECUTE_BACKGROUND
  };

  // public for use in callbacks and IRQ
  volatile enum FlashStatus QSPI_status = STATUS_READY;
  QSPI_HandleTypeDef handle;

private:

  QSPI_CommandTypeDef s_command;

  HAL_StatusTypeDef WriteEnable(void);
  void GPIO_Init_1IO(void);
  void GPIO_Init_IO2_IO3_AF(void);
  HAL_StatusTypeDef AutoPollingMemReady(uint32_t Timeout);
  HAL_StatusTypeDef AutoPollingMemReady_IT(void);
  HAL_StatusTypeDef EnterMemory_QPI(void);
  void init_command(QSPI_CommandTypeDef *s_command);

  bool done_TXing(void) { return QSPI_status == STATUS_TX_COMPLETE; }

  uint8_t test_encode_num(uint32_t num)	{return (num*7) + (num>>7);}

public:
  QSpiFlash();

  bool is_ready(void) { return QSPI_status == STATUS_READY; }

  bool Test(void);
  bool Test_Sector(uint8_t sector_num);

  static uint32_t get_64kblock_addr(uint8_t block64k_num);
  static uint32_t get_32kblock_addr(uint8_t block32k_num);
  static uint32_t get_sector_addr(uint8_t sector_num);

  HAL_StatusTypeDef Reset(void);

  bool Read(uint8_t* pData, uint32_t read_addr, uint32_t num_bytes,
               UseInterruptFlags use_interrupt);
  bool Write(uint8_t* pData, uint32_t write_addr, uint32_t num_bytes);
  bool Write_Page(uint8_t* pData, uint32_t write_addr, uint32_t num_bytes,
                  UseInterruptFlags use_interrupt);

  bool Erase(ErasableSizes size, uint32_t BaseAddress, UseInterruptFlags use_interrupt);

  static QSpiFlash *instance_;

};


// Wrapper reader/writer inside a 32k block. The block is split into
// [cell_nr_] cells of equal size, each potentially containing an
// object of Data, and aligned to page boundaries
// 
// This template uses 796 bytes for 4 instances
template<int block, class Data>
struct FlashBlock {
  using data_t = Data;
  static constexpr int size_ = QSPI_32KBLOCK_SIZE;
  static constexpr int data_size_ = sizeof(data_t);
  // data size aligned to the next page boundary
  static constexpr int aligned_data_size_ =
    ((data_size_ >> QSPI_PAGE_ADDRESS_BITS) + 1) << QSPI_PAGE_ADDRESS_BITS;
  static_assert(aligned_data_size_ < size_);
  static constexpr int cell_nr_ = size_ / aligned_data_size_;

  bool Read(data_t *data, int cell) {
    if (cell >= cell_nr_) return false;
    uint32_t addr = QSpiFlash::get_32kblock_addr(block) + cell * aligned_data_size_;
    while(!QSpiFlash::instance_->is_ready());
    bool read_ok = QSpiFlash::instance_->Read(reinterpret_cast<uint8_t*>(data),
                                      addr, data_size_,
                                      QSpiFlash::EXECUTE_BACKGROUND);
    while(!QSpiFlash::instance_->is_ready()); //wait for data to be transferred before using it
    return read_ok;
  }

  // cell < cell_nr_
  bool Write(data_t *data, int cell) {
    if (cell >= cell_nr_) return false;
    uint32_t addr = QSpiFlash::get_32kblock_addr(block) + cell * aligned_data_size_;
    while(!QSpiFlash::instance_->is_ready());
    return QSpiFlash::instance_->Write(reinterpret_cast<uint8_t*>(data),
                                       addr, data_size_);
  }

  bool Erase() {
    while(!QSpiFlash::instance_->is_ready());
    return QSpiFlash::instance_->Erase(QSpiFlash::BLOCK_32K,
                                       QSpiFlash::get_32kblock_addr(block),
                                       QSpiFlash::EXECUTE_BACKGROUND);
  }
  // Verify all bits are 1's
  bool IsWriteable(int cell) {
    if (cell >= cell_nr_) return false;
    uint8_t check[data_size_];
    if (Read(reinterpret_cast<data_t*>(check), cell)) {
      for (int i=0; i<data_size_; i++) {
        if (check[i]!=0xFF) return false;
      }
      return true;
    }
    return false;  
  }

  // simple wrappers to read/write in 1st cell
  bool Read(data_t *data) {
    return Read(data, 0);
  }
  bool Write(data_t *data) {
    return Erase() && Write(data, 0);
  }
};

#pragma GCC pop_options
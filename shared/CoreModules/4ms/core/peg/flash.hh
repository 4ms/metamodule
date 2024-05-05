#pragma once
#include "stm32xx.h"

HAL_StatusTypeDef flash_write_page(const uint8_t *data, uint32_t dst_addr, uint32_t bytes_to_write);

void flash_begin_open_program(void);
void flash_end_open_program(void);

HAL_StatusTypeDef flash_open_erase_page(uint32_t address);

HAL_StatusTypeDef flash_open_program_halfword(uint8_t halfword, uint32_t address);
HAL_StatusTypeDef flash_open_program_word(uint32_t word, uint32_t address);
HAL_StatusTypeDef flash_open_program_doubleword(uint64_t doubleword, uint32_t address);

HAL_StatusTypeDef flash_open_program_byte_array(uint8_t *arr, uint32_t address, uint32_t num_bytes);
HAL_StatusTypeDef flash_open_program_halfword_array(uint16_t *arr, uint32_t address, uint32_t num_bytes);
HAL_StatusTypeDef flash_open_program_word_array(uint32_t *arr, uint32_t address, uint32_t num_bytes);

HAL_StatusTypeDef flash_erase_page(uint32_t address);

uint16_t flash_read_halfword(uint32_t address);
uint32_t flash_read_word(uint32_t address);
uint8_t flash_read_byte(uint32_t address);

HAL_StatusTypeDef flash_read_byte_array(uint8_t *arr, uint32_t address, uint32_t num_bytes);
HAL_StatusTypeDef flash_read_halfword_array(uint16_t *arr, uint32_t address, uint32_t num_bytes);
HAL_StatusTypeDef flash_read_word_array(uint32_t *arr, uint32_t address, uint32_t num_bytes);
HAL_StatusTypeDef flash_read_doubleword_array(uint64_t *arr, uint32_t address, uint32_t num_bytes);

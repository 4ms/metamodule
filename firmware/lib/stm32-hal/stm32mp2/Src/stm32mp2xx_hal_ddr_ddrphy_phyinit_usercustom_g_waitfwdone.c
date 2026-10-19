/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stm32mp2xx_hal.h"
#include "stm32mp2xx_hal_ddr_ddrphy_phyinit_usercustom.h"

/* Firmware major messages */
#define FW_MAJ_MSG_TRAINING_SUCCESS	0x0000007
#define FW_MAJ_MSG_START_STREAMING	0x0000008
#define FW_MAJ_MSG_TRAINING_FAILED	0x00000FF

#define PHYINIT_DELAY_1US		1U
#define PHYINIT_DELAY_10US		10U
#define PHYINIT_TIMEOUT_US_1S		1000000U

static void phyinit_udelay(unsigned long delay_us)
{
  __IO uint32_t wait_loop_index = 0U;

  wait_loop_index = (delay_us * (SystemCoreClock / (1000000UL * 2UL)));

  #ifdef USE_STM32MP257CXX_EMU
  wait_loop_index /= 100;
  #endif

  while(wait_loop_index != 0UL)
  {
    wait_loop_index--;
  }
}

static __IO uint32_t phyinit_timeout_init_us(unsigned long timeout_us)
{
  __IO uint32_t wait_loop_index = 0U;

  wait_loop_index = timeout_us * (SystemCoreClock / (1000000UL * 2UL));

  #ifdef USE_STM32MP257CXX_EMU
  wait_loop_index *= 10;
  #endif

  return wait_loop_index;
}

static bool phyinit_timeout_elapsed(__IO uint32_t timeout)
{
  if (timeout == 0U)
  {
    return true;
  }

  return false;
}

static int wait_uctwriteprotshadow(bool state)
{
	uint16_t read_data;
	uint16_t value = state ? 1U : 0U;
	__IO uint32_t timeout = phyinit_timeout_init_us(PHYINIT_TIMEOUT_US_1S);

	do {
		read_data = mmio_read_16((uintptr_t)(DDRPHYC_BASE +
						     (4 * (TAPBONLY | CSR_UCTSHADOWREGS_ADDR))));
		timeout--;
		if (phyinit_timeout_elapsed(timeout))
		{
			return -1;
		}
	} while ((read_data & 1U) != value);

	return 0;
}

static int ack_message_receipt(void)
{
	int ret;

	/* Acknowledge the receipt of the message */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + (4 * (TAPBONLY | CSR_DCTWRITEPROT_ADDR))), 0U);

	phyinit_udelay(PHYINIT_DELAY_1US);

	ret = wait_uctwriteprotshadow(true);
	if (ret != 0) {
		return ret;
	}

	/* Complete the 4-phase protocol */
	mmio_write_16((uintptr_t)(DDRPHYC_BASE + (4 * (TAPBONLY | CSR_DCTWRITEPROT_ADDR))), 1U);

	phyinit_udelay(PHYINIT_DELAY_1US);

	return 0;
}

static int get_major_message(int *msg)
{
	int message_number;
	int ret;

	ret = wait_uctwriteprotshadow(false);
	if (ret != 0) {
		return ret;
	}

	message_number = mmio_read_16((uintptr_t)(DDRPHYC_BASE +
						  (4 * (TAPBONLY | CSR_UCTWRITEONLYSHADOW_ADDR))));

	ret = ack_message_receipt();
	if (ret != 0) {
		return ret;
	}

	*msg = message_number;

	return 0;
}

static int get_streaming_message(int *msg)
{
	int stream_word_lower_part;
	int stream_word_upper_part;
	int ret;

	ret = wait_uctwriteprotshadow(false);
	if (ret != 0) {
		return ret;
	}

	stream_word_lower_part = mmio_read_16((uintptr_t)(DDRPHYC_BASE +
							  (4 * (TAPBONLY |
								CSR_UCTWRITEONLYSHADOW_ADDR))));

	stream_word_upper_part = mmio_read_16((uintptr_t)(DDRPHYC_BASE +
							  (4 * (TAPBONLY |
								CSR_UCTDATWRITEONLYSHADOW_ADDR))));

	ret = ack_message_receipt();
	if (ret != 0) {
		return ret;
	}

	*msg = stream_word_lower_part | (stream_word_upper_part << 16);

	return 0;
}

/*
 * Implements the mechanism to wait for completion of training firmware execution.
 *
 * The purpose of user this function is to wait for firmware to finish training.
 * The user can either implement a counter to wait or implement the polling
 * mechanism described in the Training Firmware App Note section "Running the
 * Firmware".  The wait time is highly dependent on the training features
 * enabled via sequencectrl input to the message block.  See Training Firmware
 * App note for details.
 *
 * The default behavior of this function is to print comments relating to this
 * process.  A function call of the same name will be printed in the output text
 * file.
 *
 * The user can choose to leave this function as is, or implement mechanism to
 * trigger mailbox poling event in simulation.
 *
 * \return 0 on success.
 */
int ddrphy_phyinit_usercustom_g_waitfwdone(void)
{
	int fw_major_message;
	int ret;

	VERBOSE("%s Start\n", __func__);

	do {
		ret = get_major_message(&fw_major_message);
		if (ret != 0) {
			return ret;
		}

		VERBOSE("fw_major_message = %x\n", (unsigned int)fw_major_message);

		if (fw_major_message == FW_MAJ_MSG_START_STREAMING) {
			int i;
			int read_data;
			int stream_len;

			ret = get_streaming_message(&read_data);
			if (ret != 0) {
				return ret;
			}

			stream_len = read_data & 0xFFFF;

			for (i = 0; i < stream_len; i++) {
				ret = get_streaming_message(&read_data);
				if (ret != 0) {
					return ret;
				}

				VERBOSE("streaming message = %x\n", (unsigned int)read_data);
			}
		}
	} while ((fw_major_message != FW_MAJ_MSG_TRAINING_SUCCESS) &&
		 (fw_major_message != FW_MAJ_MSG_TRAINING_FAILED));

	phyinit_udelay(PHYINIT_DELAY_10US);

	if (fw_major_message == FW_MAJ_MSG_TRAINING_FAILED) {
		ERROR("%s Training has failed.\n", __func__);
		return -1;
	}

	VERBOSE("%s End\n", __func__);

	return 0;
}

#pragma once
#include "usbh_def.h"

void parse_midistream_itf_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_injack_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_outjack_desc(USBH_DescHeader_t const *pdesc);
void parse_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_cs_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void scan_all_descriptors(USBH_HandleTypeDef const *phost);

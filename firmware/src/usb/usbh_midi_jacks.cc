#include "usbh_ctlreq.h"
#include "usbh_def.h"
#include <cstdint>

// TODO: Make these functions store useful information about
// the MIDI topology (possibly letting the user choose a different
// endpoint/jack combo.
//
// Right now these functions just print detailed info about the
// descriptors found.

constexpr uint16_t as_le_u16(uint16_t x) {
	// reinterpret_cast of midi bytes works as-is on cortex-a7
	return x;
	// on some other system, perhaps this is needed?
	// return (x << 8) | (x >> 8);
}

void parse_audiocontrol_itf_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) AudioControlInterfaceDescriptor {
		uint8_t len;
		uint8_t type;
		uint8_t subtype;
		uint16_t class_revision;
		uint16_t class_specific_desc_total_size;
		uint8_t num_midi_itfs;
		uint8_t our_midi_itf_id;
	};

	auto *d = reinterpret_cast<AudioControlInterfaceDescriptor const *>(pdesc);

	printf("AudioControl interface (len %u, expected %zu): ", d->len, sizeof(AudioControlInterfaceDescriptor));
	printf("class_revision: %u\n", as_le_u16(d->class_revision));
	printf("class_specific_desc_total_size: %u\n", as_le_u16(d->class_specific_desc_total_size));
	printf("num_midi_itfs: %u\n", d->num_midi_itfs);
	printf("our_midi_itf_id: %u\n", d->our_midi_itf_id);
	printf("\n");
}

void parse_midistream_itf_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) MidiStreamInterfaceDescriptor {
		uint8_t len;
		uint8_t type;
		uint8_t subtype;
		uint16_t class_revision;
		uint16_t class_specific_desc_total_size;
	};
	auto *d = reinterpret_cast<MidiStreamInterfaceDescriptor const *>(pdesc);

	printf("MidiStreaming interface (len %u, expected %zu): ", d->len, sizeof(MidiStreamInterfaceDescriptor));
	printf("class_revision: %u\n", as_le_u16(d->class_revision));
	printf("class_specific_desc_total_size: %u\n", as_le_u16(d->class_specific_desc_total_size));
	printf("\n");
}

void parse_midistream_injack_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) MidiInJackDescriptor {
		uint8_t len;
		uint8_t type;
		uint8_t subtype;
		enum class JackType : uint8_t { Embedded = 1, External = 2 };
		JackType jack_type;
		uint8_t jack_id;
		uint8_t jack_string_idx;
	};
	auto *d = reinterpret_cast<MidiInJackDescriptor const *>(pdesc);

	printf("MidiInJackDescriptor interface (len %u, expected %zu): ", d->len, sizeof(MidiInJackDescriptor));
	printf("jack_type: %u (emb=1, ext=2)\n", d->jack_type);
	printf("jack_id: %u\n", d->jack_id);
	printf("jack_string_idx: %u\n", d->jack_string_idx);
	printf("\n");
}

void parse_midistream_outjack_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) MidiOutJackDescriptor {
		uint8_t len;
		uint8_t type;
		uint8_t subtype;
		enum class JackType : uint8_t { Embedded = 1, External = 2 };
		JackType jack_type;
		uint8_t jack_id;
		uint8_t num_input_pins;
		uint8_t connected_to_entity_id;
		uint8_t connected_to_entity_pin;
		uint8_t jack_string_idx;
	};
	auto *d = reinterpret_cast<MidiOutJackDescriptor const *>(pdesc);

	printf("MidiOutJackDescriptor interface (len %u, expected %zu): ", d->len, sizeof(MidiOutJackDescriptor));
	printf("jack_type: %u (emb=1, ext=2)\n", d->jack_type);
	printf("jack_id: %u\n", d->jack_id);
	printf("num_input_pins: %u\n", d->num_input_pins);
	printf("connected_to_entity_id: %u\n", d->connected_to_entity_id);
	printf("connected_to_entity_pin: %u\n", d->connected_to_entity_pin);
	printf("jack_string_idx: %u\n", d->jack_string_idx);
	printf("\n");
}

void parse_bulk_ep_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) EPDescriptor {
		uint8_t len;
		uint8_t type; //0x05
		uint8_t addr;
		uint8_t ep_type; //0x02
		uint16_t max_packet_size;
		uint8_t interval_ignore;
		uint8_t refresh_ignore;
		uint8_t sync_addr_ignore;
	};
	auto *d = reinterpret_cast<EPDescriptor const *>(pdesc);

	printf("EPDescriptor interface (len %u, expected %zu): \n", d->len, sizeof(EPDescriptor));
	if (d->type != 0x5 || d->ep_type != 0x2)
		printf("Type 0x%x (expected 0x5), ep_type %u (expected 2=bulk)\n", d->type, d->ep_type);

	printf("addr: %u (%s)\n", d->addr & 0x7F, (d->addr & 0x80) ? "In" : "Out");
	printf("max_packet_size: %u\n", d->max_packet_size);
	printf("\n");
}

void parse_midistream_cs_bulk_ep_desc(USBH_DescHeader_t const *pdesc) {
	struct __attribute__((packed)) MidiEPDescriptor {
		uint8_t len;
		uint8_t type;	 //0x25
		uint8_t subtype; //1
		uint8_t num_embedded_midi_in_jacks;
		uint8_t associated_jack_id[];
	};
	auto *d = reinterpret_cast<MidiEPDescriptor const *>(pdesc);

	printf("MidiEPDescriptor interface (len %u, min 5): \n", d->len);
	if (d->type != 0x25 || d->subtype != 0x1)
		printf("Type 0x%x (expected 0x25), subtype %u (expected 1)\n", d->type, d->subtype);
	printf("num_embedded_midi_in_jacks: %u\n", d->num_embedded_midi_in_jacks);
	for (auto i = 0u; i < d->num_embedded_midi_in_jacks; i++)
		printf("associated_jack_id %u: %u\n", i, d->associated_jack_id[i]);
	printf("\n");
}

void scan_all_descriptors(USBH_HandleTypeDef const *phost) {
	unsigned desc_total_length = phost->device.CfgDesc.wTotalLength;
	auto *pdesc = reinterpret_cast<USBH_DescHeader_t const *>(phost->device.CfgDesc_Raw);
	uint16_t ptr = USB_LEN_CFG_DESC;

	while (ptr < desc_total_length) {
		pdesc = USBH_GetNextDesc((uint8_t *)(void *)pdesc, &ptr);

		printf("desc: len %u, type 0x%x (ptr=%u): ", pdesc->bLength, pdesc->bDescriptorType, ptr);
		for (unsigned i = 0; i < pdesc->bLength; i++) {
			printf("%02x ", (unsigned)*((uint8_t *)(pdesc) + i));
		}
		printf("\n");

		if (pdesc->bDescriptorType == 0x24) //Class-specific descriptor
		{
			uint8_t subtype = ((uint8_t *)pdesc)[2];
			if (subtype == 1) { //MS_HEADER
				if (pdesc->bLength == 0x9)
					parse_audiocontrol_itf_desc(pdesc);
				else
					parse_midistream_itf_desc(pdesc);
			} else if (subtype == 0x02) {
				parse_midistream_injack_desc(pdesc);
			} else if (subtype == 0x03) {
				parse_midistream_outjack_desc(pdesc);
			}

		} else if (pdesc->bDescriptorType == 0x25) { //Class-specific endpoint desc
			parse_midistream_cs_bulk_ep_desc(pdesc);

		} else if (pdesc->bDescriptorType == 0x5) { //Standard endpoint desc
			parse_bulk_ep_desc(pdesc);
		}
	}
}

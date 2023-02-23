#define printf_ printf
#define __DMB()

static inline unsigned HAL_GetTick() {
	static unsigned tm = 0;
	tm++;
	return tm;
}

#include "../src/inter_core_comm.hh"
#include "doctest.h"

using namespace MetaModule;

static volatile InterCoreCommMessage sharedmsg;
static MetaModule::InterCoreComm<MetaModule::ICCCoreType::Initiator> tx{sharedmsg};
static MetaModule::InterCoreComm<MetaModule::ICCCoreType::Responder> rx{sharedmsg};

TEST_CASE("ICC") {

	SUBCASE("Tx can send right away, but only once") {
		mdrivlib::IPCC_<1>::reset();
		mdrivlib::IPCC_<2>::reset();

		InterCoreCommMessage msg;
		msg.message_type = InterCoreCommMessage::RequestRefreshPatchList;
		bool ok = tx.send_message(msg);
		CHECK(ok);

		ok = tx.send_message(msg);
		CHECK_FALSE(ok);
	}

	SUBCASE("RX cannot send right away") {
		mdrivlib::IPCC_<1>::reset();
		mdrivlib::IPCC_<2>::reset();

		InterCoreCommMessage msg;
		msg.message_type = InterCoreCommMessage::RequestRefreshPatchList;
		bool ok = rx.send_message(msg);
		CHECK_FALSE(ok);
	}

	SUBCASE("Tx sends, RX receives it, sends back, TX receives it") {
		mdrivlib::IPCC_<1>::reset();
		mdrivlib::IPCC_<2>::reset();

		InterCoreCommMessage msg;

		msg.message_type = InterCoreCommMessage::RequestRefreshPatchList;
		bool ok = tx.send_message(msg);
		CHECK(ok);

		auto rxmsg = rx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::RequestRefreshPatchList);

		msg.message_type = InterCoreCommMessage::PatchListChanged;
		ok = rx.send_message(msg);
		CHECK(ok);

		rxmsg = tx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::PatchListChanged);
	}
}

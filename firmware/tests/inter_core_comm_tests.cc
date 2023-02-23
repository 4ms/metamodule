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

	SUBCASE("Tx sends, RX receives it, sends back, TX receives it, repeat") {
		mdrivlib::IPCC_<1>::reset();
		mdrivlib::IPCC_<2>::reset();

		InterCoreCommMessage msg;

		// First round:
		msg.message_type = InterCoreCommMessage::RequestRefreshPatchList;
		bool ok = tx.send_message(msg);
		CHECK(ok);

		auto rxmsg = rx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::RequestRefreshPatchList);

		msg.message_type = InterCoreCommMessage::PatchListChanged;
		ok = rx.send_message(msg);
		CHECK(ok);

		auto txmsg = tx.get_new_message();
		CHECK(txmsg.message_type == InterCoreCommMessage::PatchListChanged);

		// Second round:
		msg.message_type = InterCoreCommMessage::RequestPatchData;
		ok = tx.send_message(msg);
		CHECK(ok);

		rxmsg = rx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::RequestPatchData);

		msg.message_type = InterCoreCommMessage::PatchDataLoaded;
		ok = rx.send_message(msg);
		CHECK(ok);

		txmsg = tx.get_new_message();
		CHECK(txmsg.message_type == InterCoreCommMessage::PatchDataLoaded);
	}

	SUBCASE("Checking get_new_message repeatedly doesn't break anything") {
		mdrivlib::IPCC_<1>::reset();
		mdrivlib::IPCC_<2>::reset();

		InterCoreCommMessage msg;

		// First round:
		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);

		msg.message_type = InterCoreCommMessage::RequestRefreshPatchList;
		bool ok = tx.send_message(msg);
		CHECK(ok);

		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);

		auto rxmsg = rx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::RequestRefreshPatchList);

		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);

		msg.message_type = InterCoreCommMessage::PatchListChanged;
		ok = rx.send_message(msg);
		CHECK(ok);

		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);

		auto txmsg = tx.get_new_message();
		CHECK(txmsg.message_type == InterCoreCommMessage::PatchListChanged);

		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(rx.get_new_message().message_type == InterCoreCommMessage::None);

		// Second round:
		msg.message_type = InterCoreCommMessage::RequestPatchData;
		ok = tx.send_message(msg);
		CHECK(ok);

		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);
		CHECK(tx.get_new_message().message_type == InterCoreCommMessage::None);

		rxmsg = rx.get_new_message();
		CHECK(rxmsg.message_type == InterCoreCommMessage::RequestPatchData);
	}
}

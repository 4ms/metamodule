#include "central_data.hh"
#include "doctest.h"

TEST_CASE("getNumModules() and register/unregistering modules")
{
	CentralData cd;
	SUBCASE("Before any init, getNumModules() returns 0") { CHECK(cd.getNumModules() == 0); }

	SUBCASE("Registering a module increases the number of modules returned by getNumModules()")
	{
		cd.registerModule({1, "TESTMODULE"});
		CHECK(cd.getNumModules() == 1);

		cd.registerModule({1, "TESTMODULE"}); // duplicate entry
		CHECK(cd.getNumModules() == 2);

		cd.registerModule({2, "SOME_OTHER_MOD"});
		CHECK(cd.getNumModules() == 3);

		SUBCASE("Removing a module decreases getNumModules() by 1, even if the module exists twice")
		{
			cd.unregisterModule({1, "TESTMODULE"});
			CHECK(cd.getNumModules() == 2);

			cd.unregisterModule({1, "TESTMODULE"});
			CHECK(cd.getNumModules() == 1);

			cd.unregisterModule({2, "SOME_OTHER_MOD"});
			CHECK(cd.getNumModules() == 0);

			SUBCASE("Removing a module twice doesn't crash")
			{
				cd.unregisterModule({1, "TESTMODULE"});
				cd.unregisterModule({1, "TESTMODULE"});
				cd.unregisterModule({2, "SOME_OTHER_MOD"});
				CHECK(cd.getNumModules() == 0);
			}
		}
		SUBCASE("Removing non-existant modules doesn't change getNumModules() or crash")
		{
			cd.unregisterModule({999, "DOESNT_EXIST"});
			CHECK(cd.getNumModules() == 3);
		}
		SUBCASE("Both the module ID and the typeID (slug) must match for a module to be removed")
		{
			cd.unregisterModule({1, "WRONG_SLUG"});
			CHECK(cd.getNumModules() == 3);

			cd.unregisterModule({999, "TESTMODULE"});
			CHECK(cd.getNumModules() == 3);
		}
	}
}

TEST_CASE("ParamStatus adding and remove param data")
{
	CentralData cd;
	SUBCASE("Before any init, paramData is size 0") { CHECK(cd.paramData.size() == 0); }
	SUBCASE("updateParamStatus() with new module/param IDs adds it to paramData")
	{
		cd.registerModule({1, "MODULE"});
		ParamStatus p;
		p.value = 0.5;
		p.moduleID = 1;
		p.paramID = 3;
		cd.updateParamStatus(p);
		CHECK(cd.paramData.size() == 1);

		bool found = false;
		for (auto &x : cd.paramData) {
			if (x.value == p.value && x.moduleID == p.moduleID && x.paramID == p.paramID)
				found = true;
		}
		CHECK(found);

		SUBCASE("updateParamStatus() with an existing module/param ID updates the value and doesn't make a new entry")
		{
			ParamStatus p2;
			p2.value = 0.7;
			p2.moduleID = 1;
			p2.paramID = 3;
			cd.updateParamStatus(p2);

			CHECK(cd.paramData.size() == 1);
			found = false;
			for (auto &x : cd.paramData) {
				if (x.value == p2.value && x.moduleID == p2.moduleID && x.paramID == p2.paramID)
					found = true;
			}
			CHECK(found);
		}
	}

	SUBCASE("Removing a module also removes its params")
	{
		cd.registerModule({1, "MODULE"});
		ParamStatus p;
		p.value = 0.5;
		p.moduleID = 1;
		p.paramID = 3;
		cd.updateParamStatus(p);
		cd.unregisterModule({1, "MODULE"});
		CHECK(cd.paramData.size() == 0);
	}
	// Todo: Adding a param with a moduleID that's not registered, will not add the param (? or will it?)
}

TEST_CASE("JackStatus adding and remove patched cable data")
{
	CentralData cd;
	SUBCASE("Before any init, jackData is size 0") { CHECK(cd.jackData.size() == 0); }
	SUBCASE("updateJackStatus() with new module/jack IDs adds it to jackData")
	{
		cd.registerModule({1, "MODULE"});
		cd.registerModule({2, "MODULE2"});
		JackStatus j;
		j.connected = true;
		j.receivedJackId = 101;
		j.receivedModuleId = 1;
		j.sendingJackId = 202;
		j.sendingModuleId = 2;
		cd.updateJackStatus(j);
		CHECK(cd.jackData.size() == 1);

		bool found = false;
		for (auto &x : cd.jackData) {
			if (x.receivedJackId == j.receivedJackId && x.receivedModuleId == j.receivedModuleId &&
				x.sendingJackId == j.sendingJackId && x.sendingModuleId == j.sendingModuleId)
				found = true;
		}
		CHECK(found);

		SUBCASE("updateJackStatus() with an existing sendingjackID/moduleID and different receivedJackId/ModuleId: "
				"updates the connection info and doesn't make a new entry")
		{
			auto originalSize = cd.jackData.size();
			JackStatus j2;
			j2.connected = true;
			j2.receivedJackId = 999;
			j2.receivedModuleId = 999;
			j2.sendingJackId = 202;
			j2.sendingModuleId = 2;
			cd.updateJackStatus(j2);

			CHECK(cd.jackData.size() == originalSize);
			found = false;
			for (auto &x : cd.jackData) {
				if (x.receivedJackId == j2.receivedJackId && x.receivedModuleId == j2.receivedModuleId &&
					x.sendingJackId == j2.sendingJackId && x.sendingModuleId == j2.sendingModuleId)
					found = true;
			}
			CHECK(found);
		}
		SUBCASE("Updating the jack info to connected=false, will set receivedJack/ModuleIds to -1")
		{
			j.connected = false;
			cd.updateJackStatus(j);
			CHECK(cd.jackData.size() == 1);
			found = false;
			for (auto &x : cd.jackData) {
				if (x.receivedJackId == -1 && x.receivedModuleId == -1 && x.sendingJackId == j.sendingJackId &&
					x.sendingModuleId == j.sendingModuleId)
					found = true;
			}
			CHECK(found);
		}
	}

	SUBCASE("Removing a module also removes its jack info")
	{
		cd.registerModule({1, "MODULE"});
		cd.registerModule({999, "MODULE999"});
		JackStatus j2;
		j2.connected = true;
		j2.receivedJackId = 999;
		j2.receivedModuleId = 999;
		j2.sendingJackId = 202;
		j2.sendingModuleId = 1;
		cd.updateJackStatus(j2);
		SUBCASE("Removing the sendingModule")
		{
			cd.unregisterModule({1, "MODULE"});
			CHECK(cd.jackData.size() == 0);
		}
		SUBCASE("Removing the receivingModule")
		{
			cd.unregisterModule({999, "MODULE999"});
			CHECK(cd.jackData.size() == 0);
		}
	}
}

TEST_CASE("messages system")
{
	CentralData cd;
	cd.registerModule({1, "MODULE1"});
	cd.registerModule({2, "MODULE2"});

	SUBCASE("No messages initially")
	{
		CHECK(cd.getMyMessage(1) == CentralData::MessageType::None);
		CHECK(cd.getMyMessage(2) == CentralData::MessageType::None);
	}

	SUBCASE("requestAllParamDataAllModules() sends everyone a message")
	{
		cd.requestAllParamDataAllModules();
		CHECK(cd.getMyMessage(1) == CentralData::MessageType::RequestAllParamData);
		CHECK(cd.getMyMessage(2) == CentralData::MessageType::RequestAllParamData);
	}
	SUBCASE("Messages are cleared after getMyMessages()")
	{
		cd.requestAllParamDataAllModules();
		cd.getMyMessage(1);
		CHECK(cd.getMyMessage(1) == CentralData::MessageType::None);

		// module 2's message shouldn't be cleared until it's checked
		CHECK(cd.getMyMessage(2) == CentralData::MessageType::RequestAllParamData);
		cd.getMyMessage(2);
		CHECK(cd.getMyMessage(2) == CentralData::MessageType::None);
	}
}

TEST_CASE("mappings")
{
	CentralData cd;

	SUBCASE("Creating a mapping, then checking if the src and dst are mapped")
	{
		cd.registerModule({1, "MODULE1"});
		LabelButtonID src;
		src.moduleID = 1;
		src.objID = 2;
		src.objType = LabelButtonID::Types::Knob;

		cd.registerModule({100, "MODULE100"});
		LabelButtonID dst;
		dst.moduleID = 100;
		dst.objID = 200;
		dst.objType = LabelButtonID::Types::Knob;

		cd.startMappingProcedure(src);
		cd.registerMapDest(dst);

		CHECK(cd.isLabelButtonMapped(src));
		CHECK(cd.isLabelButtonMapped(dst));

		CHECK(cd.isLabelButtonDstMapped(dst));
		CHECK(cd.isLabelButtonSrcMapped(dst) == false);

		CHECK(cd.isLabelButtonSrcMapped(src));
		CHECK(cd.isLabelButtonDstMapped(src) == false);

		SUBCASE("Other objects are not mapped")
		{
			LabelButtonID unmappedknob;
			unmappedknob.moduleID = 999;
			unmappedknob.objID = 222;
			unmappedknob.objType = LabelButtonID::Types::Knob;
			CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
			unmappedknob.moduleID = 1;
			unmappedknob.objID = 222;
			unmappedknob.objType = LabelButtonID::Types::Knob;
			CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
			unmappedknob.moduleID = 111;
			unmappedknob.objID = 2;
			unmappedknob.objType = LabelButtonID::Types::Knob;
			CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
			unmappedknob.moduleID = 1;
			unmappedknob.objID = 2;
			unmappedknob.objType = LabelButtonID::Types::InputJack;
			CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
		}

		SUBCASE("Default range is 0..1")
		{
			auto [min, max] = cd.getMapRange(src, dst);
			CHECK(min == doctest::Approx(0.f));
			CHECK(max == doctest::Approx(1.f));

			SUBCASE("Can set a range and read it back")
			{
				cd.setMapRange(src, dst, 0.24f, 0.78f);
				auto [min, max] = cd.getMapRange(src, dst);
				CHECK(min == doctest::Approx(0.24f));
				CHECK(max == doctest::Approx(0.78f));
			}
		}
		// Not multi-map friendly
		// 		SUBCASE("Add other mappings, but still can access the original src or dest by providing one of the
		// pair")
		// 		{
		// 			LabelButtonID dst2;
		// 			dst2.moduleID = 888;
		// 			dst2.objID = 999;
		// 			dst2.objType = LabelButtonID::Types::Knob;
		// 			LabelButtonID src2;
		// 			src2.moduleID = 777;
		// 			src2.objID = 666;
		// 			src2.objType = LabelButtonID::Types::Knob;
		// 			cd.startMappingProcedure(src2);
		// 			cd.registerMapDest(dst2);

		// 			auto should_be_src = cd.getMappedSrcFromDst(dst);
		// 			CHECK(should_be_src == src);

		// 			auto should_be_dst = cd.getMappedDstFromSrc(src);
		// 			CHECK(should_be_dst == dst);
		// 		}

		SUBCASE("Removing a mapping")
		{
			SUBCASE("By calling unregisterMapByDest")
			{
				CHECK(cd.isLabelButtonMapped(src));
				CHECK(cd.isLabelButtonMapped(dst));
				cd.unregisterMapByDest(dst);
				CHECK_FALSE(cd.isLabelButtonMapped(src));
				CHECK_FALSE(cd.isLabelButtonMapped(dst));
			}
			SUBCASE("By removing the src module")
			{
				CHECK(cd.isLabelButtonMapped(src));
				CHECK(cd.isLabelButtonMapped(dst));
				cd.unregisterModule({1, "MODULE"});
				CHECK_FALSE(cd.isLabelButtonMapped(src));
				CHECK_FALSE(cd.isLabelButtonMapped(dst));
			}
			SUBCASE("By removing the dst module")
			{
				CHECK(cd.isLabelButtonMapped(src));
				CHECK(cd.isLabelButtonMapped(dst));
				cd.unregisterModule({100, "MODULE100"});
				CHECK_FALSE(cd.isLabelButtonMapped(src));
				CHECK_FALSE(cd.isLabelButtonMapped(dst));
			}
		}
	}
}

TEST_CASE("clear_if") {}

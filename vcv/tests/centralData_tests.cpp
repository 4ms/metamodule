#include "centralData.h"
#include "doctest.h"

TEST_CASE("getNumModules() and register/unregistering modules")
{
	CentralData cd;
	SUBCASE("Before any init, getNumModules() returns 0")
	{
		CHECK(cd.getNumModules() == 0);
	}

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
	SUBCASE("Before any init, paramData is size 0")
	{
		CHECK(cd.paramData.size() == 0);
	}
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


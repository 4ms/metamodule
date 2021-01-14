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

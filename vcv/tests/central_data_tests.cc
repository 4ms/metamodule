#include "central_data.hh"
#include "doctest.h"

TEST_CASE("mappings")
{
	CentralData cd;

	SUBCASE("Creating a mapping, then checking if the src and dst are mapped")
	{
		rack::Module m1;
		cd.registerModule({1, "MODULE1"}, &m1);
		MappableObj src;
		src.moduleID = 1;
		src.objID = 2;
		src.objType = MappableObj::Type::Knob;

		rack::Module m2;
		cd.registerModule({100, "MODULE100"}, &m2);
		MappableObj dst;
		dst.moduleID = 100;
		dst.objID = 200;
		dst.objType = MappableObj::Type::Knob;

		cd.startMappingProcedure(src);

		// TESTS ARE BROKEN
		// Re-do with new framework that scans VCV Engine

		// cd.registerMapDest(dst);

		// CHECK(cd.isLabelButtonMapped(src));
		// CHECK(cd.isLabelButtonMapped(dst));

		// CHECK(cd.isLabelButtonDstMapped(dst));
		// CHECK(cd.isLabelButtonSrcMapped(dst) == false);

		// CHECK(cd.isLabelButtonSrcMapped(src));
		// CHECK(cd.isLabelButtonDstMapped(src) == false);

		// SUBCASE("Other objects are not mapped")
		// {
		// 	MappableObj unmappedknob;
		// 	unmappedknob.moduleID = 999;
		// 	unmappedknob.objID = 222;
		// 	unmappedknob.objType = MappableObj::Type::Knob;
		// 	CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
		// 	unmappedknob.moduleID = 1;
		// 	unmappedknob.objID = 222;
		// 	unmappedknob.objType = MappableObj::Type::Knob;
		// 	CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
		// 	unmappedknob.moduleID = 111;
		// 	unmappedknob.objID = 2;
		// 	unmappedknob.objType = MappableObj::Type::Knob;
		// 	CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
		// 	unmappedknob.moduleID = 1;
		// 	unmappedknob.objID = 2;
		// 	unmappedknob.objType = MappableObj::Type::InputJack;
		// 	CHECK(cd.isLabelButtonMapped(unmappedknob) == false);
		// }

		// SUBCASE("Default range is 0..1")
		// {
		// 	auto [min, max] = cd.getMapRange(src, dst);
		// 	CHECK(min == doctest::Approx(0.f));
		// 	CHECK(max == doctest::Approx(1.f));

		// 	SUBCASE("Can set a range and read it back")
		// 	{
		// 		cd.setMapRange(src, dst, 0.24f, 0.78f);
		// 		auto [min, max] = cd.getMapRange(src, dst);
		// 		CHECK(min == doctest::Approx(0.24f));
		// 		CHECK(max == doctest::Approx(0.78f));
		// 	}
		// }

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

		// SUBCASE("Removing a mapping")
		// {
		// 	SUBCASE("By calling unregisterMapByDest")
		// 	{
		// 		CHECK(cd.isLabelButtonMapped(src));
		// 		CHECK(cd.isLabelButtonMapped(dst));
		// 		cd.unregisterMapByDest(dst);
		// 		CHECK_FALSE(cd.isLabelButtonMapped(src));
		// 		CHECK_FALSE(cd.isLabelButtonMapped(dst));
		// 	}
		// 	SUBCASE("By removing the src module")
		// 	{
		// 		CHECK(cd.isLabelButtonMapped(src));
		// 		CHECK(cd.isLabelButtonMapped(dst));
		// 		cd.unregisterModule({1, "MODULE"});
		// 		CHECK_FALSE(cd.isLabelButtonMapped(src));
		// 		CHECK_FALSE(cd.isLabelButtonMapped(dst));
		// 	}
		// 	SUBCASE("By removing the dst module")
		// 	{
		// 		CHECK(cd.isLabelButtonMapped(src));
		// 		CHECK(cd.isLabelButtonMapped(dst));
		// 		cd.unregisterModule({100, "MODULE100"});
		// 		CHECK_FALSE(cd.isLabelButtonMapped(src));
		// 		CHECK_FALSE(cd.isLabelButtonMapped(dst));
		// 	}
		// }
	}
}

#include "doctest.h"
#include "gui/pages/module_view/group_member_name.hh"

using MetaModule::ModView::group_member_name;

TEST_CASE("Group member names: words in the group name are removed") {
	CHECK(group_member_name("Red Speed", "Red") == "Speed");
	CHECK(group_member_name("Red Jitter", "Red") == "Jitter");
	CHECK(group_member_name("Feedback A", "Channel A") == "Feedback");
	CHECK(group_member_name("Time A", "Channel A") == "Time");
	CHECK(group_member_name("Channel A Level", "Channel A") == "Level");
	CHECK(group_member_name("Mix A to B", "A") == "Mix to B");
}

TEST_CASE("Group member names: only whole, space-separated words match") {
	CHECK(group_member_name("A1_Gain", "Channel A") == "A1_Gain");
	CHECK(group_member_name("A:Level", "Channel A") == "A:Level");
	CHECK(group_member_name("Redux", "Red") == "Redux");
	CHECK(group_member_name("Red-Speed", "Red") == "Red-Speed");
	CHECK(group_member_name("Feedback A", "Channel_A") == "Feedback A");
	CHECK(group_member_name("Feedback A", "Chan.A") == "Feedback A");
}

TEST_CASE("Group member names: matching is case-sensitive") {
	CHECK(group_member_name("Add a voice", "Channel A") == "Add a voice");
	CHECK(group_member_name("red Speed", "Red") == "red Speed");
}

TEST_CASE("Group member names: a name is never emptied") {
	CHECK(group_member_name("Mix", "Mix") == "Mix");
	CHECK(group_member_name("Channel A", "Channel A") == "Channel A");
	CHECK(group_member_name("A Channel", "Channel A") == "A Channel");
}

TEST_CASE("Group member names: extra spaces") {
	CHECK(group_member_name("Red  Speed", "Red") == "Speed");
	CHECK(group_member_name(" Speed Red ", " Red  ") == "Speed");
	CHECK(group_member_name("Speed", "") == "Speed");
	CHECK(group_member_name("", "Red") == "");
}

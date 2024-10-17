#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"

namespace MetaModule
{

using FileStorageComm = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, IntercoreStorageMessage>;

}

#pragma once
#include "CoreModules/fs_access.hh"
#include "console/pr_dbg.hh"
#include "core_intercom/intercore_modulefs_message.hh"
#include "drivers/cache.hh"
#include "drivers/inter_core_comm.hh"
#include "util/overloaded.hh"
#include "util/padded_aligned.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

namespace StaticBuffers
{
extern IntercoreModuleFS::Message icc_module_fs_message_core0;
extern IntercoreModuleFS::Message icc_module_fs_message_core1;
extern std::array<uint8_t, 64 * 1024> module_fs_buffer_core0;
extern std::array<uint8_t, 64 * 1024> module_fs_buffer_core1;
} // namespace StaticBuffers

struct FS::Impl {
public:
	// Put these in separate place?
	std::string root;
	std::string cwd;
	std::span<char> file_buffer;

	Impl(std::string_view root)
		: root{root} {

		auto &backing_buffer =
			core() == 1 ? StaticBuffers::module_fs_buffer_core1 : StaticBuffers::module_fs_buffer_core0;

		file_buffer = {(char *)backing_buffer.data(), backing_buffer.size()};
	}

	template<typename ResponseT>
	std::optional<ResponseT> get_response_or_timeout(IntercoreModuleFS::Message const &message,
													 uint32_t timeout = 3000) {
		// Send
		auto start = HAL_GetTick();

		while (!send(message)) {

			if (HAL_GetTick() - start > 3000) {
				pr_dbg("Sending message timed out\n");
				return {}; //timeout
			}
		}

		// Get Response
		start = HAL_GetTick();

		while (true) {
			auto response = get_message();

			// Ignore empty messages
			if (response.index() != IntercoreModuleFS::Message{IntercoreModuleFS::None{}}.index()) {

				if (auto type_response = std::get_if<ResponseT>(&response))
					return std::optional<ResponseT>(*type_response);
				else {
					pr_err("ModFS: Got unexpected response type (%u -> %u)\n", message.index(), response.index());
					return std::optional<ResponseT>{};
				}
			}

			if (HAL_GetTick() - start > timeout) {
				pr_dbg("Waiting for response timed out\n");
				return {};
			}
		}

		return {};
	}

	std::string full_path(const char *path) {
		return root + cwd + path;
	}

private:
	static uint32_t core() {
		return __get_MPIDR() & 0b1;
	}

	static bool send(IntercoreModuleFS::Message const &message) {
		if (core() == 1)
			return comm_core1.send_message(message);
		else
			return comm_core0.send_message(message);
	}

	static IntercoreModuleFS::Message get_message() {
		if (core() == 1)
			return comm_core1.get_new_message();
		else
			return comm_core0.get_new_message();
	}

	static constexpr uint32_t IPCC_ChanCore0 = 2;
	static constexpr uint32_t IPCC_ChanCore1 = 3;

	using CommModuleFS0 =
		mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, IntercoreModuleFS::Message, IPCC_ChanCore0>;

	using CommModuleFS1 =
		mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Initiator, IntercoreModuleFS::Message, IPCC_ChanCore1>;

	static inline CommModuleFS0 comm_core0{StaticBuffers::icc_module_fs_message_core0};
	static inline CommModuleFS1 comm_core1{StaticBuffers::icc_module_fs_message_core1};
};

} // namespace MetaModule

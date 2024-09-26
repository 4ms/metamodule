#include "general_io.hh"

namespace MetaModule::FS
{

bool write_file(FileStorageProxy &proxy, std::string_view filedata, PatchLocation location) {
	return write_file(proxy, std::span<const char>{filedata.data(), filedata.size()}, location);
}

bool write_file(FileStorageProxy &proxy, std::string const &filedata, PatchLocation location) {
	return write_file(proxy, std::span<const char>{filedata.data(), filedata.length()}, location);
}

bool write_file(FileStorageProxy &proxy, std::span<const char> filedata, PatchLocation location) {
	// Copy into non-cacheable RAM:
	auto buffer = get_ram_buffer();
	std::memcpy(buffer.data(), filedata.data(), filedata.size());
	auto bufferc = std::span<char>{(char *)buffer.data(), filedata.size()};

	uint32_t timeout = get_time();
	while (proxy.request_write_file(bufferc, location.vol, location.filename) == FileStorageProxy::WriteResult::Busy) {
		if (get_time() - timeout > 1000) {
			pr_err("File write request not made in 1 second\n");
			return false;
		}
	}

	timeout = get_time();
	while (true) {
		auto msg = proxy.get_message();

		if (msg.message_type == FileStorageProxy::WriteFileOK) {
			pr_dbg("File written\n");
			return true;

		} else if (msg.message_type == FileStorageProxy::WriteFileFail) {
			pr_err("File write failed\n");
			return false;
		}

		if (get_time() - timeout > 4000) {
			pr_err("File write request not responded to in 4 seconds\n");
			return false;
		}
	}

	return true;
}

} // namespace MetaModule::FS

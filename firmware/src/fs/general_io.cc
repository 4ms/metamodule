#include "general_io.hh"
#include "delay.hh"
#include "memory/ram_buffer.hh"

namespace MetaModule::FS
{
static std::optional<IntercoreStorageMessage> wait_response(FileStorageProxy &proxy,
															IntercoreStorageMessage::MessageType MessageOK,
															IntercoreStorageMessage::MessageType MessageFail);

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

	return wait_response(proxy, FileStorageProxy::WriteFileOK, FileStorageProxy::WriteFileFail).has_value();
}

bool append_file(FileStorageProxy &proxy, std::string_view filedata, PatchLocation location) {
	// Copy into non-cacheable RAM:
	auto buffer = get_ram_buffer();
	std::memcpy(buffer.data(), filedata.data(), filedata.size());
	auto bufferc = std::span<char>{(char *)buffer.data(), filedata.size()};

	uint32_t timeout = get_time();
	while (proxy.request_append_file(bufferc, location.vol, location.filename) == FileStorageProxy::WriteResult::Busy) {
		if (get_time() - timeout > 1000) {
			pr_err("File write request not made in 1 second\n");
			return false;
		}
	}

	return wait_response(proxy, FileStorageProxy::WriteFileOK, FileStorageProxy::WriteFileFail).has_value();
}

std::optional<unsigned> file_size(FileStorageProxy &proxy, PatchLocation location) {
	uint32_t timeout = get_time();
	while (proxy.request_file_info(location.vol, location.filename) == false) {
		if (get_time() - timeout > 1000) {
			pr_err("File info request not made in 1 second\n");
			return false;
		}
	}

	const auto resp = wait_response(proxy, FileStorageProxy::FileInfoSuccess, FileStorageProxy::FileInfoFailed);
	if (resp) {
		return resp->length;
	} else {
		return {};
	}
}

std::optional<unsigned> read_file(FileStorageProxy &proxy, std::string &filedata, PatchLocation location) {

	uint32_t timeout = get_time();
	while (proxy.request_file_info(location.vol, location.filename) == false) {
		if (get_time() - timeout > 1000) {
			pr_err("File info request not made in 1 second\n");
			return {};
		}
	}

	if (auto msg = wait_response(proxy, FileStorageProxy::FileInfoSuccess, FileStorageProxy::FileInfoFailed)) {
		auto filesize = msg->length;

		// Read into non-cacheable RAM:
		auto buffer = get_ram_buffer();
		auto bufferc = std::span<char>{(char *)buffer.data(), filesize};

		uint32_t timeout = get_time();
		while (proxy.request_load_file(location.filename, location.vol, bufferc) == false) {
			if (get_time() - timeout > 3000) {
				pr_err("File read request not made in 3 seconds\n");
				return {};
			}
		}

		if (auto msg = wait_response(proxy, FileStorageProxy::LoadFileOK, FileStorageProxy::LoadFileFailed)) {
			if (msg->bytes_read != filesize) {
				pr_warn("File '%s' was read for %u bytes, but file size is %u bytes\n",
						location.filename.c_str(),
						msg->bytes_read,
						filesize);
			}
			filedata.clear();
			filedata.append(std::string_view{bufferc});
			filedata.append("\0"); // fail safe

			return msg->bytes_read;
		}

		else
			return {};

	} else
		return {};
}

static std::optional<IntercoreStorageMessage> wait_response(FileStorageProxy &proxy,
															IntercoreStorageMessage::MessageType MessageOK,
															IntercoreStorageMessage::MessageType MessageFail) {
	uint32_t timeout = get_time();
	while (true) {
		auto msg = proxy.get_message();

		if (msg.message_type == MessageOK) {
			return msg;

		} else if (msg.message_type == MessageFail) {
			pr_err("File request failed (%u)\n", (unsigned)msg.message_type);
			return {};
		}

		if (get_time() - timeout > 4000) {
			pr_err("File request not responded to in 4 seconds\n");
			return {};
		}
	}

	return {};
}

} // namespace MetaModule::FS

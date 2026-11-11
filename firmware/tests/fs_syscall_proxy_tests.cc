#include "doctest.h"
#include "fs/syscall/fs_syscall_proxy.hh"
#include <algorithm>
#include <span>
#include <vector>

// FsSyscallProxy is built against tests/stubs/fs_proxy.hh, which answers
// Read requests from FakeM4::file instead of sending them to the M4 core.

namespace
{

using MetaModule::FakeM4;
using MetaModule::FsSyscallProxy;

// Size of the buffer shared with the M4: the most that one request can read
const size_t ChunkSize = MetaModule::FsProxy::file_buffer().size();

void make_file(size_t size) {
	FakeM4::file.resize(size);
	for (size_t i = 0; i < size; i++)
		FakeM4::file[i] = (char)((i * 2654435761u) >> 13);
	FakeM4::reset();
}

} // namespace

TEST_CASE("FsSyscallProxy::read with file and buffer sizes around the chunk size") {
	FsSyscallProxy proxy;

	const size_t file_sizes[] = {
		0,
		1,
		ChunkSize - 1,
		ChunkSize,
		ChunkSize + 1,
		2 * ChunkSize - 1,
		2 * ChunkSize,
		2 * ChunkSize + 1,
		5 * ChunkSize + 777,
	};

	const size_t buffer_sizes[] = {
		0,
		1,
		4096,
		ChunkSize - 1,
		ChunkSize,
		ChunkSize + 1,
		2 * ChunkSize,
		3 * ChunkSize + 5,
		6 * ChunkSize,
	};

	for (auto file_size : file_sizes) {
		for (auto buffer_size : buffer_sizes) {
			CAPTURE(file_size);
			CAPTURE(buffer_size);

			make_file(file_size);
			FIL fil{};

			// Extra bytes at the end detect writes past the caller's buffer
			const char untouched = 0x55;
			std::vector<char> buffer(buffer_size + 16, untouched);

			auto bytes_read = proxy.read(&fil, std::span{buffer.data(), buffer_size});
			auto expected = std::min(file_size, buffer_size);

			REQUIRE(bytes_read.has_value());
			CHECK(*bytes_read == expected);
			CHECK(fil.fptr == expected);
			CHECK(std::equal(buffer.begin(), buffer.begin() + expected, FakeM4::file.begin()));

			// Nothing is written past what was reported as read
			CHECK(std::all_of(buffer.begin() + expected, buffer.end(), [=](char c) { return c == untouched; }));

			// No request is larger than the shared buffer
			CHECK(FakeM4::max_request <= ChunkSize);
		}
	}
}

TEST_CASE("FsSyscallProxy::read continues where the previous read stopped") {
	FsSyscallProxy proxy;
	make_file(5 * ChunkSize + 777);

	FIL fil{};
	std::vector<char> contents;
	std::vector<char> buffer(2 * ChunkSize + 3);

	while (true) {
		auto bytes_read = proxy.read(&fil, buffer);
		REQUIRE(bytes_read.has_value());
		if (*bytes_read == 0)
			break;
		contents.insert(contents.end(), buffer.begin(), buffer.begin() + *bytes_read);
	}

	CHECK(contents == FakeM4::file);
}

TEST_CASE("FsSyscallProxy::read of zero bytes does not send a request") {
	FsSyscallProxy proxy;
	make_file(100);

	FIL fil{};
	auto bytes_read = proxy.read(&fil, std::span<char>{});

	REQUIRE(bytes_read.has_value());
	CHECK(*bytes_read == 0);
	CHECK(FakeM4::read_calls == 0);
}

TEST_CASE("FsSyscallProxy::read fails if the first chunk times out") {
	FsSyscallProxy proxy;
	make_file(3 * ChunkSize);
	FakeM4::timeout_on_call = 1;

	FIL fil{};
	std::vector<char> buffer(3 * ChunkSize);

	CHECK_FALSE(proxy.read(&fil, buffer).has_value());
	CHECK(fil.fptr == 0);
}

TEST_CASE("FsSyscallProxy::read returns what it has if a later chunk times out") {
	FsSyscallProxy proxy;
	make_file(3 * ChunkSize);
	FakeM4::timeout_on_call = 2;

	FIL fil{};
	std::vector<char> buffer(3 * ChunkSize);

	auto bytes_read = proxy.read(&fil, buffer);
	REQUIRE(bytes_read.has_value());
	CHECK(*bytes_read == ChunkSize);

	// File position matches what was returned, so the caller can carry on
	CHECK(fil.fptr == ChunkSize);

	// Reading the remainder (as newlib does after a short read) completes the file
	auto more_bytes_read = proxy.read(&fil, std::span{buffer}.subspan(*bytes_read));
	REQUIRE(more_bytes_read.has_value());
	CHECK(*bytes_read + *more_bytes_read == 3 * ChunkSize);
	CHECK(buffer == FakeM4::file);
}

TEST_CASE("FsSyscallProxy::read fails if the first chunk has a disk error") {
	FsSyscallProxy proxy;
	make_file(3 * ChunkSize);
	FakeM4::diskerr_on_call = 1;

	FIL fil{};
	std::vector<char> buffer(3 * ChunkSize);

	// An error, not a read of 0 bytes (which would mean end of file)
	CHECK_FALSE(proxy.read(&fil, buffer).has_value());

	// The error is kept in the FIL, so FatFS refuses later reads of it
	CHECK(fil.err == FR_DISK_ERR);

	// No more requests are sent after the error
	CHECK(FakeM4::read_calls == 1);
}

TEST_CASE("FsSyscallProxy::read returns what it has if a later chunk has a disk error") {
	FsSyscallProxy proxy;
	make_file(3 * ChunkSize);
	FakeM4::diskerr_on_call = 2;

	FIL fil{};
	std::vector<char> buffer(3 * ChunkSize);

	auto bytes_read = proxy.read(&fil, buffer);
	REQUIRE(bytes_read.has_value());
	CHECK(*bytes_read == ChunkSize);
	CHECK(std::equal(buffer.begin(), buffer.begin() + ChunkSize, FakeM4::file.begin()));

	// No more requests are sent after the error
	CHECK(FakeM4::read_calls == 2);
}

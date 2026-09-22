#pragma once
#include "console/console_buffer_reader.hh"
#include "core_intercom/shared_memory.hh"
#include "usb/dev_drive_block.hh"
#include <array>
#include <cstdio>
#include <string_view>

namespace MetaModule
{

// Line-based commands typed (or scripted) into the USB console.
class ConsoleCommands {
public:
	explicit ConsoleCommands(ConsoleBufferReader &reader)
		: reader_{reader} {
	}

	// Feed received console bytes. Returns true if the byte completed a line.
	bool put(uint8_t c) {
		if (c == '\r' || c == '\n') {
			if (len_ > 0) {
				dispatch(std::string_view{line_.data(), len_});
				len_ = 0;
				return true;
			}
			return false;
		}

		if (len_ < line_.size())
			line_[len_++] = (char)c;
		else
			len_ = 0; // overlong line: drop it rather than split it in two

		return false;
	}

private:
	void dispatch(std::string_view cmd) {
		// Case-insensitive compare against a literal
		auto is = [cmd](std::string_view name) {
			if (cmd.size() != name.size())
				return false;
			for (size_t i = 0; i < cmd.size(); i++) {
				auto a = cmd[i] >= 'a' && cmd[i] <= 'z' ? cmd[i] - 32 : cmd[i];
				if (a != name[i])
					return false;
			}
			return true;
		};

		if (is("INSTALL") || is("SCAN"))
			send(DevDriveCommand::Install);

		else if (is("EJECT"))
			send(DevDriveCommand::Eject);

		else if (is("MOUNT"))
			send(DevDriveCommand::Mount);

		else if (is("STATUS"))
			send(DevDriveCommand::Status);

		else if (is("COL"))
			reader_.set_color(true);

		else if (is("MONO"))
			reader_.set_color(false);

		else if (is("HELP") || is("?"))
			print_help();

		else
			printf("Unknown command '%.*s'. Type help for a list.\n", (int)cmd.size(), cmd.data());
	}

	static void send(DevDriveCommand cmd) {
		if (auto *block = SharedMemoryS::ptrs.dev_drive_msgs)
			block->send_command(cmd);
		else
			printf("Developer drive is not available\n");
	}

	static void print_help() {
		printf("Commands:\n"
			   "  install  install any .mmplugin files on the developer drive,\n"
			   "           then give the drive back to the host\n"
			   "  eject    remove the drive from the host\n"
			   "  mount    give the drive back to the host\n"
			   "  status   report the developer drive state\n"
			   "  col      console color on\n"
			   "  mono     console color off (default)\n"
			   "\n"
			   "From your OS, unmount the volume on the host before install\n");
	}

	ConsoleBufferReader &reader_;
	std::array<char, 32> line_{};
	size_t len_ = 0;
};

} // namespace MetaModule

#pragma once
#include "console/console_buffer_reader.hh"
#include "console/uart_log.hh"
#include "core_intercom/shared_memory.hh"
#include "usb/dev_drive_block.hh"
#include <array>
#include <cstdio>
#include <cstring>
#include <string_view>

namespace MetaModule
{

// Line-based commands typed (or scripted) into the USB console.
class ConsoleCommands {
public:
	ConsoleCommands(ConsoleBufferReader &reader, DevDriveBlock &dev_drive_msgs)
		: reader_{reader}
		, message_block{dev_drive_msgs} {
	}

	// Feed received console bytes, echoing them back. Returns true if the byte completed a line.
	bool put(uint8_t c) {
		// Swallow the LF of a CRLF, so it doesn't count as a second (empty) line
		const bool after_cr = last_was_cr_;
		last_was_cr_ = (c == '\r');
		if (c == '\n' && after_cr)
			return false;

		if (skip_escape(c))
			return false;

		if (c == '\r' || c == '\n') {
			echo("\n");
			const bool had_cmd = len_ > 0;
			if (had_cmd)
				dispatch(std::string_view{line_.data(), len_});
			len_ = 0;
			print_prompt();
			return had_cmd;
		}

		if (c == '\b' || c == 0x7F) {
			if (len_ > 0) {
				len_--;
				echo("\b \b");
			}
			return false;
		}

		// Ignore other control bytes, and anything past the line limit
		if (c < 0x20 || c > 0x7E || len_ >= line_.size())
			return false;

		line_[len_++] = (char)c;
		const char s[2] = {(char)c, '\0'};
		echo(s);
		return false;
	}

	void print_prompt() {
		if (reader_.using_color())
			echo(Term::Red);
		echo("> ");
		if (reader_.using_color())
			echo(Term::Normal);
	}

private:
	// Consume terminal escape sequences (arrow keys, etc) rather than storing and echoing them.
	// Returns true if c was part of one.
	bool skip_escape(uint8_t c) {
		switch (esc_) {
			case Esc::None:
				if (c != 0x1B)
					return false;
				esc_ = Esc::Start;
				return true;

			case Esc::Start:
				// ESC [ ... and ESC O x are multi-byte; other ESC x sequences are just two bytes
				esc_ = (c == '[') ? Esc::Csi : (c == 'O') ? Esc::Ss3 : Esc::None;
				return true;

			case Esc::Csi:
				// Parameter bytes until a final byte in 0x40-0x7E
				if (c >= 0x40 && c <= 0x7E)
					esc_ = Esc::None;
				return true;

			case Esc::Ss3:
				esc_ = Esc::None;
				return true;
		}
		return false;
	}

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

	uint32_t send(DevDriveCommand cmd) {
		return message_block.send_command(cmd);
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

	// Bypass stdio: its buffer isn't safe to use from the USB ISR on every keystroke,
	// and would hold back partial lines (echo, prompt) until a newline
	static void echo(const char *s) {
		UartLog::write_stdout(s, strlen(s));
	}

	ConsoleBufferReader &reader_;
	std::array<char, 32> line_{};
	size_t len_ = 0;
	bool last_was_cr_ = false;
	DevDriveBlock &message_block;

	enum class Esc { None, Start, Csi, Ss3 };
	Esc esc_ = Esc::None;
};

} // namespace MetaModule

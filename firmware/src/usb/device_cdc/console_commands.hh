#pragma once
#include "console/console_buffer_reader.hh"
#include "console/uart_log.hh"
#include "usb/dev_drive_block.hh"
#include "util/static_string.hh"
#include <atomic>
#include <cstdio>
#include <cstring>
#include <optional>
#include <string_view>

namespace MetaModule
{

// Line-based commands typed (or scripted) into the USB console.
//
// The console output from each core goes through a separate buffer, and the
// buffers are interleaved in no particular order. Keystrokes are echoed and the
// prompt is printed by the M4, but some commands are carried out (and their
// output printed) by the A7. To keep the output in order, a command runs in
// these steps:
//   put() (USB ISR): echo chars and keep track of the command
//   process() (main loop):
//     - run the command, or send it to the A7 and wait for it to finish
//     - print the prompt
class ConsoleCommands {
public:
	ConsoleCommands(ConsoleBufferReader &reader, DevDriveBlock &dev_drive_msgs)
		: reader_{reader}
		, message_block{dev_drive_msgs} {
	}

	// Feed received console bytes, echoing them back. Queues a command if found.
	// Called from the USB ISR.
	void put(uint8_t c) {
		// Swallow the LF of a CRLF, so it doesn't count as a second (empty) line
		const bool after_cr = last_was_cr_;
		last_was_cr_ = (c == '\r');
		if (c == '\n' && after_cr)
			return;

		if (skip_escape(c))
			return;

		if (c == '\r' || c == '\n') {
			echo("\n");
			if (state_ != State::Idle) {
				echo("Busy, try again.\n");

			} else {
				// Command received: store it for process() to handle
				cmd_ = line_;
				state_ = State::IssuingCommand;
			}
			line_.clear();
			return;
		}

		// Backspace
		if (c == '\b' || c == 0x7F) {
			if (line_.pop()) {
				echo("\b \b");
			}
			return;
		}

		// Ignore other control bytes
		if (c < 0x20 || c > 0x7E)
			return;

		// Echo character back if it's not past the line limit
		if (line_.append((char)c)) {
			const char s[2] = {(char)c, '\0'};
			echo(s);
		}
	}

	void print_prompt() {
		if (reader_.using_color())
			echo(Term::Red);
		echo("> ");
		if (reader_.using_color())
			echo(Term::Normal);
	}

	// Dispatch commands queued by put()
	void process(uint32_t now_ms) {
		switch (state_) {
			case State::Idle:
				break;

			case State::IssuingCommand: {
				if (auto sent = dispatch(cmd_)) {
					// Keep track of the command count, so we hold off on showing the prompt until it completed
					sent_count_ = *sent;
					sent_time_ = now_ms;
					state_ = State::WaitCommandComplete;
				} else
					finish();
			} break;

			case State::WaitCommandComplete: {
				if (message_block.is_command_done(sent_count_)) {
					finish();
				} else if (now_ms - sent_time_ > CommandTimeout) {
					echo("Command Timed out\n");
					finish();
				}
			} break;
		}
	}

private:
	void finish() {
		fflush(stdout); // command output from printf() must go before the prompt
		print_prompt();
		state_ = State::Idle;
	}

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

	// Runs the command. If it was sent to the A7, returns the count to wait for.
	std::optional<uint32_t> dispatch(std::string_view cmd) {
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
			return send(DevDriveCommand::Install);

		else if (is("EJECT"))
			return send(DevDriveCommand::Eject);

		else if (is("MOUNT"))
			return send(DevDriveCommand::Mount);

		else if (is("STATUS"))
			return send(DevDriveCommand::Status);

		else if (is("COL"))
			reader_.set_color(true);

		else if (is("MONO"))
			reader_.set_color(false);

		else if (is("HELP") || is("?"))
			print_help();

		else if (cmd.size() > 0)
			printf("Unknown command '%.*s'. Type help or ? for a list.\n", (int)cmd.size(), cmd.data());

		return std::nullopt;
	}

	uint32_t send(DevDriveCommand cmd) {
		return message_block.send_command(cmd);
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

	// Bypass stdio: its buffer isn't safe to use from the USB ISR on every keystroke
	static void echo(const char *s) {
		UartLog::write_stdout(s, strlen(s));
	}

	ConsoleBufferReader &reader_;
	StaticString<31> line_{};
	bool last_was_cr_ = false;

	enum class State { Idle, IssuingCommand, WaitCommandComplete };
	std::atomic<State> state_ = State::Idle;
	StaticString<31> cmd_{};

	uint32_t sent_count_{};
	uint32_t sent_time_{};
	static constexpr uint32_t CommandTimeout = 10000;

	DevDriveBlock &message_block;

	enum class Esc { None, Start, Csi, Ss3 };
	Esc esc_ = Esc::None;
};

} // namespace MetaModule

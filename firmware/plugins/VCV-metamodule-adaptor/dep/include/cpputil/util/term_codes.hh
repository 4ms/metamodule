#pragma once

struct Term {
	static constexpr const char *Normal = "\x1b[0m";

	static constexpr const char *Black = "\x1b[30m";
	static constexpr const char *Red = "\x1b[31m";
	static constexpr const char *Green = "\x1b[32m";
	static constexpr const char *Yellow = "\x1b[33m";
	static constexpr const char *Blue = "\x1b[34m";
	static constexpr const char *Magenta = "\x1b[35m";
	static constexpr const char *Cyan = "\x1b[36m";
	static constexpr const char *White = "\x1b[37m";

	static constexpr const char *BoldBlack = "\x1b[30;1m";
	static constexpr const char *BoldRed = "\x1b[31;1m";
	static constexpr const char *BoldGreen = "\x1b[32;1m";
	static constexpr const char *BoldYellow = "\x1b[33;1m";
	static constexpr const char *BoldBlue = "\x1b[34;1m";
	static constexpr const char *BoldMagenta = "\x1b[35;1m";
	static constexpr const char *BoldCyan = "\x1b[36;1m";
	static constexpr const char *BoldWhite = "\x1b[37;1m";

	static constexpr const char *BlinkBlack = "\x1b[30;5m";
	static constexpr const char *BlinkRed = "\x1b[31;5m";
	static constexpr const char *BlinkGreen = "\x1b[32;5m";
	static constexpr const char *BlinkYellow = "\x1b[33;5m";
	static constexpr const char *BlinkBlue = "\x1b[34;5m";
	static constexpr const char *BlinkMagenta = "\x1b[35;5m";
	static constexpr const char *BlinkCyan = "\x1b[36;5m";
	static constexpr const char *BlinkWhite = "\x1b[37;5m";

	static constexpr const char *Bold = "\x1b[1m";
	static constexpr const char *Blink = "\x1b[5m";

	static constexpr const char *JumpLineStart = "\x1b[0G";
	static constexpr const char *ClearLine = "\x1b[2K";
	static constexpr const char *ClearScreen = "\x1b[2J";
	static constexpr const char *SaveCursorPos = "\x1b[s";
	static constexpr const char *RestoreCursorPos = "\x1b[u";
};

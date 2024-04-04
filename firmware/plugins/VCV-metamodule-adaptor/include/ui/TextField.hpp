#pragma once
#include <context.hpp>
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct TextField : widget::OpaqueWidget {
	std::string text;
	std::string placeholder;

	bool password = false;
	bool multiline = false;
	int cursor = 0;
	int selection = 0;

	Widget *prevField = nullptr;
	Widget *nextField = nullptr;

	virtual int getTextPosition(math::Vec mousePos) {
		return 0;
	}

	std::string getText() {
		return text;
	}
	void setText(std::string text) {
		this->text = text;
	}
	void selectAll() {
	}
	std::string getSelectedText() {
		return text;
	}
	void insertText(std::string text) {
		setText(text);
	}
	void copyClipboard() {
	}
	void cutClipboard() {
	}
	void pasteClipboard() {
	}
	void cursorToPrevWord() {
	}
	void cursorToNextWord() {
	}
	void createContextMenu() {
	}
};

struct PasswordField : TextField {
	PasswordField() {
		password = true;
	}
};

} // namespace rack::ui

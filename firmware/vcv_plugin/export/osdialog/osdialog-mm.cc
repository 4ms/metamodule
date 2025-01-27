#include "lvgl.h"
#include "util/static_string.hh"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <osdialog.h>
#include <vector>

int osdialog_message(osdialog_message_level level, osdialog_message_buttons buttons, const char *message) {
	// return 1; // clicked Yes/OK
	return 0; // clicked No/Cancel
}

char *osdialog_prompt(osdialog_message_level level, const char *message, const char *text) {
	return nullptr;
}

char *osdialog_file(osdialog_file_action action, const char *path, const char *filename, osdialog_filters *filters) {
	if (action == OSDIALOG_OPEN) {
		printf("Open file dialog box\n");
	} else if (action == OSDIALOG_OPEN_DIR) {
		printf("Open dir dialog box\n");
	} else if (action == OSDIALOG_SAVE) {
		printf("Save file dialog box -- not supported\n");
	}

	std::vector<StaticString<8>> exts;
	for (; filters; filters = filters->next) {
		for (osdialog_filter_patterns *patterns = filters->patterns; patterns; patterns = patterns->next) {
			exts.push_back(std::string_view{patterns->pattern}); //automatically truncated and null-terminated
			printf("Filter: %s\n", exts.back().c_str());
		}
	}

	//open file browser

	// Caller will free() the returned ptr if it's not null
	return nullptr;
}

int osdialog_color_picker(osdialog_color *color, int opacity) {
	return 0;
}

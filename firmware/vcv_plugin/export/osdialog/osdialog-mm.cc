#include <cstddef>
#include <cstring>
#include <osdialog.h>

int osdialog_message(osdialog_message_level level, osdialog_message_buttons buttons, const char *message) {
	// return 1; // clicked Yes/OK
	return 0; // clicked No/Cancel
}

char *osdialog_prompt(osdialog_message_level level, const char *message, const char *text) {
	return nullptr;
}

char *osdialog_file(osdialog_file_action action, const char *path, const char *filename, osdialog_filters *filters) {
	return nullptr;
}

int osdialog_color_picker(osdialog_color *color, int opacity) {
	return 0;
}

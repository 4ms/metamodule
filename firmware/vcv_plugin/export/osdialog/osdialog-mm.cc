#include <osdialog.h>
#include <string>

std::string stringify_osdialog_filters(osdialog_filters *filters) {
	std::string exts;
	for (; filters; filters = filters->next) {
		for (osdialog_filter_patterns *patterns = filters->patterns; patterns; patterns = patterns->next) {
			if (exts.length() > 0)
				exts += ", ";
			exts += std::string(".") + patterns->pattern;
		}
	}
	printf("Filter: %s\n", exts.c_str());
	return exts;
}

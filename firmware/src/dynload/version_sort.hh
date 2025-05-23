#pragma once
#include "dynload//plugin_file_list.hh"
#include "util/string_compare.hh"
#include "util/version_tools.hh"

namespace MetaModule
{

// Compare plugins, showing them alphabetically by plugin name, and then
// if there are multiple versions for a plugin name, sort newest to oldest by version.
//
// Returns true if `a` should be shown in a list above `b`:
// - true if a's plugin name is alphabetically before b's
// - true if the plugin names are equal and a's version is LATER than b's
//
// Uses definition of Precedence in SemVer: https://semver.org/#spec-item-11
// Except we're not strict about section 11.4. TODO: follow section 11.4 strictly
//
inline bool alpha_then_newest_version(PluginFile const &a, PluginFile const &b) {
	if (a.plugin_name == b.plugin_name) {
		// sort by version, newest first
		auto vers_a = VersionUtil::Version(a.version_in_filename);
		auto vers_b = VersionUtil::Version(b.version_in_filename);
		if (vers_a == vers_b) {
			// versions are equal. See if exactly one has a suffix: if so, then it's older

			if (vers_a.is_normal && !vers_b.is_normal) {
				// b has suffix but not a, so a should be shown above b
				return true;

			} else if (!vers_a.is_normal && vers_b.is_normal) {
				// a has suffix but not b, so b should be shown above a
				return false;

			} else {
				// Both or neither have suffixes, so show the lexically later one.
				// Return true if a is lexically after b (e.g. "dev-13" is after "dev-12")
				// meaning we should show a above b (dev-13 is newer).
				// This also means "fw-X.X" will show above (newer) than "dev-ZZ", since "f" is after "d"
				return less_ci(b.version_in_filename, a.version_in_filename);
			}
		} else
			return vers_a > vers_b;

		return true;
	} else
		return less_ci(a.plugin_name, b.plugin_name);
}

} // namespace MetaModule

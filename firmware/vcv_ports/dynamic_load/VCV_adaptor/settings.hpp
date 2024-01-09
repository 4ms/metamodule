#pragma once
#include "color.hpp"
#include "common.hpp"
#include "json.hpp"
#include "math.hpp"
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <vector>

namespace rack
{

struct settings {

	// Runtime state, not serialized.

	/** Path to settings.json */
	// static inline std::string settingsPath;
	static inline bool devMode;
	static inline bool headless;
	static inline bool isPlugin;

	// Persistent state, serialized to settings.json.

	/** Launches Rack without loading plugins or the autosave patch. Always set to false when settings are saved. */
	static inline bool safeMode;
	/** vcvrack.com user token */
	static inline std::string token;
	/** Whether the window is maximized */
	static inline bool windowMaximized;
	/** Size of window in pixels */
	static inline math::Vec windowSize;
	/** Position in window in pixels */
	static inline math::Vec windowPos;
	/** Reverse the zoom scroll direction */
	static inline bool invertZoom;
	/** Ratio between UI pixel and physical screen pixel.
0 for auto.
*/
	static inline float pixelRatio;
	/** Name of UI theme, specified in ui::refreshTheme() */
	static inline std::string uiTheme;
	/** Opacity of cables in the range [0, 1] */
	static inline float cableOpacity;
	/** Straightness of cables in the range [0, 1]. Unitless and arbitrary. */
	static inline float cableTension;
	static inline float rackBrightness;
	static inline float haloBrightness;
	/** Allows rack to hide and lock the cursor position when dragging knobs etc. */
	static inline bool allowCursorLock;
	enum KnobMode {
		KNOB_MODE_LINEAR,
		KNOB_MODE_SCALED_LINEAR,
		KNOB_MODE_ROTARY_ABSOLUTE,
		KNOB_MODE_ROTARY_RELATIVE,
	};
	static inline KnobMode knobMode;
	static inline bool knobScroll;
	static inline float knobLinearSensitivity;
	static inline float knobScrollSensitivity;
	static inline float sampleRate;
	static inline int threadCount;
	static inline bool tooltips;
	static inline bool cpuMeter;
	static inline bool lockModules;
	static inline bool squeezeModules;
	static inline bool preferDarkPanels;
	/** Maximum screen redraw frequency in Hz, or 0 for unlimited. */
	static inline float frameRateLimit;
	/** Interval between autosaves in seconds. */
	static inline float autosaveInterval;
	static inline bool skipLoadOnLaunch;
	static inline std::list<std::string> recentPatchPaths;
	static inline std::vector<NVGcolor> cableColors;
	static inline bool autoCheckUpdates;
	static inline bool showTipsOnLaunch;
	static inline int tipIndex;
	enum BrowserSort {
		BROWSER_SORT_UPDATED,
		BROWSER_SORT_LAST_USED,
		BROWSER_SORT_MOST_USED,
		BROWSER_SORT_BRAND,
		BROWSER_SORT_NAME,
		BROWSER_SORT_RANDOM,
	};
	static inline BrowserSort browserSort;
	static inline float browserZoom;
	static inline json_t *pluginSettingsJ;

	struct ModuleInfo {
		bool enabled = true;
		bool favorite = false;
		int added = 0;
		double lastAdded = NAN;
	};
	/** pluginSlug -> (moduleSlug -> ModuleInfo) */
	static inline std::map<std::string, std::map<std::string, ModuleInfo>> moduleInfos;
	/** Returns a ModuleInfo if exists for the given slugs.
*/
	ModuleInfo *getModuleInfo(const std::string &pluginSlug, const std::string &moduleSlug);

	/** The VCV JSON API returns the data structure
{pluginSlug: [moduleSlugs] or true}
where "true" represents that the user is subscribed to the plugin (all modules and future modules).
C++ isn't weakly typed, so we need the PluginWhitelist data structure to store this information.
*/
	struct PluginWhitelist {
		bool subscribed = false;
		std::set<std::string> moduleSlugs;
	};
	static inline std::map<std::string, PluginWhitelist> moduleWhitelist;

	bool isModuleWhitelisted(const std::string &pluginSlug, const std::string &moduleSlug);

	// PRIVATE void init();
	// PRIVATE void destroy();
	// PRIVATE json_t *toJson();
	// PRIVATE void fromJson(json_t *rootJ);
	// PRIVATE void save(std::string path = "");
	// PRIVATE void load(std::string path = "");
};

} // namespace rack

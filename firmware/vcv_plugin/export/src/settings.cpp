#include <settings.hpp>

namespace rack::settings
{

// Runtime state

std::string settingsPath = "";
bool devMode = false;
bool headless = true;
bool isPlugin = false;

// Persistent state

bool safeMode{};
std::string token{};
bool windowMaximized{};
math::Vec windowSize{};
math::Vec windowPos{};
bool invertZoom{};
float pixelRatio{};
std::string uiTheme{};
float cableOpacity{};
float cableTension{};
float rackBrightness{};
float haloBrightness{};
bool allowCursorLock{};
KnobMode knobMode{};
bool knobScroll{};
float knobLinearSensitivity{};
float knobScrollSensitivity{};
float sampleRate{};
int threadCount{};
bool tooltips{};
bool cpuMeter{};
bool lockModules{};
bool squeezeModules{};
bool preferDarkPanels{};
float frameRateLimit{};
float autosaveInterval{};
bool skipLoadOnLaunch{};
std::list<std::string> recentPatchPaths{};
std::vector<NVGcolor> cableColors{};
bool autoCheckUpdates{};
bool showTipsOnLaunch{};
int tipIndex{};
BrowserSort browserSort{};
float browserZoom{};
json_t *pluginSettingsJ{};
std::map<std::string, std::map<std::string, ModuleInfo>> moduleInfos;
ModuleInfo *getModuleInfo(const std::string &pluginSlug, const std::string &moduleSlug) {
	return {};
}
std::map<std::string, PluginWhitelist> moduleWhitelist;
bool isModuleWhitelisted(const std::string &pluginSlug, const std::string &moduleSlug) {
	return false;
};

} // namespace rack::settings

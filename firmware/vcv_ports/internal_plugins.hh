#include "plugin/Plugin.hpp"

extern rack::plugin::Plugin *pluginInstance;

// This can be used by the internal plugin if they need to load from their plugin files after startup
extern rack::plugin::Plugin *internalPluginInstance;

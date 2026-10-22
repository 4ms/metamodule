#pragma once

// Plugin files' extension. A macro, so it can be part of string literals.
// MP2 plugins (AArch64) aren't MP1 plugins, so they have their own extension: the plugin SDK makes
// both from one build (MyPlugin.mmplugin and MyPlugin.mm2plugin).
#define PLUGIN_FILE_EXTENSION ".mm2plugin"

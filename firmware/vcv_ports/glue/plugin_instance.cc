namespace rack::plugin
{
struct Plugin;
}

// This is used for internal plugins. It's set to the current plugin instance while loading the internal plugin
// It's a workaround for the fact that internal plugins can't all have their own global symbol of this name.
// We need it when the internal plugin loads an asset, because it needs to know what dir to look in (which is stored in Plugin)
rack::plugin::Plugin *pluginInstance;

namespace rack::plugin
{
struct Plugin;
}

// This is used for internal plugins. It's set to the current plugin instance while loading the internal plugin
// It's a workaround for the fact that internal plugins can't all have their own global symbol of this name.
// We need it when the internal plugin loads an asset, because it needs to know what dir to look in (which is stored in Plugin)
rack::plugin::Plugin *pluginInstance;

// These are optionally used by the plugins if they need to refer to their instance after the
// plugin is loaded (i.e. while a module is running)
rack::plugin::Plugin *befacoPluginInstance;
rack::plugin::Plugin *audibleInstrumentsPluginInstance;
rack::plugin::Plugin *hetrickcvPluginInstance;
rack::plugin::Plugin *nonlinearcircuitsPluginInstance;
rack::plugin::Plugin *eightfoldPluginInstance;
rack::plugin::Plugin *valleyPluginInstance;
rack::plugin::Plugin *rackCorePluginInstance;

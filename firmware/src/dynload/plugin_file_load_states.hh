#pragma once

namespace MetaModule
{

enum class PluginFileLoaderState {
	NotInit,
	Error,
	InvalidPlugin,
	RamDiskFull,
	Idle,
	RequestList,
	WaitingForList,
	GotList,
	PrepareForReadingPlugin,
	RequestReadPlugin,
	LoadingPlugin,
	UntarPlugin,
	ProcessingPlugin,
	Success
};

} // namespace MetaModule

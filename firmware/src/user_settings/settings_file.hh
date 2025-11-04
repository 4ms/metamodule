#pragma once
#include "patch_file/file_storage_proxy.hh"
#include "user_settings/settings.hh"

namespace MetaModule::Settings
{

bool write_settings(FileStorageProxy &proxy, UserSettings const &settings, Volume vol = Volume::NorFlash);
bool read_settings(FileStorageProxy &proxy, UserSettings *settings, Volume vol = Volume::NorFlash);

} // namespace MetaModule::Settings

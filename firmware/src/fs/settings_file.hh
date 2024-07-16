#pragma once
#include "gui/pages/view_settings.hh"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule::Settings
{

bool write_settings(FileStorageProxy &proxy, ViewSettings const &settings);
bool read_settings(FileStorageProxy &proxy, ViewSettings *settings);

} // namespace MetaModule::Settings

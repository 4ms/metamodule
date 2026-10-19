#pragma once
// Headers MP1's fs_proxy.hh provides, which src/fs/syscall relies on
#include <cstring>
#include <optional>
#include <span>
#include <string_view>

// STUB: stands in for src/core_a7/fs_proxy.hh, the A7's side of the file access messages to the M4
// (IntercoreModuleFS). See core_a35/fs_syscall_proxy.cc.
namespace MetaModule
{
struct FsProxy {};
} // namespace MetaModule

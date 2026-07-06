#pragma once
#include "core_intercom/intercore_modulefs_message.hh"
#include "ff.h"

// The filesystem core (M4/M33) owns all FatFs FIL/DIR state; this core
// addresses those objects by FsHandle. Callers on this core hold FIL/DIR
// purely as opaque storage: we stash the handle and the last-known file state
// inside the existing fields, so the layout (and the plugin-facing File/Dir
// wrappers in ff_host.hh) is unchanged and local reads keep working with no
// round-trip:
//   obj.sclust           <- the FsHandle
//   obj.fs               <- non-null while open (preserves is_reset())
//   fptr / obj.objsize / err <- cached FsFileState (f_tell/f_size/f_eof/f_error)

namespace MetaModule::FsHandleCache
{

inline IntercoreModuleFS::FsHandle handle(const FIL &fil) {
	return fil.obj.sclust;
}

inline IntercoreModuleFS::FsHandle handle(const DIR &dir) {
	return dir.obj.sclust;
}

inline void update_state(FIL &fil, const IntercoreModuleFS::FsFileState &state) {
	fil.fptr = state.fptr;
	fil.obj.objsize = state.objsize;
	fil.err = state.err;
}

inline void set_open(FIL &fil, IntercoreModuleFS::FsHandle h, const IntercoreModuleFS::FsFileState &state) {
	fil.obj.sclust = h;
	fil.obj.fs = (h == IntercoreModuleFS::InvalidFsHandle) ? nullptr : reinterpret_cast<FATFS *>(&fil);
	update_state(fil, state);
}

inline void set_closed(FIL &fil) {
	fil.obj.fs = nullptr;
	fil.obj.sclust = IntercoreModuleFS::InvalidFsHandle;
}

inline void set_open(DIR &dir, IntercoreModuleFS::FsHandle h) {
	dir.obj.sclust = h;
	dir.obj.fs = (h == IntercoreModuleFS::InvalidFsHandle) ? nullptr : reinterpret_cast<FATFS *>(&dir);
}

inline void set_closed(DIR &dir) {
	dir.obj.fs = nullptr;
	dir.obj.sclust = IntercoreModuleFS::InvalidFsHandle;
}

} // namespace MetaModule::FsHandleCache

#pragma once
#include "CoreModules/CoreProcessor.hh"

namespace MetaModule::BlockJobControl
{

// Engine side of BlockJob (threads/block_job.hh).
//
// Jobs run on a background runner on Core 2, at a priority below the per-frame
// module/cable interrupts, so they fill the time Core 2 would otherwise spend
// waiting for Core 1. The deadline is enforced by Core 1 at the start of each
// frame, while Core 2 is outside its frame interrupts and the runner can finish.

// Core 1: call at the start of each frame, before any module runs.
// Waits for any job that's due by this frame.
void begin_frame();

// The runner: runs the submitted job that's due soonest.
// Returns the module that owns it, or nullptr if no job was waiting.
CoreProcessor *run_next_job();

// Installs the function that wakes the runner when a job is submitted.
// Until one is installed, submit() runs the job immediately.
void set_runner_notify(void (*notify)());

// True if the module has created a BlockJob
bool has_block_job(CoreProcessor const *module);

} // namespace MetaModule::BlockJobControl

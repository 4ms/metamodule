#include "CoreModules/async_thread.hh"
#include "async_thread_control.hh"
#include "console/pr_dbg.hh"

namespace MetaModule
{

struct AsyncThread::Internal {
	std::optional<uint32_t> id = 0;

	Internal(std::optional<uint32_t> id)
		: id{id} {
	}
};

AsyncThread::AsyncThread(CoreProcessor *module)
	: internal{std::make_unique<Internal>(create_async_task(module))} {
}

AsyncThread::AsyncThread(CoreProcessor *module, Callback &&new_action)
	: action(std::move(new_action))
	, internal{std::make_unique<Internal>(create_async_task(module))} {
}

void AsyncThread::start() {
	if (internal->id) {
		if (auto task = get_task(*internal->id)) {
			pr_trace("Start task id %u on core %u\n", *internal->id, task->core_id);

			task->action = action;
			task->one_shot = false;
			task->enabled = true;
		}
	}
}

void AsyncThread::start(Callback &&new_action) {
	action = std::move(new_action);
	start();
}

void AsyncThread::run_once() {
	if (internal->id) {
		if (auto task = get_task(*internal->id)) {
			task->action = action;
			task->one_shot = true;
			task->enabled = true;

			pr_dbg("Run once task id %u core %u\n", *internal->id, task->core_id);
		}
	}
}

void AsyncThread::stop() {
	if (internal->id) {
		if (auto task = get_task(*internal->id)) {
			task->enabled = false;

			pr_trace("Stop task id %u on core %u\n", *internal->id, task->core_id);
		} else
			pr_err("Can't stop unknown task id %u\n", *internal->id);
	}
}

AsyncThread::~AsyncThread() {
	stop();
	if (internal->id)
		destroy_async_task(*internal->id);
}

bool AsyncThread::is_enabled() {
	if (internal->id) {
		if (auto task = get_task(*internal->id)) {
			return task->enabled;
		}
	}
	return false;
}

} // namespace MetaModule

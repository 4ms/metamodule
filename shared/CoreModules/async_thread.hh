#pragma once
#include "util/callable.hh"

namespace MetaModule
{

class AsyncThread {
public:
	AsyncThread(Callback &&action);
	AsyncThread();

	void start(unsigned module_id);
	void start(unsigned module_id, Callback &&action);

	~AsyncThread();

private:
	Callback action{};
	unsigned id{};
};

} // namespace MetaModule

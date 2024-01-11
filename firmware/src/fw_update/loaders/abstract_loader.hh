#pragma once

#include <util/static_string.hh>
#include <utility>
#include <span>

namespace MetaModule
{

class FileWorkerBase
{
public:
	enum class Error { None, Failed, Mismatch };

	virtual Error start();
	virtual std::pair<std::size_t, Error> process();
};

}
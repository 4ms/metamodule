#pragma once

#include <util/static_string.hh>
#include <utility>

namespace MetaModule
{
class FileLoaderBase
{
public:

    enum class Error { None, Failed };

	virtual bool verify(StaticString<32> md5_chars);

	virtual bool start();

	virtual std::pair<int, Error> load_next_block();
};
}
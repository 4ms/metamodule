#include "hash_processor.hh"

namespace MetaModule
{

MD5Processor::MD5Processor() {
	MD5Init(&context);
}

void MD5Processor::update(std::span<uint8_t> data) {
	MD5Update(&context, data.data(), data.size());
}

MD5Processor::Digest_t MD5Processor::getDigest() {
	Digest_t result;
	MD5Final(result.data(), &context);
	return result;
}

} // namespace MetaModule
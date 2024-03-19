#include <cstring>
#include <iostream>
#include <memory>
#include <ostream>
#include <string_view>

#include "doctest/doctest.h"
#include "base64.h"


// custom buffer
class TCharBuffer final
{
public:
    explicit TCharBuffer(size_t size = 0) : mData(size > 0 ? new char[size] : nullptr), mSize(size) {}
    ~TCharBuffer() noexcept = default;

    char* Ptr() noexcept { return mData.get(); }
    const char* Ptr() const noexcept { return mData.get(); }
    size_t Size() const noexcept { return mSize; }

private:
    std::unique_ptr<char[]> mData;
    size_t mSize = 0;
};


namespace base64
{
    // the const_adapter_t maker is required for containers containing input (immutable) data
    template <>
    inline const_adapter_t make_const_adapter<TCharBuffer>(const TCharBuffer& buffer)
    {
        return const_adapter_t(reinterpret_cast<const uint8_t*>(buffer.Ptr()), buffer.Size());
    }

    // mutable_adapter_t required for containers containing output (mutable) data
    template <>
    inline mutable_adapter_t make_mutable_adapter<TCharBuffer>(TCharBuffer& buffer)
    {
        return mutable_adapter_t(reinterpret_cast<uint8_t*>(buffer.Ptr()), buffer.Size());
    }
}   // namespace base64


TEST_CASE("create_adapters_directly")
{
    using namespace base64;

    constexpr char text[] =
        "Create adapters directly and use them in encoding/decoding functions.";
    const size_t text_size = strlen(text);

    const size_t encoded_size = calc_encoded_size(text_size);
    std::unique_ptr<char[]> encoded{ new char[encoded_size + 1] };
    encoded[encoded_size] = '\0';

    // make an adapter for the text buffer
    const const_adapter_t text_adapter = make_const_adapter(text, text_size);
    // create an adapter for the buffer that will contain encoded data
    mutable_adapter_t encoded_adapter = make_mutable_adapter(encoded.get(), encoded_size);

    // use text_adapter and encoded_adapter adapters to encode data
    auto err_code = encode(text_adapter, encoded_adapter);
    REQUIRE(!err_code);

    // you can use the encoded_adapter as a const_adapter_t
    const size_t decoded_size = calc_decoded_size(encoded_adapter);
    REQUIRE(decoded_size == text_size);

    std::unique_ptr<char[]> decoded{ new char[decoded_size + 1] };
    decoded[decoded_size] = '\0';

    // make a mutable adapter for the buffer that will contain decoded data
    auto decoded_adapter = make_mutable_adapter(decoded.get(), decoded_size);

    // use encoded_adapter and decoded_adapter adapters to decode data
    err_code = decode(encoded_adapter, decoded_adapter);
    REQUIRE(!err_code);
    REQUIRE(strncmp(text, decoded.get(), text_size) == 0);
}


TEST_CASE("define_adapter_makers")
{
    using namespace base64;

    constexpr std::string_view text = "Define adapter makers for custom container.";
    const size_t encoded_size = calc_encoded_size(text.size());

    TCharBuffer encoded{ encoded_size };
    auto err_code = encode(text, encoded);
    REQUIRE(!err_code);

    const size_t decoded_size = calc_decoded_size(encoded);
    REQUIRE(decoded_size == text.size());

    TCharBuffer decoded{ decoded_size };
    err_code = decode(encoded, decoded);
    REQUIRE(!err_code);
    REQUIRE(text == std::string_view(decoded.Ptr(), decoded.Size()));
}

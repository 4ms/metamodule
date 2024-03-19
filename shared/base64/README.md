# base64 - modern C++ library for Base64 encoding & decoding

[![C++](https://img.shields.io/badge/c%2B%2B-20-informational.svg)](https://shields.io/)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
![](https://github.com/khva/kvstor/workflows/linux/badge.svg)
![](https://github.com/khva/kvstor/workflows/macos/badge.svg)
![](https://github.com/khva/kvstor/workflows/windows/badge.svg)


## Table of Contents
- [Description](#description)
- [How to use the library](#how-to-use-the-library)
  - [Quick start](#quick-start)
  - [Base64 encoding](#base64-encoding)
  - [Base64 decoding](#base64-decoding)
  - [Error handling](#error-handling)
  - [How to use custom buffers](#how-to-use-custom-buffers)
- [How to add base64 library to your project](#how-to-add-base64-library-to-your-project)
- [Additional information](#additional-information)


## Description
The `base64` library implements Base64 encoding and decoding functions.

Its main features:
 - header-only and easy to use
 - written in C++20
 - supports different types of STL containers: `std::string`, `std::vector`, `std::string_view`, `std::array`
 - easily adaptable to use custom containers/buffers
 - supports [Base64](https://www.rfc-editor.org/rfc/rfc2045#section-6.8) and ["URL and Filename Safe" Base64](https://www.rfc-editor.org/rfc/rfc3548#section-4) alphabets
 - easily adaptable to use custom Base64 alphabet
 - cross-platform, it can be used on Linux, macOS and Windows (tested on GCC, Clang and MSVC)
 - no external dependencies (only the doctest library is used as part of the test subproject)


## How to use the library
The top-level interface functions are defined in the header file `base64/base64.h`.

### Quick start
Example of encoding data in Base64:
```c++
constexpr std::string_view data = "0123456789";

// calculate the size of output buffer
const size_t encoded_size = base64::calc_encoded_size(data.size());
std::string encoded;

// allocate a buffer of sufficient size
encoded.resize(encoded_size);

// call the encoding function
base64::encode(data, encoded);
assert(encoded == "MDEyMzQ1Njc4OQ==");

```

Example of decoding data from Base64:
```c++
constexpr std::string_view data = "MDEyMzQ1Njc4OQ==";

// calculate the size of output buffer
const size_t decoded_size = base64::calc_decoded_size(data);
std::string decoded;

// allocate a buffer of sufficient size
decoded.resize(decoded_size);

// call the decoding function
base64::decode(data, decoded);
assert(decoded == "0123456789");

```


### Base64 encoding
There are two encoding functions in `base64.h`:
```c++
template <typename raw_array, typename base64_array>
error_code_t encode(const raw_array & raw_data, base64_array & base64_data);

template <typename raw_array, typename base64_array>
error_code_t encode_url(const raw_array & raw_data, base64_array & base64_data);
```
Both functions encode incoming data into Base64 and put the result into the output buffer. The difference between these functions lies in the alphabets used. The `encode()` function uses [Base64](https://www.rfc-editor.org/rfc/rfc2045#section-6.8) alphabet and the `encode_url()` uses ["URL and Filename Safe" Base64](https://www.rfc-editor.org/rfc/rfc3548#section-4) alphabet.

**Parameters:**
 - `raw_data` — the input buffer containing data to encode, supported buffer types: [std::basic_string](https://en.cppreference.com/w/cpp/string/basic_string), [std::vector](https://en.cppreference.com/w/cpp/container/vector), [std::basic_string_view](https://en.cppreference.com/w/cpp/string/basic_string_view), [std::array](https://en.cppreference.com/w/cpp/container/array)
 - `base64_data` — the output buffer containing encoded data after successful execution, supported buffer types: [std::basic_string](https://en.cppreference.com/w/cpp/string/basic_string), [std::vector](https://en.cppreference.com/w/cpp/container/vector), [std::array](https://en.cppreference.com/w/cpp/container/array)

Encoding functions return an error code of type `error_code_t`. The `error_code_t::no_error()` method returns `true` if encoding is successful. Possible error types:
 - `error_type_t::no_error` — no error
 - `error_type_t::insufficient_buffer_size` — insufficient size of output buffer

For more information about errors, see the [Error handling](#error-handling) section.

**Important:** encoding functions do not allocate any dynamic memory, so you need to allocate a buffer of sufficient size before encoding. To do this, use the encoded size calculation functions:

```c++
size_t calc_encoded_size(size_t raw_size) noexcept;
size_t calc_encoded_size_url(size_t raw_size) noexcept;
```
Both functions calculate the encoding buffer size based on the size of the input data. Similar to encoding functions, the first function uses the standard Base64 alphabet, and the second uses the "URL and Filename Safe" Base64 alphabet.

**Parameters:**
 - `raw_size` — the size of input buffer containing data to encode

The calculation functions never fail.

#### Example: Base64 encoding
```c++
#include "base64.h"
#include <iostream>

void base64_encoding()
{
    using namespace base64;

    constexpr std::string_view video_attr = R"({"is_full_screen":false,"window_size":{"width":400,"height":200}})";
    std::string video_base64(calc_encoded_size_url(video_attr.size()), '\0');
    encode_url(video_attr, video_base64);

    std::cout << "original video attributes: " << video_attr << std::endl;
    std::cout << "base64 video attributes:   " << video_base64 << std::endl;
}
```
Expected output:
```
original video attributes: {"is_full_screen":false,"window_size":{"width":400,"height":200}}
base64 video attributes:   eyJpc19mdWxsX3NjcmVlbiI6ZmFsc2UsIndpbmRvd19zaXplIjp7IndpZHRoIjo0MDAsImhlaWdodCI6MjAwfX0
```


### Base64 decoding
There are two decoding functions in `base64.h`:
```c++
template <typename base64_array, typename raw_array>
error_code_t decode(const base64_array & base64_data, raw_array & raw_data);

template <typename base64_array, typename raw_array>
error_code_t decode_url(const base64_array & base64_data, raw_array & raw_data);
```
Both functions decode incoming data from Base64 and put the result into the output buffer. The difference between these functions lies in the alphabets used. The `decode()` function uses [Base64](https://www.rfc-editor.org/rfc/rfc2045#section-6.8) alphabet and the `decode_url()` uses ["URL and Filename Safe" Base64](https://www.rfc-editor.org/rfc/rfc3548#section-4) alphabet.

**Parameters:**
 - `base64_data` — the input buffer containing encoded data, supported buffer types: [std::basic_string](https://en.cppreference.com/w/cpp/string/basic_string), [std::vector](https://en.cppreference.com/w/cpp/container/vector), [std::basic_string_view](https://en.cppreference.com/w/cpp/string/basic_string_view), [std::array](https://en.cppreference.com/w/cpp/container/array)
 - `raw_data` — the output buffer containing decoded data after successful execution, supported buffer types: [std::basic_string](https://en.cppreference.com/w/cpp/string/basic_string), [std::vector](https://en.cppreference.com/w/cpp/container/vector), [std::array](https://en.cppreference.com/w/cpp/container/array)

Encoding functions return an error code of type `error_code_t`. The `error_code_t::no_error()` method returns `true` if encoding is successful. Possible error types:
 - `error_type_t::no_error` — no error
 - `error_type_t::insufficient_buffer_size` — insufficient size of output buffer
 - `error_type_t::invalid_buffer_size` — invalid size of input buffer, the buffer is truncated or corrupted
 - `error_type_t::non_alphabetic_symbol` — the input buffer contains a non-alphabetic symbol

For more information about errors, see the [Error handling](#error-handling) section.

**Important:** decoding functions do not allocate any dynamic memory, so you need to allocate a buffer of sufficient size before decoding. To do this, use the decoded size calculation functions:
```c++
template <typename base64_array>
size_t calc_decoded_size(const base64_array & base64_data) noexcept;

template <typename base64_array>
size_t calc_decoded_size_url(const base64_array & base64_data) noexcept;
```
Both functions calculate the decoding buffer size based on the encoded data. Similar to decoding functions, the first function uses the standard Base64 alphabet, and the second uses the "URL and Filename Safe" Base64 alphabet.

**Parameters:**
 - `base64_data` — the input buffer containing data to decode

The calculation functions never fail.

#### Example: Base64 decoding
```c++
#include "base64.h"
#include <iostream>

void base64_decoding()
{
    using namespace base64;

    constexpr std::string_view video_base64 = "eyJpc19mdWxsX3NjcmVlbiI6ZmFsc2UsIndpbmRvd19zaXplIjp7IndpZHRoIjo0MDAsImhlaWdodCI6MjAwfX0";
    std::string video_attr(calc_decoded_size_url(video_base64), '\0');
    decode_url(video_base64, video_attr);

    std::cout << "base64 video attributes:  " << video_base64 << std::endl;
    std::cout << "decoded video attributes: " << video_attr << std::endl;
}
```
Expected output:
```
base64 video attributes:  eyJpc19mdWxsX3NjcmVlbiI6ZmFsc2UsIndpbmRvd19zaXplIjp7IndpZHRoIjo0MDAsImhlaWdodCI6MjAwfX0
decoded video attributes: {"is_full_screen":false,"window_size":{"width":400,"height":200}}
```


### Error handling
The encoding and decoding functions return a value of type `error_code_t`. The `error_code_t` class contains an error code and an error message. The success of the encoding/decoding operation can be determined using the methods:
```c++
bool has_error() const noexcept;
explicit operator bool() const noexcept;
```
Both methods return `true` if operation fails. You can get the type of error using the method:
```c++
error_type_t type() const noexcept;
```
The method returns the following types of errors:
 - `error_type_t::no_error` — no error
 - `error_type_t::insufficient_buffer_size` — insufficient size of output buffer
 - `error_type_t::invalid_buffer_size` — invalid size of input buffer, the buffer is truncated or corrupted
 - `error_type_t::non_alphabetic_symbol` — the input buffer contains a non-alphabetic symbol

The error message can be obtained using the method:
```c++
const std::string & msg() const noexcept
```
The `msg` method returns an empty string if there is no error.

#### Example: non-alphabetical character in the input buffer
```c++
#include "base64.h"
#include <iostream>

void non_alphabetical_character()
{
    using namespace base64;

    // the non-alphabetical character '(' at index 3
    constexpr std::string_view wrong_data = "MDE(MzQ1Njc4OUFC";

    std::string decoded(calc_decoded_size(wrong_data), '\0');
    const error_code_t error = decode(wrong_data, decoded);

    if (error)
    {
        std::cout << "An error has occurred. " << error.msg() << std::endl;
        return;
    }
    std::cout << "decoded data: " << decoded << std::endl;
}
```
Expected output:
```
An error has occurred. The buffer has the non-alphabetical character 0x28 at index 3.
```

### How to use custom buffers
The `base64` library provides the ability to use containers that are not among the supported ones (`std::string`, `std::vector`, `std::string_view`, `std::array`) as buffers. Low-level library functions work with containers via adapters. There are two ways to use unsupported containers:
 1. [Create adapters directly and use them in encoding/decoding functions](#create-adapters-directly-and-use-them-in-encoding/decoding-functions).
 2. [Define adapter makers for custom container](#define-adapter-makers-for-custom-container).

The `base64` library has two types of adapters: `const_adapter_t` and `mutable_adapter_t`. Both are defined in the `base64/impl/adapters.h` header:
 - `const_adapter_t` is used for containers with input (immutable) data
 - `mutable_adapter_t` is used for containers with output (mutable) data

#### Create adapters directly and use them in encoding/decoding functions
Adapters can be created using the helper functions defined in the `base64/impl/make_adapter.h` header:
```c++
const_adapter_t make_const_adapter(const void * data, size_t byte_count) noexcept;
mutable_adapter_t make_mutable_adapter(void * data, size_t byte_count) noexcept;
```
Both methods create adapters for input and output containers, respectively.

**Parameters:**
 - `data` — pointer to the underlying array serving as byte storage of container (can be `nullptr`)
 - `byte_count` — number of bytes available for writing (must be 0 if `data` is `nullptr`)

#### Example: create adapters directly
```c++
#include <cstring>
#include <iostream>
#include <memory>
#include "base64.h"

void create_adapters_directly()
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

    // use text_adapter and encoded_adapter to encode data
    auto err_code = encode(text_adapter, encoded_adapter);
    assert(!err_code);

    // you can use the encoded_adapter as a const_adapter_t
    const size_t decoded_size = calc_decoded_size(encoded_adapter);
    assert(decoded_size == text_size);

    std::unique_ptr<char[]> decoded{ new char[decoded_size + 1] };
    decoded[decoded_size] = '\0';

    // make a mutable adapter for the buffer that will contain decoded data
    auto decoded_adapter = make_mutable_adapter(decoded.get(), decoded_size);

    // use encoded_adapter and decoded_adapter to decode data
    err_code = decode(encoded_adapter, decoded_adapter);
    assert(!err_code);

    std::cout << "encoded data: " << encoded.get() << std::endl;
    std::cout << "decoded data: " << decoded.get() << std::endl;

    assert(strncmp(text, decoded.get(), text_size) == 0);
}
```
Expected output:
```
encoded data: Q3JlYXRlIGFkYXB0ZXJzIGRpcmVjdGx5IGFuZCB1c2UgdGhlbSBpbiBlbmNvZGluZy9kZWNvZGluZyBmdW5jdGlvbnMu
decoded data: Create adapters directly and use them in encoding/decoding functions.
```

#### Define adapter makers for custom container
A more useful way is to implement adapter makers for your custom container. The adapter makers for custom containers are declared in the `base64/impl/make_adapter.h` header:
```c++
template <typename custom_buffer_type>
const_adapter_t make_const_adapter(const custom_buffer_type &);

template <typename custom_buffer_type>
mutable_adapter_t make_mutable_adapter(custom_buffer_type &);
```
There is only a declaration without an implementation. You will get a linker error if you try to use a custom buffer in encoding/decoding functions.
```c++
TCharBuffer encoded{ encoded_size };
auto err_code = encode(text, encoded);

```
This code produces the linker error:
```
in function `base64::error_code_t base64::encode<std::basic_string_view<char, std::char_traits<char> >, TCharBuffer>(std::basic_string_view<char, std::char_traits<char> > const&, TCharBuffer&)':
/base64/base64.h:75: undefined reference to `base64::mutable_adapter_t base64::make_mutable_adapter<TCharBuffer>(TCharBuffer&)'
```
It is necessary to define a template specialization of adapter makers for the `TCharBuffer` class. Template specialization must be defined in the `base64` namespace:
```c++
namespace base64
{
    // the const_adapter_t maker is required for containers with input (immutable) data
    template <>
    inline const_adapter_t make_const_adapter<TCharBuffer>(const TCharBuffer& buffer)
    {
        return const_adapter_t(reinterpret_cast<const uint8_t*>(buffer.Ptr()), buffer.Size());
    }

    // mutable_adapter_t required for containers with output (mutable) data
    template <>
    inline mutable_adapter_t make_mutable_adapter<TCharBuffer>(TCharBuffer& buffer)
    {
        return mutable_adapter_t(reinterpret_cast<uint8_t*>(buffer.Ptr()), buffer.Size());
    }
}   // namespace base64
```
And here you can see a full example.

#### Example: define adapter makers
```c++
#include <iostream>
#include <memory>
#include <string_view>
#include "base64.h"

// custom buffer
class TCharBuffer final
{
public:
    explicit TCharBuffer(size_t size = 0)
      : mData(size > 0 ? new char[size] : nullptr), mSize(size) {}
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

void define_adapter_makers()
{
    using namespace base64;

    constexpr std::string_view text = "Define adapter makers for custom container.";
    const size_t encoded_size = calc_encoded_size(text.size());

    TCharBuffer encoded{ encoded_size };
    auto err_code = encode(text, encoded);
    assert(!err_code);

    const size_t decoded_size = calc_decoded_size(encoded);
    TCharBuffer decoded{ decoded_size };
    err_code = decode(encoded, decoded);
    assert(!err_code);

    const std::string_view encoded_text(encoded.Ptr(), encoded.Size());
    const std::string_view decoded_text(decoded.Ptr(), decoded.Size());

    std::cout << "encoded data: " << encoded_text << std::endl;
    std::cout << "decoded data: " << decoded_text << std::endl;

    assert(text == decoded_text);
}
```
 Expected output:
```
encoded data: RGVmaW5lIGFkYXB0ZXIgbWFrZXJzIGZvciBjdXN0b20gY29udGFpbmVyLg==
decoded data: Define adapter makers for custom container.
```
As you can see, it is much more convenient to define adapter makers for custom container than to сreate adapters directly and use them in encoding/decoding functions.


## How to add base64 library to your project
The `base64` library can be added as a submodule. Example for adding library to the `third_party` directory in your project:
```bash
git submodule add https://github.com/khva/base64 third_party/base64
```

Another way is to download and copy the library code directly into your project:
 - copy the `base64.h` file to the directory intended for third-party libraries, e.g. to `third_party/base64/base64.h`
 - copy the `impl` directory to the same path, e.g. to `third_party/base64/impl`
 - add `base64.h` path to project settings, e.g. for CMake project: `include_directories(third_party/base64)`


## Additional information
- the library was tested on compilers GCC 11.3, Apple Clang 13, MS Visual Studio 2019/2022
- the minimum version of CMake is 3.15
- the [doctest](https://github.com/doctest/doctest) version 2.4.9 framework is used for testing (as part of the project in the `tests/doctest` directory)

#pragma once


#include "adapters.h"
#include "encoding_traits.h"
#include "errors.h"
#include "make_adapter.h"

#include <cassert>


namespace base64
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // encode functions declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename encoding_traits>
    size_t calc_encoded_size_impl(size_t raw_size) noexcept;

    template <typename encoding_traits>
    error_code_t encode_impl(
        const const_adapter_t       & raw_data,
        const mutable_adapter_t     & base64_data);


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // encode functions definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    inline size_t calc_encoded_size_impl(size_t raw_size) noexcept
    {
        if constexpr (encoding_traits::has_pad())
        {
            return 4 * ((raw_size + 2) / 3);
        }
        else
        {
            const size_t tail_size = raw_size % 3;
            return 4 * (raw_size / 3) + (tail_size == 0 ? 0 : tail_size + 1);
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    error_code_t encode_impl(
        const const_adapter_t       & raw_data,
        const mutable_adapter_t     & base64_data)
    {
        const size_t raw_size = raw_data.size();
        const size_t encoded_size = calc_encoded_size_impl<encoding_traits>(raw_size);
        const size_t base64_size = base64_data.size();

        if (base64_size < encoded_size)
        {
            return detail::insufficient_buffer_size_error(base64_size, encoded_size);
        }

        const uint8_t * raw_ptr = raw_data.data();
        uint8_t * base64_ptr = base64_data.data();

        for (size_t i = 0, j = 0; i < raw_size;)
        {
            uint32_t octet_a = i < raw_size ? raw_ptr[i++] : uint8_t{ 0 };
            uint32_t octet_b = i < raw_size ? raw_ptr[i++] : uint8_t{ 0 };
            uint32_t octet_c = i < raw_size ? raw_ptr[i++] : uint8_t{ 0 };

            uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

            base64_ptr[j++] = encoding_traits::char_at((triple >> 3 * 6) & 0x3F);
            base64_ptr[j++] = encoding_traits::char_at((triple >> 2 * 6) & 0x3F);
            base64_ptr[j++] = encoding_traits::char_at((triple >> 1 * 6) & 0x3F);
            base64_ptr[j++] = encoding_traits::char_at((triple >> 0 * 6) & 0x3F);
        }

        if constexpr (encoding_traits::has_pad())
        {
            const size_t tail_size = raw_size % 3;

            if (tail_size == 2)
            {
                base64_ptr[encoded_size - 1] = encoding_traits::pad();
            }
            else if (tail_size == 1)
            {
                base64_ptr[encoded_size - 1] = encoding_traits::pad();
                base64_ptr[encoded_size - 2] = encoding_traits::pad();
            }
        }

        return error_code_t{};
    }

}   // namespace base64

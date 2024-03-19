#pragma once

#include "adapters.h"
#include "encoding_traits.h"
#include "make_adapter.h"

#include <cassert>


namespace base64
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // decode functions declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename encoding_traits>
    size_t calc_decoded_size_impl(const const_adapter_t & base64_data) noexcept;

    template <typename encoding_traits>
    error_code_t decode_impl(
        const const_adapter_t       & base64_data,
        const mutable_adapter_t     & raw_data);


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // decode functions definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    size_t calc_decoded_size_impl(const const_adapter_t & base64_data) noexcept
    {
        const size_t encoded_size = base64_data.size();
        size_t raw_size = 3 * (encoded_size / 4);

        if constexpr (encoding_traits::has_pad())
        {
            if (encoded_size > 0)
            {
                const uint8_t * base64_ptr = base64_data.data();

                if (base64_ptr[encoded_size - 1] == encoding_traits::pad())
                {
                    --raw_size;

                    if (encoded_size > 1 && base64_ptr[encoded_size - 2] == encoding_traits::pad())
                        --raw_size;
                }
            }
        }
        else
        {
            const size_t tail_size = encoded_size % 4;
            raw_size += tail_size == 0 ? 0 : tail_size - 1;
        }

        return raw_size;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    error_code_t decode_impl(
        const const_adapter_t       & base64_data,
        const mutable_adapter_t     & raw_data)
    {
        const size_t raw_size = calc_decoded_size_impl<encoding_traits>(base64_data);
        const size_t raw_buffer_size = raw_data.size();
        const size_t base64_buffer_size = base64_data.size();

        if (raw_buffer_size < raw_size)
        {
            return detail::insufficient_buffer_size_error(raw_buffer_size, raw_size);
        }

        if (!detail::check_base64_buffer_size<encoding_traits>(base64_buffer_size))
        {
            return detail::invalid_buffer_size_error<encoding_traits>(base64_buffer_size);
        }

        error_code_t err_code;
        const uint8_t * base64_ptr = base64_data.data();

        auto index_of = [base64_ptr, & err_code](size_t pos) -> uint32_t
        {
            const uint8_t symbol = base64_ptr[pos];

            if constexpr (encoding_traits::has_pad())
            {
                if (symbol == encoding_traits::pad())
                    return 0;
            }

            const uint32_t index = encoding_traits::index_of(symbol);

            if (index == encoding_traits::invalid_index())
            {
                if (!err_code)
                    err_code = detail::non_alphabetic_symbol_error(pos, symbol);

                return 0;
            }

            return index;
        };

        auto calc_triple = [](uint32_t sextet_a, uint32_t sextet_b, uint32_t sextet_c, uint32_t sextet_d) -> uint32_t
        {
            return (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);
        };

        const size_t encoded_size = 4 * (base64_buffer_size / 4);
        uint8_t * raw_ptr = raw_data.data();

        size_t raw_pos = 0;
        for (size_t i = 0; i < encoded_size && !err_code;)
        {
            const uint32_t sextet_a = index_of(i++);
            const uint32_t sextet_b = index_of(i++);
            const uint32_t sextet_c = index_of(i++);
            const uint32_t sextet_d = index_of(i++);

            const uint32_t triple = calc_triple(sextet_a, sextet_b, sextet_c, sextet_d);

            assert(raw_pos < raw_size);
            raw_ptr[raw_pos++] = (triple >> 2 * 8) & 0xFF;

            if (raw_pos < raw_size)
                raw_ptr[raw_pos++] = (triple >> 1 * 8) & 0xFF;

            if (raw_pos < raw_size)
                raw_ptr[raw_pos++] = (triple >> 0 * 8) & 0xFF;
        }

        if constexpr (!encoding_traits::has_pad())
        {
            const size_t tail_size = base64_buffer_size - encoded_size;
            assert(tail_size == 0 || tail_size == 2 || tail_size == 3);

            if (tail_size > 0 && !err_code)
            {
                size_t tail_pos = encoded_size;

                const uint32_t sextet_a = index_of(tail_pos++);
                const uint32_t sextet_b = tail_size > 1 ? index_of(tail_pos++) : 0;
                const uint32_t sextet_c = tail_size > 2 ? index_of(tail_pos) : 0;

                const uint32_t triple = calc_triple(sextet_a, sextet_b, sextet_c, 0);

                assert(raw_pos < raw_size);
                raw_ptr[raw_pos++] = (triple >> 2 * 8) & 0xFF;
                
                if (raw_pos < raw_size)
                    raw_ptr[raw_pos++] = (triple >> 1 * 8) & 0xFF;
            }
        }

        return err_code;
    }

}   // namespace base64

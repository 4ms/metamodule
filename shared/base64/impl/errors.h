#pragma once

#include "encoding_traits.h"

#include <cstdio>
#include <string>
#include <string_view>


namespace base64
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // error_type_t enum definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    enum class error_type_t
    {
        no_error = 0,
        insufficient_buffer_size,
        invalid_buffer_size,
        non_alphabetic_symbol
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // error_code_t class definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    class error_code_t
    {
    public:
        error_code_t() noexcept = default;
        error_code_t(error_type_t code, std::string msg) noexcept : m_msg(std::move(msg)), m_code(code) {}
        ~error_code_t() noexcept = default;

        error_type_t type() const noexcept          {   return m_code;  }
        const std::string & msg() const noexcept    {   return m_msg;   }

        bool has_error() const noexcept             {   return m_code != error_type_t::no_error;    }
        explicit operator bool() const noexcept     {   return has_error();                         }

    private:
        std::string     m_msg;
        error_type_t    m_code = error_type_t::no_error;
    };


namespace detail
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // helper functions declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    error_code_t insufficient_buffer_size_error(size_t obtained_size, size_t required_size);

    template <typename encoding_traits>
    error_code_t invalid_buffer_size_error(size_t base64_buffer_size);

    error_code_t non_alphabetic_symbol_error(size_t pos, uint8_t bad_symbol);

    template <typename encoding_traits>
    bool check_base64_buffer_size(size_t base64_buffer_size);


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // helper functions definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Note: a formatting library is not used here (a good one like 'fmt').
    //       fmt is good, but external dependency is bad.

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline error_code_t insufficient_buffer_size_error(size_t obtained_size, size_t required_size)
    {
        constexpr size_t msg_buffer_size = 255;
        std::string msg(msg_buffer_size + 1, '\0');

        constexpr std::string_view msg_template =
            "The buffer has insufficient size (required - %zu, obtained - %zu).";

        std::snprintf(msg.data(), msg_buffer_size, msg_template.data(), required_size, obtained_size);

        return error_code_t(error_type_t::insufficient_buffer_size, msg.c_str());
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    inline error_code_t invalid_buffer_size_error(size_t base64_buffer_size)
    {
        constexpr size_t msg_buffer_size = 255;
        std::string msg(msg_buffer_size + 1, '\0');

        if constexpr (encoding_traits::has_pad())
        {
            constexpr std::string_view msg_template =
                "The base64 buffer has invalid size of %zu. "
                "The buffer size must be a multiple of 4.";

            std::snprintf(msg.data(), msg_buffer_size, msg_template.data(), base64_buffer_size);
        }
        else
        {
            constexpr std::string_view msg_template =
                "The base64 buffer has invalid size of %zu. "
                "The buffer size must be a multiple of 4 or have a remainder of division 2 and 3.";

            std::snprintf(msg.data(), msg_buffer_size, msg_template.data(), base64_buffer_size);
        }

        return error_code_t(error_type_t::invalid_buffer_size, msg.c_str());
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline error_code_t non_alphabetic_symbol_error(size_t pos, uint8_t bad_symbol)
    {
        constexpr size_t msg_buffer_size = 255;
        std::string msg(msg_buffer_size + 1, '\0');

        constexpr std::string_view msg_template =
            "The buffer has the non-alphabetical character 0x%02X at index %zu.";

        std::snprintf(msg.data(), msg_buffer_size, msg_template.data(), bad_symbol, pos);

        return error_code_t(error_type_t::non_alphabetic_symbol, msg.c_str());
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename encoding_traits>
    inline bool check_base64_buffer_size(size_t base64_buffer_size)
    {
        if constexpr (encoding_traits::has_pad())
        {
            return base64_buffer_size % 4 == 0;
        }
        else
        {
            const size_t tail_size = base64_buffer_size % 4;
            return tail_size == 0 || tail_size == 2 || tail_size == 3;
        }
    }

}   // namespace detail
}   // namespace base64

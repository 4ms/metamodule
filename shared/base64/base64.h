#pragma once

#include "impl/encode.h"
#include "impl/decode.h"


namespace base64
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // encode functions declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    size_t calc_encoded_size(size_t raw_size) noexcept;
    size_t calc_encoded_size_url(size_t raw_size) noexcept;

    template <typename raw_array, typename base64_array>
    error_code_t encode(
        const raw_array     & raw_data,
        base64_array        & base64_data);

    template <typename raw_array, typename base64_array>
    error_code_t encode_url(
        const raw_array     & raw_data,
        base64_array        & base64_data);



    ////////////////////////////////////////////////////////////////////////////////////////////////
    // decode functions declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename base64_array>
    size_t calc_decoded_size(const base64_array & base64_data) noexcept;

    template <typename base64_array>
    size_t calc_decoded_size_url(const base64_array & base64_data) noexcept;

    template <typename base64_array, typename raw_array>
    error_code_t decode(
        const base64_array      & base64_data,
        raw_array               & raw_data);

    template <typename base64_array, typename raw_array>
    error_code_t decode_url(
        const base64_array      & base64_data,
        raw_array               & raw_data);



    ////////////////////////////////////////////////////////////////////////////////////////////////
    // encode functions (definition)
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline size_t calc_encoded_size(size_t raw_size) noexcept
    {
        return calc_encoded_size_impl<def_encoding_t>(raw_size);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline size_t calc_encoded_size_url(size_t raw_size) noexcept
    {
        return calc_encoded_size_impl<url_encoding_t>(raw_size);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename raw_array, typename base64_array>
    inline error_code_t encode(
        const raw_array         & raw_data,
        base64_array            & base64_data )
    {
        return encode_impl<def_encoding_t>(
            make_const_adapter(raw_data),
            make_mutable_adapter(base64_data));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename raw_array, typename base64_array>
    inline error_code_t encode_url(
        const raw_array         & raw_data,
        base64_array            & base64_data )
    {
        return encode_impl<url_encoding_t>(
            make_const_adapter(raw_data),
            make_mutable_adapter(base64_data));
    }



    ////////////////////////////////////////////////////////////////////////////////////////////////
    // decode functions definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename base64_array>
    inline size_t calc_decoded_size(const base64_array & base64_data) noexcept
    {
        return calc_decoded_size_impl<def_encoding_t>(make_const_adapter(base64_data));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename base64_array>
    inline size_t calc_decoded_size_url(const base64_array & base64_data) noexcept
    {
        return calc_decoded_size_impl<url_encoding_t>(make_const_adapter(base64_data));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename base64_array, typename raw_array>
    inline error_code_t decode(
        const base64_array      & base64_data,
        raw_array               & raw_data)
    {
        return decode_impl<def_encoding_t>(
            make_const_adapter(base64_data),
            make_mutable_adapter(raw_data));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename base64_array, typename raw_array>
    inline error_code_t decode_url(
        const base64_array      & base64_data,
        raw_array               & raw_data)
    {
        return decode_impl<url_encoding_t>(
            make_const_adapter(base64_data),
            make_mutable_adapter(raw_data));
    }

}   // namespace base64

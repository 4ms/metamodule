#pragma once

#include "adapters.h"

#include <array>
#include <string>
#include <string_view>
#include <vector>


namespace base64
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // adapter makers declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    mutable_adapter_t make_mutable_adapter(void * data, size_t byte_count) noexcept;
    const_adapter_t make_const_adapter(const void * data, size_t byte_count) noexcept;

    // stub for custom adapter makers
    template <typename custom_buffer_type>
    mutable_adapter_t make_mutable_adapter(custom_buffer_type &);

    template <typename custom_buffer_type>
    const_adapter_t make_const_adapter(const custom_buffer_type &);

    // dummy functions for calls like: encode(const_adapter_t, std::string)
    mutable_adapter_t make_mutable_adapter(mutable_adapter_t & adapter) noexcept;
    const_adapter_t make_const_adapter(const const_adapter_t & adapter) noexcept;
    const_adapter_t make_const_adapter(const mutable_adapter_t & adapter) noexcept;

    // std::array<> adapter makers
    template <typename pod_type, size_t array_size>
    mutable_adapter_t make_mutable_adapter(std::array<pod_type, array_size> & data) noexcept;

    template <typename pod_type, size_t array_size>
    const_adapter_t make_const_adapter(const std::array<pod_type, array_size> & data) noexcept;

    // std::vector<> adapter makers
    template <typename pod_type, typename allocator_type>
    mutable_adapter_t make_mutable_adapter(
        std::vector<pod_type, allocator_type> & data) noexcept;

    template <typename pod_type, typename allocator_type>
    const_adapter_t make_const_adapter(
        const std::vector<pod_type, allocator_type> & data) noexcept;

    // std::basic_string<> adapter makers
    template <typename char_type, typename traits_type, typename allocator_type>
    mutable_adapter_t make_mutable_adapter(
        std::basic_string<char_type, traits_type, allocator_type> & data) noexcept;

    template <typename char_type, typename traits_type, typename allocator_type>
    const_adapter_t make_const_adapter(
        const std::basic_string<char_type, traits_type, allocator_type> & data) noexcept;

    // std::basic_string<> const adapter maker
    template <typename char_type, typename traits_type>
    const_adapter_t make_const_adapter(
        const std::basic_string_view<char_type, traits_type> & data) noexcept;


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // adapter makers definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline mutable_adapter_t make_mutable_adapter(void * data, size_t byte_count) noexcept
    {
        return mutable_adapter_t(reinterpret_cast<uint8_t *>(data), byte_count);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline const_adapter_t make_const_adapter(const void * data, size_t byte_count) noexcept
    {
        return const_adapter_t(reinterpret_cast<const uint8_t *>(data), byte_count);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline mutable_adapter_t make_mutable_adapter(mutable_adapter_t & adapter) noexcept
    {
        return adapter;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline const_adapter_t make_const_adapter(const const_adapter_t & adapter) noexcept
    {
        return adapter;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline const_adapter_t make_const_adapter(const mutable_adapter_t & adapter) noexcept
    {
        return const_adapter_t(adapter.data(), adapter.size());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename pod_type, size_t array_size>
    inline mutable_adapter_t make_mutable_adapter(std::array<pod_type, array_size> & data) noexcept
    {
        return mutable_adapter_t(
            reinterpret_cast<uint8_t *>(data.data()), array_size * sizeof(pod_type));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename pod_type, size_t array_size>
    inline const_adapter_t make_const_adapter(const std::array<pod_type, array_size> & data) noexcept
    {
        return const_adapter_t(
            reinterpret_cast<const uint8_t*>(data.data()), array_size * sizeof(pod_type));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename pod_type, typename allocator_type>
    inline mutable_adapter_t make_mutable_adapter(
        std::vector<pod_type, allocator_type> & data) noexcept
    {
        return mutable_adapter_t(
            reinterpret_cast<uint8_t *>(data.data()), data.size() * sizeof(pod_type));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename pod_type, typename allocator_type>
    inline const_adapter_t make_const_adapter(
        const std::vector<pod_type, allocator_type> & data) noexcept
    {
        return const_adapter_t(
            reinterpret_cast<const uint8_t *>(data.data()), data.size() * sizeof(pod_type));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename char_type, typename traits_type, typename allocator_type>
    inline mutable_adapter_t make_mutable_adapter(
        std::basic_string<char_type, traits_type, allocator_type> & data) noexcept
    {
        const size_t array_bytes = data.size() * sizeof(char_type);
        return mutable_adapter_t(
            array_bytes > 0
            ? reinterpret_cast<uint8_t *>(data.data())
            : nullptr, array_bytes);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename char_type, typename traits_type, typename allocator_type>
    inline const_adapter_t make_const_adapter(
        const std::basic_string<char_type, traits_type, allocator_type> & data) noexcept
    {
        const size_t array_bytes = data.size() * sizeof(char_type);
        return const_adapter_t(
            array_bytes > 0
            ? reinterpret_cast<const uint8_t *>(data.data())
            : nullptr, array_bytes);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename char_type, typename traits_type>
    inline const_adapter_t make_const_adapter(
        const std::basic_string_view<char_type, traits_type> & data) noexcept
    {
        const size_t array_bytes = data.size() * sizeof(char_type);
        return const_adapter_t(
            array_bytes > 0
            ? reinterpret_cast<const uint8_t *>(data.data())
            : nullptr, array_bytes);
    }

}   // namespace base64

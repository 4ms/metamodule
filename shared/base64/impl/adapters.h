#pragma once

#include <cassert>
#include <cstdint>
#include <utility>


namespace base64
{

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // adapter_t class declaration
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename byte_type>
    class adapter_t
    {
    public:
        adapter_t() noexcept = default;
        ~adapter_t() noexcept = default;

        adapter_t(byte_type * data, size_t byte_count) noexcept;

        adapter_t(const adapter_t & other) noexcept = default;
        adapter_t & operator=(const adapter_t & other) noexcept = default;

        void swap(adapter_t & other) noexcept;

        byte_type * data() const noexcept;
        size_t size() const noexcept;

    private:
        byte_type * m_data = nullptr;
        size_t      m_size = 0;
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // adapter_t class definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename byte_type>
    inline adapter_t<byte_type>::adapter_t(byte_type * data, size_t byte_count) noexcept
        : m_data(data)
        , m_size(byte_count)
    {
        assert(data != nullptr || (data == nullptr && byte_count == 0));
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename byte_type>
    inline void adapter_t<byte_type>::swap(adapter_t & other) noexcept
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename byte_type>
    inline byte_type * adapter_t<byte_type>::data() const noexcept
    {
        return m_data;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename byte_type>
    inline size_t adapter_t<byte_type>::size() const noexcept
    {
        return m_size;
    }



    ////////////////////////////////////////////////////////////////////////////////////////////////
    // const_adapter_t & mutable_adapter_t definition
    ////////////////////////////////////////////////////////////////////////////////////////////////

    using const_adapter_t = adapter_t<const uint8_t>;
    using mutable_adapter_t = adapter_t<uint8_t>;

}   // namespace base64

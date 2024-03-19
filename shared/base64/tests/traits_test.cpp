#include <ostream>
#include <string_view>

#include "doctest/doctest.h"
#include "base64.h"

TEST_CASE("def_encoding_traits_consistency")
{
    using namespace base64;

    constexpr std::string_view expected_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    REQUIRE(def_encoding_t::alphabet() == expected_alphabet);
    REQUIRE(def_encoding_t::alphabet_size() == 64);
    REQUIRE(def_encoding_t::has_pad());
    REQUIRE(def_encoding_t::pad() == uint8_t{ '=' });
    REQUIRE(def_encoding_t::invalid_index() == 64);

    uint32_t pos = 0;
    bool wrong_pos = false;

    for (const char symbol : def_encoding_t::alphabet())
    {
        pos = def_encoding_t::index_of(static_cast<uint8_t>(symbol));
        if (pos == def_encoding_t::invalid_index())
            break;

        if (def_encoding_t::char_at(pos) != static_cast<uint8_t>(symbol))
        {
            wrong_pos = true;
            break;
        }
    }

    REQUIRE(pos == 63);
    REQUIRE(!wrong_pos);
}


TEST_CASE("url_encoding_traits_consistency")
{
    using namespace base64;

    constexpr std::string_view expected_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    REQUIRE(url_encoding_t::alphabet() == expected_alphabet);
    REQUIRE(url_encoding_t::alphabet_size() == 64);
    REQUIRE(!url_encoding_t::has_pad());
    REQUIRE(url_encoding_t::invalid_index() == 64);

    uint32_t pos = 0;
    bool wrong_pos = false;

    for (const char symbol : url_encoding_t::alphabet())
    {
        pos = url_encoding_t::index_of(static_cast<uint8_t>(symbol));
        if (pos == url_encoding_t::invalid_index())
            break;

        if (url_encoding_t::char_at(pos) != static_cast<uint8_t>(symbol))
        {
            wrong_pos = true;
            break;
        }
    }

    REQUIRE(pos == 63);
    REQUIRE(!wrong_pos);
}


constexpr const char alt_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789*-";
using encoding_with_pad = base64::encoding_traits_t<alt_alphabet, '='>;

TEST_CASE("custom_encoding_traits_with_pad_consistency")
{
    using namespace base64;

    REQUIRE(encoding_with_pad::alphabet() == alt_alphabet);
    REQUIRE(encoding_with_pad::alphabet_size() == 64);
    REQUIRE(encoding_with_pad::has_pad());
    REQUIRE(encoding_with_pad::pad() == uint8_t{ '=' });
    REQUIRE(encoding_with_pad::invalid_index() == 64);

    uint32_t pos = 0;
    bool wrong_pos = false;

    for (const char symbol : encoding_with_pad::alphabet())
    {
        pos = encoding_with_pad::index_of(static_cast<uint8_t>(symbol));
        if (pos == encoding_with_pad::invalid_index())
            break;

        if (encoding_with_pad::char_at(pos) != static_cast<uint8_t>(symbol))
        {
            wrong_pos = true;
            break;
        }
    }

    REQUIRE(pos == 63);
    REQUIRE(!wrong_pos);
}


constexpr const char url_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
using encoding_without_pad = base64::encoding_traits_t<url_alphabet, 0>;

TEST_CASE("custom_encoding_traits_without_pad_consistency")
{
    using namespace base64;

    REQUIRE(encoding_without_pad::alphabet() == url_alphabet);
    REQUIRE(encoding_without_pad::alphabet_size() == 64);
    REQUIRE(!encoding_without_pad::has_pad());
    REQUIRE(encoding_without_pad::pad() == uint8_t{ 0 });
    REQUIRE(encoding_without_pad::invalid_index() == 64);

    uint32_t pos = 0;
    bool wrong_pos = false;

    for (const char symbol : encoding_without_pad::alphabet())
    {
        pos = encoding_without_pad::index_of(static_cast<uint8_t>(symbol));
        if (pos == encoding_without_pad::invalid_index())
            break;

        if (encoding_without_pad::char_at(pos) != static_cast<uint8_t>(symbol))
        {
            wrong_pos = true;
            break;
        }
    }

    REQUIRE(pos == 63);
    REQUIRE(!wrong_pos);
}

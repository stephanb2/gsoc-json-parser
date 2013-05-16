///////////////////////////////////////////////////////////////////////////////
//
// http://protoc.sourceforge.net/
//
// Copyright (C) 2013 Bjorn Reese <breese@users.sourceforge.net>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
// MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHORS AND
// CONTRIBUTORS ACCEPT NO RESPONSIBILITY IN ANY CONCEIVABLE MANNER.
//
///////////////////////////////////////////////////////////////////////////////

//SB required on linux:
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE json_decoder
//SB end

#include <boost/test/unit_test.hpp>

#include <protoc/json/decoder.hpp>

using namespace protoc;

BOOST_AUTO_TEST_SUITE(json_decoder_suite)

//-----------------------------------------------------------------------------
// Whitespaces
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_spaces)
{
    const char input[] = "  ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_tabs)
{
    const char input[] = "\t\t";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_carriage_returns)
{
    const char input[] = "\r\r";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_newlines)
{
    const char input[] = "\n\n";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_junk)
{
    const char input[] = "n true";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_null)
{
    const char input[] = "null";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_null);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_null)
{
    const char input[] = "  null  ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_null);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_nul)
{
    const char input[] = "nul";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_nuller)
{
    const char input[] = "nuller";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const char input[] = "false";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_false);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_false)
{
    const char input[] = "  false  ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_false);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_fals)
{
    const char input[] = "fals";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_falser)
{
    const char input[] = "falser";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const char input[] = "true";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_true);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_true)
{
    const char input[] = "  true  ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_true);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_tru)
{
    const char input[] = "tru";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_truer)
{
    const char input[] = "truer";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_integer_zero)
{
    const char input[] = "0";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_integer);
    BOOST_REQUIRE_EQUAL(decoder.get_integer(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_integer_zero)
{
    const char input[] = "  0  ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_integer);
    BOOST_REQUIRE_EQUAL(decoder.get_integer(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_integer_hundred)
{
    const char input[] = "100";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_integer);
    BOOST_REQUIRE_EQUAL(decoder.get_integer(), 100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_integer_minus_hundred)
{
    const char input[] = "-100";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_integer);
    BOOST_REQUIRE_EQUAL(decoder.get_integer(), -100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_integer_minus)
{
    const char input[] = "-";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_integer_minus_a)
{
    const char input[] = "-a";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_zero)
{
    const char input[] = "0.0";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one)
{
    const char input[] = "1.0";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_minus_one)
{
    const char input[] = "-1.0";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), -1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one_exp_one)
{
    const char input[] = "1e1";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one_upper_exp_one)
{
    const char input[] = "1E1";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one_dot_exp_one)
{
    const char input[] = "1.0e1";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one_exp_plus_one)
{
    const char input[] = "1e+1";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_float_one_exp_minus_one)
{
    const char input[] = "1e-1";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_float);
    BOOST_REQUIRE_EQUAL(decoder.get_float(), 1e-1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_eof_float_missing_fraction)
{
    const char input[] = "0.";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_float_missing_fraction)
{
    const char input[] = "0. ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_eof_float_missing_exponent)
{
    const char input[] = "0e";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_float_missing_exponent)
{
    const char input[] = "0e ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_eof_float_missing_exponent_plus)
{
    const char input[] = "0e+";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_float_missing_exponent_plus)
{
    const char input[] = "0e+ ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_eof_float_missing_exponent_minus)
{
    const char input[] = "0e-";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_float_missing_exponent_minus)
{
    const char input[] = "0e- ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    const char input[] = "\"\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "alpha");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    const char input[] = "\"\\\"\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    const char input[] = "\"\\\\\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\\");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    const char input[] = "\"\\/\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "/");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_backspace)
{
    const char input[] = "\"\\b\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\b");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_formfeed)
{
    const char input[] = "\"\\f\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\f");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_newline)
{
    const char input[] = "\"\\n\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\n");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_carriage_return)
{
    const char input[] = "\"\\r\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\r");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_tab)
{
    const char input[] = "\"\\t\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\t");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_one)
{
    const char input[] = "\"\\u0001\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\x01");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_a)
{
    const char input[] = "\"\\u0061\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "a");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_0123)
{
    const char input[] = "\"\\u0123\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\u0123");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_4567)
{
    const char input[] = "\"\\u4567\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\u4567");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_89AB)
{
    const char input[] = "\"\\u89AB\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\u89AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_CDEF)
{
    const char input[] = "\"\\uCDEF\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "\uCDEF");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_missing_one)
{
    const char input[] = "\"\\u000\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_missing_two)
{
    const char input[] = "\"\\u00\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_missing_three)
{
    const char input[] = "\"\\u0\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_missing_four)
{
    const char input[] = "\"\\u\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_error);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_eof)
{
    const char input[] = "\"\\u0000";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_eof_one)
{
    const char input[] = "\"\\u000";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_eof_two)
{
    const char input[] = "\"\\u00";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_eof_three)
{
    const char input[] = "\"\\u0";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape_unicode_eof_four)
{
    const char input[] = "\"\\u";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_fail_string_escape)
{
    const char input[] = "\"\\\"";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_object_begin)
{
    const char input[] = "{";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_object_begin)
{
    const char input[] = " { ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_object_end)
{
    const char input[] = "}";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_object_end)
{
    const char input[] = " } ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_object)
{
    const char input[] = "{ \"key\" : false }";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_string);
    BOOST_REQUIRE_EQUAL(decoder.get_string(), "key");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_colon);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_false);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_object_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_array_begin)
{
    const char input[] = "[";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_array_begin)
{
    const char input[] = " [ ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_array_end)
{
    const char input[] = "]";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_white_array_end)
{
    const char input[] = " ] ";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_CASE(test_array)
{
    const char input[] = "[true, false]";
    json::decoder decoder(input, input + sizeof(input) - 1);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_begin);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_true);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_comma);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_false);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_array_end);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::token_eof);
}

BOOST_AUTO_TEST_SUITE_END()

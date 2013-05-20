///////////////////////////////////////////////////////////////////////////////
//
// http://jsonec.sourceforge.net/
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

#include <cassert>
#include <jsonec/json/decoder.hpp>
#include <jsonec/json/parser.hpp>

namespace jsonec
{
namespace json
{

parser::parser(builder& b)
    : callbacks(b)
{
}

bool parser::parse(const std::string& buffer)
{
    decoder lexer(buffer.data(), buffer.data() + buffer.size());
    for (;;)
    {
        switch (lexer.next())
        {
        case token_error:
            return false;

        case token_eof:
            return true;

        case token_null:
            callbacks.on_null();
            break;

        case token_true:
            callbacks.on_boolean(true);
            break;

        case token_false:
            callbacks.on_boolean(false);
            break;

        case token_number:
            callbacks.on_number(lexer.get_number());
            break;

        case token_string:
            callbacks.on_string(lexer.get_string());
            break;

        case token_comma:
            // FIXME
            break;

        case token_colon:
            // FIXME
            break;

        case token_array_begin:
            callbacks.on_array_begin();
            break;

        case token_array_end:
            callbacks.on_array_end();
            break;

        case token_object_begin:
            callbacks.on_object_begin();
            break;

        case token_object_end:
            callbacks.on_object_end();
            break;

        default:
            assert(false);
            break;
        }
    }
    assert(false); // We should never get there
    return false;
}

}
}

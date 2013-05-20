#ifndef JSONEC_JSON_PARSER_HPP
#define JSONEC_JSON_PARSER_HPP

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

#include <string>
#include <jsonec/builder.hpp>

namespace jsonec
{
namespace json
{

class parser
{
    typedef bool (parser::*state)();

public:
    parser(builder&);

    bool parse(const std::string&);

private:
    builder& callbacks;
    state current_state;
};

}
}

#endif /* JSONEC_JSON_PARSER_HPP */

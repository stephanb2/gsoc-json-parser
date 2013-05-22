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

/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-20
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_BUILDER_HPP
#define PROTOC_JSON_BUILDER_HPP

namespace protoc
{
namespace json
{


// abstract builder
//
class builder
{
public:
    virtual void on_null() = 0;
    virtual void on_int(int) = 0;
    virtual void on_string(const std::string&) = 0;

    virtual void on_array_begin() = 0;
    virtual void on_array_end() = 0;
};

} //namespace
}

#endif /* PROTOC_JSON_BUILDER_HPP */

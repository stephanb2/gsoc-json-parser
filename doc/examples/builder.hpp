#ifndef JSONEC_BUILDER_HPP
#define JSONEC_BUILDER_HPP

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
#include <boost/cstdint.hpp>

namespace jsonec
{

class builder
{
public:
    virtual void on_null() = 0;
    virtual void on_boolean(bool yes) = 0;
    virtual void on_int8(boost::int8_t) = 0;
    virtual void on_int16(boost::int16_t) = 0;
    virtual void on_int32(boost::int32_t) = 0;
    virtual void on_int64(boost::int64_t) = 0;
    virtual void on_float(float) = 0;
    virtual void on_double(double) = 0;
    virtual void on_number(const std::string&) = 0;
    virtual void on_string(const std::string&) = 0;

    virtual void on_object_begin() = 0;
    virtual void on_object_end() = 0;

    virtual void on_array_begin() = 0;
    virtual void on_array_end() = 0;
};

}

#endif /* JSONEC_BUILDER_HPP */



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


namespace protoc
{
namespace json
{


// abstract builder
class builder
{
public:
    const dynamic::var& value()
    {
         return _value;
    }

    virtual void on_null() = 0;
    virtual void on_int(int) = 0;

    virtual void on_array_begin() = 0;
    virtual void on_array_end() = 0;

protected:
    dynamic::var _value;
};

} //namespace
}

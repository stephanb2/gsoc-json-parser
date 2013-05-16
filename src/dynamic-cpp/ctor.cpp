/*
    Copyright (C) 2009, 2011 Ferruccio Barletta (ferruccio.barletta@gmail.com)

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/
/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-04-10
 *  @license    MIT License
 */

#include "dynamic-cpp/dynamic.h"

namespace dynamic {

    ///
    /// ctor: init with null ($)
    ///
    var::var() : _var() {}

    ///
    /// ctor: init with int
    ///
    var::var(int n) : _var(n) {}

    ///
    /// ctor: init with double
    ///
    var::var(double n) : _var(n) {}

    ///
    /// ctor: init with string
    ///
    var::var(const string& s) : _var(string_t(s)) {}

    ///
    /// ctor: init with string constant
    ///
    var::var(const char* s) : _var(string_t(s)) {}

    ///
    /// ctor: init with wide string
    ///
    var::var(const wstring& s) : _var(wstring_t(s)) {}

    ///
    /// ctor: init with wide string
    ///
    var::var(const wchar_t* s) : _var(wstring_t(s)) {}

    ///
    /// ctor: init with var
    ///
    var::var(const var& v) : _var(v._var) {}

    ///
    /// ctor: init with list
    ///
    var::var(list_ptr _list) : _var(_list) {}

    ///
    /// ctor: init with array
    ///
    var::var(array_ptr _array) : _var(_array) {}

    ///
    /// ctor: init with set
    ///
    var::var(set_ptr _set) : _var(_set) {}

    ///
    /// ctor: init with dict
    ///
    var::var(dict_ptr _dict) : _var(_dict) {}

    ///
    /// ctor: init with map //SB
    ///
    var::var(map_ptr _map) : _var(_map) {}

// ------------------------------------ //SB

    /// create an empty array
    ///
    var var::new_array() { return var(array_ptr(new array_t)); }

    /// create empty map
    ///
    var var::new_map() { return var(map_ptr(new map_t)); }

    /// create empty dict
    ///
    var var::new_dict() { return var(dict_ptr(new dict_t)); }

    /// create empty list
    ///
    var var::new_list() { return var(list_ptr(new list_t)); }

    /// create empty set
    ///
    var var::new_set() { return var(set_ptr(new set_t)); }

}

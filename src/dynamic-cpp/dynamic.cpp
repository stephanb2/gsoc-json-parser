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
#include <cassert>
#include <iostream>
#include <iomanip>

namespace dynamic {

    const var $;
    
    bool var::less_var::operator () (const var& lhs, const var& rhs) {
        // if the two vars are of different types, order by type
        type_t lht = lhs.get_type(), rht = rhs.get_type();
        if (lht != rht) return lht < rht;

        // they are of the same type, order by value
        switch (lht) {
            case type_null : return false;
            case type_int : return get<int_t>(lhs._var) < get<int_t>(rhs._var);
            case type_double : return get<double_t>(lhs._var) < get<double_t>(rhs._var);
            case type_string : return *(get<string_t>(lhs._var).ps) < *(get<string_t>(rhs._var).ps);
            case type_wstring : return *(get<wstring_t>(lhs._var).ps) < *(get<wstring_t>(rhs._var).ps);
            case type_list :
            case type_array :
            case type_set :
            case type_dict :
            case type_map : //SB
                return false;
            default : throw exception("unhandled type");
        }
    }

    ///
    /// append an int to a collection
    ///
    var& var::operator () (int n) { return operator() (var(n)); }

    ///
    /// append a double to a collection
    ///
    var& var::operator () (double n) { return operator() (var(n)); }

    ///
    /// append a string to a collection
    ///
    var& var::operator () (const string& s) { return operator() (var(s)); }

    ///
    /// append a string constant to a collection
    ///
    var& var::operator () (const char* s) { return operator() (var(s)); }

    ///
    /// append a wide string to a collection
    ///
    var& var::operator () (const wstring& s) { return operator() (var(s)); }

    ///
    /// append a wide string constant to a collection
    ///
    var& var::operator () (const wchar_t* s) { return operator() (var(s)); }

    ///
    /// append a single value to a collection
    ///
    var& var::operator () (const var& v) {    
        switch (get_type()) {
            case type_null :    throw exception("invalid () operation on $");
            case type_int :     throw exception("invalid () operation on int");
            case type_double :  throw exception("invalid () operation on double");
            case type_string :  throw exception("invalid () operation on string");
            case type_wstring : throw exception("invalid () operation on wstring");
            case type_list :    get<list_ptr>(_var)->push_back(v); break;
            case type_array :   get<array_ptr>(_var)->push_back(v); break;
            case type_set :     get<set_ptr>(_var)->insert(v); break;
            case type_dict :    get<dict_ptr>(_var)->insert(make_pair<var,var>(v, $)); break;
            default :           throw exception("unhandled () operation");
        }
        return *this;
    }

    ///
    /// add a key,value to a dict
    ///
    var& var::operator () (const var& k, const var& v) {
        switch (get_type()) {
            case type_null :    throw exception("invalid (,) operation on $");
            case type_int :     throw exception("invalid (,) operation on int");
            case type_double :  throw exception("invalid (,) operation on double");
            case type_string :  throw exception("invalid (,) operation on string");
            case type_wstring : throw exception("invalid (,) operation on wstring");
            case type_list :    throw exception("invalid (,) operation on list");
            case type_array :   throw exception("invalid (,) operation on array");
            case type_set :     throw exception("invalid (,) operation on set");
            case type_dict :    get<dict_ptr>(_var)->insert(make_pair<var,var>(k, v)); break;
            default :           throw exception("unhandled (,) operation");
        }
        return *this;
    }

    ///
    /// add a key,value to a map //SB
    ///
    var& var::operator () (const string& k, const var& v) {
        switch (get_type()) {
            case type_null :    throw exception("invalid (,) operation on $");
            case type_int :     throw exception("invalid (,) operation on int");
            case type_double :  throw exception("invalid (,) operation on double");
            case type_string :  throw exception("invalid (,) operation on string");
            case type_wstring : throw exception("invalid (,) operation on wstring");
            case type_list :    throw exception("invalid (,) operation on list");
            case type_array :   throw exception("invalid (,) operation on array");
            case type_set :     throw exception("invalid (,) operation on set");
            case type_dict :    throw exception("invalid (,) operation on dict");
            case type_map :     get<map_ptr>(_var)->insert(make_pair<string,var>(k, v)); break;
            default :           throw exception("unhandled (,) operation");
        }
        return *this;
    }



    ///
    /// count of objects in a collection or characters in a string
    ///
    unsigned int var::count() const {
        switch (get_type()) {
            case type_null :    throw exception("invalid .count() operation on $");
            case type_int :     throw exception("invalid .count() operation on int");
            case type_double :  throw exception("invalid .count() operation on double");
            case type_string :  return static_cast<unsigned int>(get<string_t>(_var).ps->length());
            case type_wstring : return static_cast<unsigned int>(get<wstring_t>(_var).ps->length());
            case type_list :    return static_cast<unsigned int>(get<list_ptr>(_var)->size());
            case type_array :   return static_cast<unsigned int>(get<array_ptr>(_var)->size());
            case type_set :     return static_cast<unsigned int>(get<set_ptr>(_var)->size());
            case type_dict :    return static_cast<unsigned int>(get<dict_ptr>(_var)->size());
            case type_map :     return static_cast<unsigned int>(get<map_ptr>(_var)->size()); //SB
            default :           throw exception("unhandled .count() operation");
        }
    }

    ///
    /// index[] operator for collections
    ///
    var& var::operator [] (int n) {
        switch (get_type()) {
            case type_null :    throw exception("cannot apply [] to $");
            case type_int :     throw exception("cannot apply [] to int");
            case type_double :  throw exception("cannot apply [] to double");
            case type_string :  throw exception("cannot apply [] to string");
            case type_wstring : throw exception("cannot apply [] to wstring");
            case type_list :    {
                                    list_ptr& l = get<list_ptr>(_var);
                                    if (n < 0 || n >= int(l->size())) throw exception("[] out of range in list");
                                    list_t::iterator li = l->begin();
                                    advance(li, n);
                                    return *li;
                                }
            case type_array :   {
                                    array_ptr& a = get<array_ptr>(_var);
                                    if (n < 0 || n >= int(a->size())) throw exception("[] out of range in array");
                                    return (*a)[n];
                                }
            case type_set :     {
                                    set_ptr& s = get<set_ptr>(_var);
                                    if (n < 0 || n >= int(s->size())) throw exception("[] out of range in set");
                                    set_t::iterator si = s->begin();
                                    advance(si, n);
                                    return const_cast<var&>(*si);
                                }
            case type_dict :    {
                                    dict_ptr& d = get<dict_ptr>(_var);
                                    var key(n);
                                    dict_t::iterator di = d->find(key);
                                    if (di == d->end()) throw exception("[] not found in dict");
                                    return di->second;
                                }
            case type_map  :    throw exception("map[] requires string");
            default :           throw exception("unhandled [] operation");
        }
    }

    ///
    /// index a collection with a double
    ///
    var& var::operator [] (double n) { return operator[] (var(n)); }

    ///
    /// index a collection with a string //SB
    ///
    // var& var::operator [] (const string& s) { return operator[] (var(s)); }
    var& var::operator [] (const string& s) {
        switch (get_type()) {
            case type_null :    throw exception("cannot apply [] to $");
            case type_int :     throw exception("cannot apply [] to int");
            case type_double :  throw exception("cannot apply [] to double");
            case type_string :  throw exception("cannot apply [] to string");
            case type_wstring : throw exception("cannot apply [] to wstring");
            case type_list :    throw exception("list[] requires int");
            case type_array :   throw exception("array[] requires int");
            case type_set :     throw exception("set[] requires int");
            case type_dict :    return operator[] (var(s));
            //SB
            case type_map :    { 
                                    var key(s);
                                    map_ptr& m = get<map_ptr>(_var);
                                    map_t::iterator mi = m->find(key);
                                    if (mi != m->end()) return mi->second;
                                    (*m)[key] = $;
                                    return (*m)[key];
                                }
            default :           throw exception("unhandled [] operation");
        }
    }

    ///
    /// index a collection with a string constant
    ///
    var& var::operator [] (const char* s) { return operator[] (var(s)); }

    ///
    /// index a collection with a wide string
    ///
    var& var::operator [] (const wstring& s) { return operator[] (var(s)); }

    ///
    /// index a collection with a wide string constant
    ///
    var& var::operator [] (const wchar_t* s) { return operator[] (var(s)); }
    
    ///
    /// index a collection
    /// 
    var& var::operator [] (const var& v) {
        switch (get_type()) {
            case type_null :    throw exception("cannot apply [var] to $");
            case type_int :     throw exception("cannot apply [var] to int");
            case type_double :  throw exception("cannot apply [var] to double");
            case type_string :  throw exception("cannot apply [var] to string");
            case type_wstring : throw exception("cannot apply [var] to wstring");
            case type_list :    throw exception("list[] requires int");
            case type_array :   throw exception("array[] requires int");
            case type_set :     throw exception("set[] requires int");
            case type_dict :    {
                                    var key(v);
                                    dict_ptr& d = get<dict_ptr>(_var);
                                    dict_t::iterator di = d->find(key);
                                    if (di != d->end()) return di->second;
                                    (*d)[key] = $;
                                    return (*d)[key];
                                }
            case type_map :     throw exception("map[] requires string");
            default :           throw exception("unhandled [var] operation");
        }
    }

    ///
    /// write a var to an ostream    //TODO:add maps
    ///
    ostream& var::_write_var(ostream& os) {
        switch (get_type()) {
            case type_null :    os << "$"; return os;
            case type_int :     os << get<int>(_var); return os;
            case type_double :  os << get<double>(_var); return os;
            case type_string :  return _write_string(os);
            case type_wstring : return _write_wstring(os);
            case type_list :
            case type_array :
            case type_set :
            case type_dict :    return _write_collection(os);
            default :           throw exception("var::_write_var(ostream) unhandled type");
        }
    }

    ///
    /// write a string to an ostream
    ///
    ostream& var::_write_string(ostream& os) {
        assert(is_string());
        os << '\'';
        for (const char* s = (*get<string_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << "\\b"; break;
                case '\r' : os << "\\r"; break;
                case '\n' : os << "\\n"; break;
                case '\f' : os << "\\f"; break;
                case '\t' : os << "\\t"; break;
                case '\\' : os << "\\\\"; break;
                case '\'' : os << "\\'"; break;
                default :
                    if (*s < ' ') os << "0" << oct << setw(3) << setfill('0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a wide string to an ostream
    ///
    ostream& var::_write_wstring(ostream& os) {
        assert(is_wstring());
        os << '\'';
        for (const wchar_t* s = (*get<wstring_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << L"\\b"; break;
                case '\r' : os << L"\\r"; break;
                case '\n' : os << L"\\n"; break;
                case '\f' : os << L"\\f"; break;
                case '\t' : os << L"\\t"; break;
                case '\\' : os << L"\\\\"; break;
                case '\'' : os << L"\\'"; break;
                default :
                    if (*s < ' ') os << L"0" << oct << setw(3) << setfill('0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a collection to an ostream    //TODO:add maps
    ///
    ostream& var::_write_collection(ostream& os) {
        assert(is_collection());
        switch (get_type())
        {
            case type_list : os << "("; break;
            case type_array : os << "["; break;
            case type_set : os << "{"; break;
            case type_dict : os << "<"; break;
            default : assert(false);
        }
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << " ";
            (*vi)._write_var(os);
            if (get_type() == type_dict) {
                os << ":";
                (*this)[*vi]._write_var(os);
            }
        }
        switch (get_type())
        {
            case type_list : os << ")"; break;
            case type_array : os << "]"; break;
            case type_set : os << "}"; break;
            case type_dict : os << ">"; break;
            default : assert(false);
        }
        return os;
    }

    ///
    /// write a var to a wostream
    ///
    wostream& var::_write_var(wostream& os) {
        switch (get_type()) {
            case type_null :    os << "$"; return os;
            case type_int :     os << get<int>(_var); return os;
            case type_double :  os << get<double>(_var); return os;
            case type_string :  return _write_string(os);
            case type_wstring : return _write_wstring(os);
            case type_list :
            case type_array :
            case type_set :
            case type_dict :    return _write_collection(os);
            default :           throw exception("var::_write_var(wostream) unhandled type");
        }
    }

    ///
    /// write a string to a wostream
    ///
    wostream& var::_write_string(wostream& os) {
        assert(is_string());
        os << '\'';
        for (const char* s = (*get<string_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << "\\b"; break;
                case '\r' : os << "\\r"; break;
                case '\n' : os << "\\n"; break;
                case '\f' : os << "\\f"; break;
                case '\t' : os << "\\t"; break;
                case '\\' : os << "\\\\"; break;
                case '\'' : os << "\\'"; break;
                default :
                    if (*s < ' ') os << "0" << oct << setw(3) << setfill(L'0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }

    ///
    /// write a wide string to a wostream  //TODO:add maps
    ///
    wostream& var::_write_wstring(wostream& os) {
        assert(is_wstring());
        os << '\'';
        for (const wchar_t* s = (*get<wstring_t>(_var).ps).c_str(); *s; ++s)
            switch (*s) {
                case '\b' : os << L"\\b"; break;
                case '\r' : os << L"\\r"; break;
                case '\n' : os << L"\\n"; break;
                case '\f' : os << L"\\f"; break;
                case '\t' : os << L"\\t"; break;
                case '\\' : os << L"\\\\"; break;
                case '\'' : os << L"\\'"; break;
                default :
                    if (*s < ' ') os << "0" << oct << setw(3) << setfill(L'0') << int(*s);
                    else os << *s;
            }
        os << '\'';
        return os;
    }
    
    ///
    /// write a collection to a wostream
    ///
    wostream& var::_write_collection(wostream& os) {
        assert(is_collection());
        switch (get_type())
        {
            case type_list : os << L"("; break;
            case type_array : os << L"["; break;
            case type_set : os << L"{"; break;
            case type_dict : os << L"<"; break;
            default : assert(false);
        }
        for (var::iterator vi = begin(); vi != end(); ++vi) {
            if (vi != begin()) os << L" ";
            (*vi)._write_var(os);
            if (get_type() == type_dict) {
                os << L":";
                (*this)[*vi]._write_var(os);
            }
        }
        switch (get_type())
        {
            case type_list : os << L")"; break;
            case type_array : os << L"]"; break;
            case type_set : os << L"}"; break;
            case type_dict : os << L">"; break;
            default : assert(false);
        }
        return os;
    }

}

/*
    Copyright (C) 2009, Ferruccio Barletta (ferruccio.barletta@gmail.com)

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


#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>

#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

///
/// Dynamic C++ namespace
///
namespace dynamic {

    using namespace std;
    using namespace boost;

    using boost::shared_ptr;

    ///
    /// exception class thrown by Dynamic C++
    ///
    class exception : public std::exception
    {
    public :
        ///
        /// construct exception with message
        ///
        exception(const char* message) : std::exception() { _message = message; }
        ~exception() throw() {}
        
        ///
        /// @return exception message
        ///
        const char* what() const throw() { return _message; }
        
    private :
        const char* _message;
    };
    
    class var;
    
    ///
    /// predefined null object
    ///
    extern const var $;

    ///
    /// the var class is the heart of Dynamic C++
    ///
    class var {
    public :
        var();
        var(int n);
        var(double n);
        var(const string& s);
        var(const char* s);
        var(const wstring& s);
        var(const wchar_t* s);
        var(const var& v);

        var& operator = (int n);
        var& operator = (double n);
        var& operator = (const string& s);
        var& operator = (const char* s);
        var& operator = (const wstring& s);
        var& operator = (const wchar_t* s);
        var& operator = (const var& v);

        operator int() const;
        operator double() const;
        operator string() const;
        operator wstring() const;

        string type() const;
/* // 
   //SB ---- disabled comparison operators ---
   //
        bool operator == (int n) const;
        bool operator == (double n) const;
        bool operator == (const string& s) const;
        bool operator == (const char* s) const;
        bool operator == (const wstring& s) const;
        bool operator == (const wchar_t* s) const;
        bool operator == (const var& v) const;

        bool operator != (int n) const;
        bool operator != (double n) const;
        bool operator != (const string& s) const;
        bool operator != (const char* s) const;
        bool operator != (const wstring& s) const;
        bool operator != (const wchar_t* s) const;
        bool operator != (const var& v) const;

        bool operator < (int n) const;
        bool operator < (double n) const;
        bool operator < (const string& s) const;
        bool operator < (const char* s) const;
        bool operator < (const wstring& s) const;
        bool operator < (const wchar_t* s) const;
        bool operator < (const var& v) const;

        bool operator <= (int n) const;
        bool operator <= (double n) const;
        bool operator <= (const string& s) const;
        bool operator <= (const char* s) const;
        bool operator <= (const wstring& s) const;
        bool operator <= (const wchar_t* s) const;
        bool operator <= (const var& v) const;

        bool operator > (int n) const;
        bool operator > (double n) const;
        bool operator > (const string& s) const;
        bool operator > (const char* s) const;
        bool operator > (const wstring& s) const;
        bool operator > (const wchar_t* s) const;
        bool operator > (const var& v) const;

        bool operator >= (int n) const;
        bool operator >= (double n) const;
        bool operator >= (const string& s) const;
        bool operator >= (const char* s) const;
        bool operator >= (const wstring& s) const;
        bool operator >= (const wchar_t* s) const;
        bool operator >= (const var& v) const;
*/
     
        /// is var a null?
        bool is_null() const { return get_type() == type_null; }
        /// is var an int?
        bool is_int() const { return get_type() == type_int; }
        /// is var a double?
        bool is_double() const { return get_type() == type_double; }
        /// is var a numeric type?
        bool is_numeric() const { return is_int() || is_double(); }
        /// is var a string?
        bool is_string() const { return get_type() == type_string; }
        /// is var a wide string?
        bool is_wstring() const { return get_type() == type_string; }
        /// is var a string type?
        bool is_string_type() const { return is_string() || is_wstring(); }
        /// is var a list?
        bool is_list() const { return get_type() == type_list; }
        /// is var an array?
        bool is_array() const { return get_type() == type_array; }
        /// is var a set?
        bool is_set() const { return get_type() == type_set; }
        /// is var a dict?
        bool is_dict() const { return get_type() == type_dict; }
        /// is var a map? //SB
        bool is_map() const { return get_type() == type_map; }
        /// is var a collection type? //SB
        bool is_collection() const { return is_list() || is_array() || is_set() || is_dict() || is_map(); }

        var& operator () (int n);
        var& operator () (double n);
        var& operator () (const string& s);
        var& operator () (const char* s);
        var& operator () (const wstring& s);
        var& operator () (const wchar_t* s);
        var& operator () (const var& v);
        var& operator () (const var& k, const var& v);
        var& operator () (const string& s, const var& v); //SB
       
        ostream& _write_var(ostream& os);
        ostream& _write_string(ostream& os);
        ostream& _write_wstring(ostream& os);
        ostream& _write_collection(ostream& os);

        wostream& _write_var(wostream& os);
        wostream& _write_string(wostream& os);
        wostream& _write_wstring(wostream& os);
        wostream& _write_collection(wostream& os);
        
        static var new_list();
        static var new_array();
        static var new_set();
        static var new_dict();
        static var new_map(); //SB

        unsigned int count() const;
        var& operator [] (int n);
        var& operator [] (double n);
        var& operator [] (const string& s);
        var& operator [] (const char* s);
        var& operator [] (const wstring& s);
        var& operator [] (const wchar_t* s);
        var& operator [] (const var& v);

        /// var comparison functor
        struct less_var {
        /// var comparison function
        bool operator () (const var& lhs, const var& rhs);
        };

        /// list type
        typedef std::list<var> list_t;
        /// array type
        typedef std::vector<var> array_t;
        /// set type
        typedef std::set<var, less_var> set_t;
        /// dict type
        typedef std::map<var, var, less_var> dict_t;
        /// map type //SB
        typedef std::map<string, var> map_t;


        ///
        /// collection iterator class
        ///
        class iterator {
        public :
            /// initialize from list iterator
            iterator(list_t::iterator iter) : _iter(iter) {}
            /// initialize from array iterator
            iterator(array_t::iterator iter) : _iter(iter) {}
            /// initialize from set iterator
            iterator(set_t::iterator iter) : _iter(iter) {}
            /// initialize from dictr iterator
            iterator(dict_t::iterator iter) : _iter(iter) {}
            /// initialize from map iterator
            iterator(map_t::iterator iter) : _iter(iter) {}   //SB         

            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);

            bool operator==(iterator rhs);
            /// iterator inequality
            bool operator!=(iterator rhs) { return !(*this == rhs); }

            var& operator*();

        private :
            // make sure base_type and the variant list for iter_t always match
            //SB added map_type, map_t::iterator
            enum base_type { list_type = 0, array_type, set_type, dict_type, map_type };
            typedef variant<list_t::iterator, array_t::iterator, set_t::iterator, 
                dict_t::iterator, map_t::iterator> iter_t;

            iter_t _iter;
        };

        iterator begin();
        iterator end();

        ///
        /// collection reverse_iterator class
        ///
        class reverse_iterator {
        public :
            /// initialize from list reverse iterator
            reverse_iterator(list_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from array reverse iterator
            reverse_iterator(array_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from set reverse iterator
            reverse_iterator(set_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from dict reverse iterator
            reverse_iterator(dict_t::reverse_iterator riter) : _riter(riter) {}
            /// initialize from dict reverse iterator
            reverse_iterator(map_t::reverse_iterator riter) : _riter(riter) {}  //SB

            reverse_iterator operator++();
            reverse_iterator operator++(int);
            reverse_iterator operator--();
            reverse_iterator operator--(int);

            bool operator==(reverse_iterator rhs);
            /// reverse iterator inequality
            bool operator!=(reverse_iterator rhs) { return !(*this == rhs); }

        private :
            // make sure base_type and the variant list for riter_t always match
            //SB added map_type, map_t::iterator
            enum base_type { list_type = 0, array_type, set_type, dict_type, map_type };
            typedef variant<list_t::reverse_iterator, array_t::reverse_iterator, set_t::reverse_iterator, dict_t::reverse_iterator, map_t::reverse_iterator> riter_t;

            riter_t _riter;
        };

        reverse_iterator rbegin();
        reverse_iterator rend();

    private :
        enum type_t { type_null, type_int, type_double, type_string, type_wstring, type_list, type_array, type_set, type_dict, type_map }; //SB

        struct null_t { null_t() {} };

        struct string_t {
            string_t() : ps(new string) {}
            string_t(const string& s) : ps(new string(s)) {}
            string_t(const char* s) : ps(new string(s)) {}

            shared_ptr<string>  ps;
        };
        
        struct wstring_t {
            wstring_t() : ps(new wstring) {}
            wstring_t(const wstring& s) : ps(new wstring(s)) {}
            wstring_t(const wchar_t* s) : ps(new wstring(s)) {}

            shared_ptr<wstring>  ps;
        };

        typedef int int_t;
        typedef double double_t;

        typedef shared_ptr<list_t> list_ptr;
        typedef shared_ptr<array_t> array_ptr;
        typedef shared_ptr<set_t> set_ptr;
        typedef shared_ptr<dict_t> dict_ptr;
        typedef shared_ptr<map_t> map_ptr; //SB

        var(list_ptr _list);
        var(array_ptr _array);
        var(set_ptr _set);
        var(dict_ptr _dict);
        var(map_ptr _map); //SB map constructor

        typedef variant<null_t, int_t, double_t, string_t, wstring_t, list_ptr, 
            array_ptr, set_ptr, dict_ptr, map_ptr> var_t; //SB

        type_t get_type() const;

        var_t _var;

        /// used to retrieve type from var
        struct type_visitor : public boost::static_visitor<type_t> {
            type_t operator () (null_t) const { return type_null; }
            type_t operator () (int_t) const { return type_int; }
            type_t operator () (double_t) const { return type_double; }
            type_t operator () (string_t s) const { return type_string; }
            type_t operator () (wstring_t s) const { return type_wstring; }
            type_t operator () (list_ptr) const { return type_list; }
            type_t operator () (array_ptr) const { return type_array; }
            type_t operator () (set_ptr) const { return type_set; }
            type_t operator () (dict_ptr) const { return type_dict; }
            type_t operator () (map_ptr) const { return type_map; } //SB
        };

    };


    /// ostream << var
    inline ostream& operator << (ostream& os, var& v) { return v._write_var(os); }
    /// wostream << var
    inline wostream& operator << (wostream& os, var& v) { return v._write_var(os); }

    /// create empty list
    inline var new_list() { return var::new_list(); }
    /// create empty array
    inline var new_array() { return var::new_array(); }
    /// create empty set
    inline var new_set() { return var::new_set(); }
    /// create empty dict
    inline var new_dict() { return var::new_dict(); }
    /// create empty map //SB
    inline var new_map() { return var::new_map(); }


    /// create list with one item
    inline var new_list(const var& v) { return var::new_list()(v); }
    /// create array with one item
    inline var new_array(const var& v) { return var::new_array()(v); }
    /// create set with one item
    inline var new_set(const var& v) { return var::new_set()(v); }
    /// create dict with one item (a key) and null value
    inline var new_dict(const var& k) { return var::new_dict()(k); }
    /// create dict with one item (a key,value pair)
    inline var new_dict(const var& k, const var& v) { return var::new_dict()(k, v); }
    /// create map with one item (a key,value pair) //SB
    inline var new_map(const string& k, const var& v) { return var::new_map()(k, v); }


}

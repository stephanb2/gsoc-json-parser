/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#include <cstdio>
#include <iostream>
#include <protoc/json/stackBuilder.hpp>


namespace protoc
{
namespace json
{

using namespace dynamic;

//constructor
stackBuilder::stackBuilder() : _errors(0) {
}


void stackBuilder::on_null() {
    if (_val.is_array()) {
        _val($);
    }
    // else _val is already initialised to null
}

void stackBuilder::on_int(int i) {
    if (_val.is_array()) {
        _val(i);
    } else {
        _val = i;
    }
}

void stackBuilder::on_string(const std::string& s){
    if (_val.is_array()) {
        _val(s);
    } else {
        _val = s;
    }
}

void stackBuilder::on_array_begin() {
    _stack.push(_val);
    _val = new_array();
}

void stackBuilder::on_array_end() {
    
    if (_stack.empty()) {
        // we get here if the parser makes an error
        _errors++;
    } else if (_stack.top().is_array()) {
        _stack.top()(_val);
        _val = _stack.top();
        _stack.pop();
    } else if (_stack.top().is_null()) {
        // _val already contains the return value
        _stack.pop();
    } else {
        // we get here if the parser makes an error
        _errors++;
        _stack.pop();
    }
}

const var& stackBuilder::result() const {
    return _val;
}

int stackBuilder::errors() {
    return _errors;
}


} //namespace
}

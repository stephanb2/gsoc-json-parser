/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#include <cstdio>
#include <iostream>
#include <protoc/json/stack_builder.hpp>


namespace protoc
{
namespace json
{

using namespace dynamic;

//constructor
stack_builder::stack_builder() : error_count(0) {
}


void stack_builder::on_null() {
    if (value.is_array()) {
        value($);
    }
    // else value is already initialised to null
}

void stack_builder::on_int(int i) {
    if (value.is_array()) {
        value(i);
    } else {
        value = i;
    }
}

void stack_builder::on_string(const std::string& s){
    if (value.is_array()) {
        value(s);
    } else {
        value = s;
    }
}

void stack_builder::on_array_begin() {
    scope.push(value);
    value = new_array();
}

void stack_builder::on_array_end() {
    
    if (scope.empty()) {
        // we get here if the parser makes an error
        error_count++;
    } else if (scope.top().is_array()) {
        scope.top()(value);
        value = scope.top();
        scope.pop();
    } else if (scope.top().is_null()) {
        // value already contains the return value
        scope.pop();
    } else {
        // we get here if the parser makes an error
        error_count++;
        scope.pop();
    }
}

const var& stack_builder::result() const {
    return value;
}

int stack_builder::errors() {
    return error_count;
}


} //namespace
}

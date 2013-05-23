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
    if (value.is_array()) 
    {
        value($);
    }
    else if (value.is_dict()) 
    {
        if (keys.empty()) 
        {
            // parser error: no key on the stack
            error_count++;
        } 
        else 
        {
            value(keys.top(), $);
            keys.pop();
        }
    }
    // else value is already initialised to null
}

void stack_builder::on_int(int i) {
    if (value.is_array())
    {
        // just add i to the array
        value(i);
    } 
    else if (value.is_dict()) 
    {
        if (keys.empty()) 
        {
            // parser error: no key on the stack
            error_count++;
        } 
        else 
        {
            value(keys.top(), i);
            keys.pop();
        }
    } 
    else 
    {
        value = i;
    }
}

void stack_builder::on_string(const std::string& s){
    if (value.is_array()) 
    {
        value(s);
    } 
    else if (value.is_dict()) 
    {
        if (keys.empty()) 
        {
            // parser error: no key on the stack
            error_count++;
        } 
        else 
        {
            value(keys.top(), s);
            keys.pop();
        }
    } 
    else 
    {
        value = s;
    }
}

// --- arrays ---
//
void stack_builder::on_array_begin() {
    scope.push(value);
    value = new_array();
}

void stack_builder::on_array_end() {
    
    if (scope.empty()) {
        // we get here if the parser makes an error
        error_count++;
    }
    //FIXME: as per on_object_end()
    else if (scope.top().is_array()) 
    {
        // we have a nested collection.
        scope.top()(value);
        value = scope.top();
        scope.pop();
    }
    else if (scope.top().is_dict()) 
    {
        //nested object: add the value to the object on the stack
        if (keys.empty()) 
        {
            // parser error: no key on the stack
            error_count++;
        } 
        else 
        {
            scope.top()(keys.top(), value);
            value = scope.top();
            scope.pop();
            keys.pop();
        }
    } 
    else if (scope.top().is_null()) 
    {
        // value already contains the return value
        scope.pop();
    } 
    else 
    {
        // we get here if the parser makes an error
        error_count++;
        scope.pop();
    }
}

// --- objects ---

void stack_builder::on_key(const std::string& s){
    if (value.is_dict()) {
        // push key value on keys stack
        dynamic::var key(s);
        keys.push(key);
    } else {
        // we get here if the parser makes an error
        error_count++;
    }
}


void stack_builder::on_object_begin() {
    scope.push(value);
    value = new_dict();
}


void stack_builder::on_object_end() {
    if (scope.empty()) 
    {
        // we get here if the parser makes an error
        error_count++;
    } 
    else if (scope.top().is_array()) 
    {
        //nested array: add the value to the array on the stack
        scope.top()(value);
        value = scope.top();
        scope.pop();
    }
    else if (scope.top().is_dict()) 
    {
        //nested object: add the value to the object on the stack
        if (keys.empty()) 
        {
            // parser error: no key on the stack
            error_count++;
        } 
        else 
        {
            scope.top()(keys.top(), value);
            value = scope.top();
            scope.pop();
            keys.pop();
        }
    } 
    else if (scope.top().is_null()) 
    {
        // no nested data: value already contains the return value
        scope.pop();
    } 
    else 
    {
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

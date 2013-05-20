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
stackBuilder::stackBuilder() : _errors(0), _isCollection(false) {
}


void stackBuilder::on_null() {
	if (_val.is_array()) {
		_val($);
	}
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
		_errors++;
	} else if (_stack.top().is_array()) {
		_stack.top()(_val);
		_val = _stack.top();
		_stack.pop();
	} else {
		_stack.pop();
	}
}

const var& stackBuilder::result() const{
	return _val;
}

} //namespace
}

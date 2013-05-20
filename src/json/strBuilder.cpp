/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#include <cstdio>
#include <iostream>
#include <protoc/json/strBuilder.hpp>


namespace protoc
{
namespace json
{

void strBuilder::on_null() {
    _result += "null ";
}

void strBuilder::on_int(int i) {
    char s[32];
    sprintf(s, "%d ", i);
    _result += s;
}

void strBuilder::on_string(const std::string& s){
    _result += +"\"" + s + "\" ";
}

void strBuilder::on_array_begin() {
    _result += "[";
}

void strBuilder::on_array_end() {
    _result += "] ";
}

const std::string& strBuilder::result() const{
    return _result;
}

} //namespace
}

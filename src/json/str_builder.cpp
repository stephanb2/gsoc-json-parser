/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#include <cstdio>
#include <iostream>
#include <protoc/json/str_builder.hpp>


namespace protoc
{
namespace json
{

void str_builder::on_null() {
    str_result += "null ";
}

void str_builder::on_int(int i) {
    char s[32];
    sprintf(s, "%d ", i);
    str_result += s;
}

void str_builder::on_string(const std::string& s){
    str_result += +"\"" + s + "\" ";
}

void str_builder::on_array_begin() {
    str_result += "[";
}

void str_builder::on_array_end() {
    str_result += "] ";
}

const std::string& str_builder::result() const {
    return str_result;
}

} //namespace
}

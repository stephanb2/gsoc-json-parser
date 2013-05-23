/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-20
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_STACK_BUILDER_HPP
#define PROTOC_JSON_STACK_BUILDER_HPP

#include <stack>
#include <string>

#include <protoc/json/builder.hpp>
#include <dynamic-cpp/dynamic.h>


namespace protoc
{
namespace json
{

// Concrete Builder
//
class stack_builder : public builder
{
public:

    stack_builder();     //constructor.

    void on_null();
    void on_int(int);
    void on_string(const std::string& s);
    void on_key(const std::string& s);   
    
    void on_array_begin();
    void on_array_end();
    void on_object_begin();
    void on_object_end();
    
    const dynamic::var& result() const;
    int errors();

private:
    dynamic::var value;
    std::stack<dynamic::var> scope;
    std::stack<dynamic::var> keys;
    int error_count;
};


} //namespace
}

#endif /* PROTOC_JSON_STACK_BUILDER_HPP */

/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-20
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_STACKBUILDER_HPP
#define PROTOC_JSON_STACKBUILDER_HPP

#include <stack>
#include <string>

#include <protoc/json/abstractBuilder.hpp>
#include <dynamic-cpp/dynamic.h>


namespace protoc
{
namespace json
{

// Concrete Builder
//
class stackBuilder : public abstractBuilder
{
public:

    stackBuilder();     //constructor.

    void on_null();
    void on_int(int);
    void on_string(const std::string& s);
    void on_array_begin();
    void on_array_end();
    const dynamic::var& result() const;
    int errors();

private:
    dynamic::var _val;
    std::stack<dynamic::var> _stack;
    int _errors;
};


} //namespace
}

#endif /* PROTOC_JSON_STACKBUILDER_HPP */

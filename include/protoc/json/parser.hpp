/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_PARSER_HPP
#define PROTOC_JSON_PARSER_HPP

#include <protoc/json/decoder.hpp>
#include <protoc/json/abstractBuilder.hpp>


namespace protoc
{
namespace json
{


class parser
{

public:
    parser(const std::string&, abstractBuilder &b);
    void test_run();
    void parse() const;

private:
    mutable protoc::json::decoder _decoder;
    void json_array() const;
    abstractBuilder& _builder;
};



} //namespace
}

#endif /* PROTOC_JSON_PARSER_HPP */

/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_PARSER_HPP
#define PROTOC_JSON_PARSER_HPP

#include <protoc/json/decoder.hpp>
#include <protoc/json/builder.hpp>


namespace protoc
{
namespace json
{


class parser
{

public:
    parser(const std::string&, builder &b);
    void test_run();
    void parse();

private:
    mutable protoc::json::decoder decode;
    void json_array();
    void json_object();
    void key_value_pair();
    builder& build;
};



} //namespace
}

#endif /* PROTOC_JSON_PARSER_HPP */

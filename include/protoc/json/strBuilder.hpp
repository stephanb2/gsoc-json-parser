/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-20
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_STRBUILDER_HPP
#define PROTOC_JSON_STRBUILDER_HPP

#include <protoc/json/abstractBuilder.hpp>
#include <string>

namespace protoc
{
namespace json
{

// Concrete Builder
//
class strBuilder : public abstractBuilder
{
public:
    //we use the default constructor.

    void on_null();
    void on_int(int);
    void on_string(const std::string& s);
    void on_array_begin();
    void on_array_end();
    const std::string& result() const;

private:
    std::string _result;
};


} //namespace
}

#endif /* PROTOC_JSON_STRBUILDER_HPP */

/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-20
 *  @license    MIT License
 */

#ifndef PROTOC_JSON_STR_BUILDER_HPP
#define PROTOC_JSON_STR_BUILDER_HPP

#include <protoc/json/builder.hpp>
#include <string>

namespace protoc
{
namespace json
{

// Concrete Builder
//
class str_builder : public builder
{
public:
    //we use the default constructor.

    void on_null();
    void on_int(int);
    void on_string(const std::string& s);
    void on_array_begin();
    void on_array_end();
    //const std::string& result() const;
    std::ostream& write_string(std::ostream& os);

private:
    std::string str_result;
};


/// ostream << str_result
inline std::ostream& operator<< (std::ostream& os, str_builder& sb) { 
    return sb.write_string(os);
}


} //namespace
}

#endif /* PROTOC_JSON_STR_BUILDER_HPP */

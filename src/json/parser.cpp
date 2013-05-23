/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-15
 *  @license    MIT License
 */

#include <iostream>
#include <protoc/json/parser.hpp>
#include <dynamic-cpp/dynamic.h>

namespace protoc
{
namespace json
{


// constructor
//
parser::parser(const std::string& buffer, builder &b)
    : decode(buffer.data(), buffer.data() + buffer.size()),
     build(b)
{
 
    if (decode.type() == json::token_eof) 
    {
        std::cout << "init eof" << std::endl;
    }
}

//
//TODO: write an error counting & reporting method
//

void parser::test_run() {

    while (decode.type() != json::token_eof) 
    {
        if (decode.type() == json::token_integer) 
        {
             build.on_int((int) decode.get_integer());
        } 
        else if (decode.type() == json::token_string) 
        {
             build.on_string(decode.get_string());
        } 
        else if (decode.type() == json::token_array_begin) 
        {
             build.on_array_begin();
        }
        else if (decode.type() == json::token_array_end)
        {
             build.on_array_end();
        }
        decode.next();
    }

}


//  BNF production:
//  Value = ( string | int64_t | double | Object | Array | true | false | null ).
//  
//  advances to the next token when it reads a ( string | number | bool | null )
//
void parser::parse()
{
    //build value is initialised to null
    
    switch (decode.type())
    {
    case json::token_null :
        build.on_null();
        decode.next();
        break;
        
    case json::token_integer :
        //FIXME: dynamic-cpp needs to accept int64_t instead of int
        //this is using the overloaded assignment operator from dynamic-cpp
        build.on_int((int) decode.get_integer());
        decode.next();
        break;

    case json::token_string :
        build.on_string(decode.get_string());
        decode.next();
        break;
    
    case json::token_array_begin :
        json_array();
        break;
        
    case json::token_object_begin :
        json_object();
        break;
    }
    
}




//  BNF production:
//  Array = "[" ( | Value {"," Value}) "]".
//TODO: error recovery
//
void parser::json_array()
{
    
    //build value is initialised to empty array

    bool empty = true;
    build.on_array_begin();

    decode.next(); //skip opening bracket

    //we use negation of condition.
    //TODO: improve this for validation, this tolerates trailing or multiple commas
    if ((decode.type() != json::token_array_end) && (decode.type() != json::token_object_end) &&
        (decode.type() != json::token_comma) && (decode.type() != json::token_colon) &&
        (decode.type() != json::token_error) && (decode.type() != json::token_eof))
    {
        //read value and push it in the builder stack
        parse();
        empty = false;
    }

    while (!empty && (decode.type() == json::token_comma))
    {
        //we have a comma, advance to the next token
        decode.next();
        
        if ((decode.type() != json::token_array_end) && (decode.type() != json::token_object_end) &&
            (decode.type() != json::token_comma) && (decode.type() != json::token_colon) &&
            (decode.type() != json::token_error) && (decode.type() != json::token_eof))
        {
            //read value and push it in the builder stack
            parse();
        }
        else
        {
            std::cout << "unexpected symbol in array" << std::endl;
        }
    }

    if (decode.type() == json::token_array_end)
    {
        build.on_array_end();
        decode.next(); //skip closing bracket
    }
    else
    {
        std::cout << "mising end of array symbol" << std::endl;
    }

}


//  BNF production:
//  Object = "{" ( | string ":" Value {"," string ":" Value}) "}".
//
//  we use this derivation:
//  Object = "{" ( | Pair {"," Pair}) "}".
//  Pair = string ":" Value.

void parser::key_value_pair()
{
    // read key
    //TODO: check for duplicate keys, or overwrite existing element ?
    if (decode.type() == json::token_string)
    {
        //read value and push it in the builder stack
        build.on_key(decode.get_string());
        decode.next();
    }
    else
    {
        std::cout << "string expected for object key" << std::endl;
    }
    
    // read colon
    if (decode.type() == json::token_colon)
    {
        decode.next(); //skip colon
    }
    else
    {
        std::cout << "missing colon after object key" << std::endl;
    }
    
    // read value
    // we use negation of condition.
    if ((decode.type() != json::token_array_end) && (decode.type() != json::token_object_end) &&
        (decode.type() != json::token_comma) && (decode.type() != json::token_colon) &&
        (decode.type() != json::token_error) && (decode.type() != json::token_eof))
    {
        //read value and push it in the builder stack
        parse();
    }
    else
    {
        std::cout << "unexpected object value" << std::endl;
    }
   
}


//  BNF production:
//  Object = "{" ( | Pair {"," Pair}) "}".
//TODO: error recovery
//
void parser::json_object()
{
    
    //build value is initialised to empty object
    bool empty = true;
    build.on_object_begin();

    decode.next(); //skip opening brace
    
    if (decode.type() != json::token_object_end)
    {
        key_value_pair();
        empty = false;
    }

    while (!empty && (decode.type() == json::token_comma))
    {
        //we have a comma, advance to the next token
        decode.next();
        key_value_pair();
    }

    if (decode.type() == json::token_object_end)
    {
        build.on_object_end();
        decode.next(); //skip closing brace
    }
    else
    {
        std::cout << "mising end of object symbol" << std::endl;
    }

}



} //namespace
}

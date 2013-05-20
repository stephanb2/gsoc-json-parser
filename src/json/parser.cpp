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
parser::parser(const std::string& buffer, abstractBuilder &b)
    : _decoder(buffer.data(), buffer.data() + buffer.size()),
	 _builder(b)
{
 
    if (_decoder.type() == json::token_eof) 
    {
        std::cout << "init eof" << std::endl;
    }
}

//
//TODO: write an error counting & reporting method
//

void parser::test_run() {

    while (_decoder.type() != json::token_eof) 
    {
        if (_decoder.type() == json::token_integer) 
        {
             _builder.on_int((int) _decoder.get_integer());
        } 
        else if (_decoder.type() == json::token_string) 
        {
             _builder.on_string(_decoder.get_string());
        } 
        else if (_decoder.type() == json::token_array_begin) 
        {
             _builder.on_array_begin();
        }
        else if (_decoder.type() == json::token_array_end)
        {
             _builder.on_array_end();
        }
        _decoder.next();
    }

}


//  BNF production:
//  Value = ( string | int64_t | double | Object | Array | true | false | null )
//  
//  will advance to the next token when it reads a ( string | number | bool | null )
//
void parser::parse() const
{
    //using namespace dynamic;
    //dynamic::var val; // val is initialised to null

    if (_decoder.type() == json::token_null)
    {
        _builder.on_null();
		_decoder.next();
    }
    else if (_decoder.type() == json::token_integer)
    {
        //FIXME: dynamic-cpp needs to accept int64_t instead of int
        //this is using the overloaded assignment operator from dynamic-cpp
        _builder.on_int((int) _decoder.get_integer());
        _decoder.next();
    }
    else if (_decoder.type() == json::token_string)
    {
        _builder.on_string(_decoder.get_string());
        _decoder.next();
    }
    else if (_decoder.type() == json::token_array_begin)
    {
        json_array();
    }
    
}




//  BNF production:
//  Array = "[" ( | Value {"," Value}) "]"
//TODO: error recovery
//
void parser::json_array() const
{
    //using namespace dynamic;
    //dynamic::var val = new_array(); // val is initialised to empty array

    bool empty = true;
	_builder.on_array_begin();

	_decoder.next(); //skip opening bracket

    //we use negation of condition.
    //TODO: improve this for validation, this tolerates trailing or multiple commas
    if ((_decoder.type() != json::token_array_end) && (_decoder.type() != json::token_object_end) &&
        (_decoder.type() != json::token_comma) && (_decoder.type() != json::token_colon) &&
        (_decoder.type() != json::token_error) && (_decoder.type() != json::token_eof))
    {
        //read value and push it in the val array
        parse();
        empty = false;
    }

    while (!empty && (_decoder.type() == json::token_comma))
    {
        //we have a comma, advance to the next token
        _decoder.next();
        
    	if ((_decoder.type() != json::token_array_end) && (_decoder.type() != json::token_object_end) &&
    	    (_decoder.type() != json::token_comma) && (_decoder.type() != json::token_colon) &&
    	    (_decoder.type() != json::token_error) && (_decoder.type() != json::token_eof))
        {
			//read value and push it in the val array
            parse();
        }
        else
        {
            std::cout << "value missing in array" << std::endl;
        }
    }

    if (_decoder.type() == json::token_array_end)
    {
        _builder.on_array_end();
		_decoder.next(); //skip closing bracket
    }
    else
    {
        std::cout << "mising end of array symbol" << std::endl;
    }

}


} //namespace
}

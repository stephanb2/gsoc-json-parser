/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-22
 *  @license    MIT License
 */
 
//#include <protoc/json/parser.hpp>
#include <protoc/json/stack_builder.hpp>
#include <protoc/json/str_builder.hpp>

//the following line is required on linux:
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE parser_tests
#include <boost/test/unit_test.hpp>

using namespace protoc;
using namespace dynamic;

BOOST_AUTO_TEST_CASE (string_builder) {
    
    std::stringstream ss;
    json::str_builder sbuild;
    
    sbuild.on_array_begin();
    sbuild.on_int(12);
    sbuild.on_string("a");
    sbuild.on_array_end();
    
    ss << sbuild;
    BOOST_CHECK_EQUAL(ss.str(), "[12 \"a\" ] ");
    
}


BOOST_AUTO_TEST_CASE (stack_builder_array01) {
    
    std::stringstream ss;
    json::stack_builder build;
    
    build.on_array_begin();
    build.on_int(12);
    build.on_string("a");
    build.on_null();
    build.on_array_end();
    
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(int(result[0]), 12);
    BOOST_CHECK_EQUAL(string(result[1]), "a");
    BOOST_CHECK_EQUAL(result[2].type(), "null");    
    BOOST_CHECK_EQUAL(ss.str(), "[12 'a' $]");
}


BOOST_AUTO_TEST_CASE (stack_builder_array) {
    
    std::stringstream ss;
    json::stack_builder build;
    
    build.on_array_begin();
    build.on_int(12);
    build.on_string("a");
    build.on_null();
    build.on_array_end();
    
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "string");    
    BOOST_CHECK_EQUAL(result[2].type(), "null");
    
    BOOST_CHECK_EQUAL(int(result[0]), 12);
    BOOST_CHECK_EQUAL(string(result[1]), "a");
    BOOST_CHECK_EQUAL(ss.str(), "[12 'a' $]");
}


BOOST_AUTO_TEST_CASE (stack_builder_array_nested) {
    
    std::stringstream ss;
    json::stack_builder build;
    
    build.on_array_begin();
    build.on_int(12);
    build.on_array_begin();
    build.on_array_end();
    build.on_int(4);    
    build.on_array_end();
    
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "array");
    BOOST_CHECK_EQUAL(result[2].type(), "int");
    
    BOOST_CHECK_EQUAL(int(result[0]), 12);
    BOOST_CHECK_EQUAL(int(result[2]), 4);
    BOOST_CHECK_EQUAL(ss.str(), "[12 [] 4]");
}


BOOST_AUTO_TEST_CASE (stack_builder_null_object) {

    std::stringstream ss;
    json::stack_builder build;

    build.on_object_begin();
    build.on_object_end();

    dynamic::var result = build.result();
    ss << result;

    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(ss.str(), "<>");
}

BOOST_AUTO_TEST_CASE (stack_builder_object) {

    std::stringstream ss;
    json::stack_builder build;

    build.on_object_begin();
    build.on_key("a");
    build.on_int(6);
    build.on_key("b");
    build.on_null();
    build.on_key("c");
    build.on_string("foo");    
    build.on_object_end();

    dynamic::var result = build.result();
    ss << result;

    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(ss.str(), "<'a':6 'b':$ 'c':'foo'>");
}


BOOST_AUTO_TEST_CASE (stack_builder_obj_in_array) {

    std::stringstream ss;
    json::stack_builder build;

    build.on_array_begin();
    build.on_int(2);
    build.on_object_begin();
    build.on_key("a");
    build.on_int(12);
    build.on_object_end();
    build.on_array_end();   

    dynamic::var result = build.result();
    ss << result;

    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[1].type(), "dict");    
    BOOST_CHECK_EQUAL(ss.str(), "[2 <'a':12>]");
}


BOOST_AUTO_TEST_CASE (stack_builder_array_in_obj) {

    std::stringstream ss;
    json::stack_builder build;

    build.on_object_begin();
    build.on_key("a");
    build.on_array_begin();
    build.on_int(2);
    build.on_int(12);
    build.on_array_end();
    build.on_object_end();

    dynamic::var result = build.result();
    ss << result;

    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(result["a"].type(), "array");    
    BOOST_CHECK_EQUAL(ss.str(), "<'a':[2 12]>");
}

BOOST_AUTO_TEST_CASE (stack_builder_nested_obj) {

    std::stringstream ss;
    json::stack_builder build;

    build.on_object_begin();
    build.on_key("root");
    build.on_object_begin();
    build.on_key("a");
    build.on_int(2);
    build.on_object_end();
    build.on_object_end();

    dynamic::var result = build.result();
    ss << result;

    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(result["root"].type(), "dict");    
    BOOST_CHECK_EQUAL(ss.str(), "<'root':<'a':2>>");
}



/*

BOOST_AUTO_TEST_CASE (parse_int) {
    
    const std::string input = "12";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();

    BOOST_CHECK_EQUAL(build.errors(), 0);
    BOOST_CHECK_EQUAL(result.type(), "int");
    BOOST_CHECK_EQUAL(int(result), 12);
}


BOOST_AUTO_TEST_CASE (parse_null) {
    
    const std::string input = "null";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    
    BOOST_CHECK_EQUAL(build.errors(), 0);
    BOOST_CHECK_EQUAL(result.type(), "null");
}


BOOST_AUTO_TEST_CASE (parse_array) {
    std::stringstream ss;
    const std::string input = "[12, null, [], \"a\"]";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "null");
    BOOST_CHECK_EQUAL(result[2].type(), "array");
    BOOST_CHECK_EQUAL(result[3].type(), "string");
    
    BOOST_CHECK_EQUAL(ss.str(), "[12 $ [] 'a']");
}


BOOST_AUTO_TEST_CASE (parse_array_nested) {
    std::stringstream ss;
    const std::string input = "[12, null, [2, []], \"a\"]";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "null");
    BOOST_CHECK_EQUAL(result[2].type(), "array");
    BOOST_CHECK_EQUAL(result[2][0].type(), "int");
    BOOST_CHECK_EQUAL(result[2][1].type(), "array");
    
    BOOST_CHECK_EQUAL(ss.str(), "[12 $ [2 []] 'a']");
}

*/


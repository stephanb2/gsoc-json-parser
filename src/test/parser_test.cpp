/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-22
 *  @license    MIT License
 */
 
#include <protoc/json/parser.hpp>
#include <protoc/json/stack_builder.hpp>
#include <protoc/json/str_builder.hpp>

//the following line is required on linux:
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE parser_tests
#include <boost/test/unit_test.hpp>

using namespace protoc;
using namespace dynamic;


BOOST_AUTO_TEST_CASE (parse_null) {
    
    const std::string input = "null";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    
    BOOST_CHECK_EQUAL(build.errors(), 0);
    BOOST_CHECK_EQUAL(result.type(), "null");
}


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

// --- arrays ---

BOOST_AUTO_TEST_CASE (parse_empty_array) {
    std::stringstream ss;
    const std::string input = "[]";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result.count(), 0);
    BOOST_CHECK_EQUAL(ss.str(), "[]");
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
    BOOST_CHECK_EQUAL(result.count(), 4);
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "null");
    BOOST_CHECK_EQUAL(result[2].type(), "array");
    BOOST_CHECK_EQUAL(result[3].type(), "string");
    
    BOOST_CHECK_EQUAL(ss.str(), "[12 $ [] 'a']");
}

// --- objects ---

BOOST_AUTO_TEST_CASE (parse_object) {
    std::stringstream ss;
    const std::string input = "{\"a\":12, \"b\":\"foo\"}";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(result.count(), 2);
    BOOST_CHECK_EQUAL(result["a"].type(), "int");
    BOOST_CHECK_EQUAL(result["b"].type(), "string");    
    
    BOOST_CHECK_EQUAL(ss.str(), "<'a':12 'b':'foo'>");
}

// --- nested containers ---

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


BOOST_AUTO_TEST_CASE (parse_array_in_object) {
    std::stringstream ss;
    const std::string input = "{\"a\":null, \"b\":[2, 6, 12]}";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(result.count(), 2);
    BOOST_CHECK_EQUAL(result["a"].type(), "null");
    BOOST_CHECK_EQUAL(result["b"].type(), "array");    
    BOOST_CHECK_EQUAL(result["b"].count(), 3);
    
    BOOST_CHECK_EQUAL(int(result["b"][0]), 2);
    BOOST_CHECK_EQUAL(ss.str(), "<'a':$ 'b':[2 6 12]>");
}


BOOST_AUTO_TEST_CASE (parse_object_in_array) {
    std::stringstream ss;
    const std::string input = "[1, {\"a\":12}]";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "array");
    BOOST_CHECK_EQUAL(result.count(), 2);
    BOOST_CHECK_EQUAL(result[0].type(), "int");
    BOOST_CHECK_EQUAL(result[1].type(), "dict");  
    
    BOOST_CHECK_EQUAL(int(result[1]["a"]), 12);
    BOOST_CHECK_EQUAL(ss.str(), "[1 <'a':12>]");
}


BOOST_AUTO_TEST_CASE (parse_nested_objects) {
    std::stringstream ss;
    const std::string input = "{\"root\":{\"a\":12, \"b\":null}}";
    
    json::stack_builder build;    
    json::parser parser(input, build);
    
    parser.parse();
    dynamic::var result = build.result();
    ss << result;
    
    BOOST_CHECK_EQUAL(build.errors(), 0); 
    BOOST_CHECK_EQUAL(result.type(), "dict");
    BOOST_CHECK_EQUAL(result.count(), 1);
    BOOST_CHECK_EQUAL(result["root"].type(), "dict");
    BOOST_CHECK_EQUAL(result["root"].count(), 2);  
    
    BOOST_CHECK_EQUAL(int(result["root"]["a"]), 12);
    BOOST_CHECK_EQUAL(ss.str(), "<'root':<'a':12 'b':$>>");
}



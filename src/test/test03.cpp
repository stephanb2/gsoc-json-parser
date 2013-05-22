/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-14
 *  @license    MIT License
 */

#include <protoc/json/parser.hpp>
#include <protoc/json/stack_builder.hpp>
#include <protoc/json/str_builder.hpp>

using namespace protoc;
using namespace dynamic;

int main() {
    {
        const std::string input = "[2, 12, [null, \"aa\", [] ] ]";

        json::str_builder build;
        json::parser parser(input, build);

        parser.test_run();
        //this uses the overloaded ostream operator from str_builder
        std::cout << build << std::endl;
    }

    {
        const std::string input = "[12, 2, [], 6]";

        json::stack_builder build;
        json::parser parser(input, build);

        parser.parse();

        dynamic::var result = build.result();
        std::cout << "input: " << input << std::endl;
        //this uses the overloaded ostream operator from dynamic-cpp
        std::cout << "parse: " << result << std::endl;
        std::cout << "errors: " << build.errors() << std::endl;
    }

    {
        const std::string input = "[2, 12, [null, \"aa\", [] ] ]";

        json::stack_builder build;
        json::parser parser(input, build);

        parser.parse();

        dynamic::var result = build.result();
        std::cout << "input: " << input << std::endl;
        std::cout << "parse: "  << result << std::endl;
        std::cout << "errors: " << build.errors() << std::endl;
    }


    return 0;
}

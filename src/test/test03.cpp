/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-14
 *  @license    MIT License
 */

#include <protoc/json/parser.hpp>
#include <protoc/json/stackBuilder.hpp>
#include <protoc/json/strBuilder.hpp>

using namespace protoc;
using namespace dynamic;

int main() {
    {
		const std::string input = "[2, 12, [null, \"aa\", [] ] ]";

		json::strBuilder build;
		json::parser parser(input, build);

		parser.test_run();
		std::cout << build.result() << std::endl;
	}

    {
		const std::string input = "[12, 2, [], 6]";

		json::stackBuilder build;
		json::parser parser(input, build);

		parser.parse();

		dynamic::var result = build.result();
		std::cout << "input: " << input << std::endl;
		//this uses the overloaded ostream operator from dynamic-cpp
		std::cout << "parse: " << result << std::endl;
	}

    {
		const std::string input = "[2, 12, [null, \"aa\", [] ] ]";

		json::stackBuilder build;
		json::parser parser(input, build);

		parser.parse();

		dynamic::var result = build.result();
		std::cout << "input: " << input << std::endl;
		std::cout << "parse: "  << result << std::endl;
	}


    return 0;
}

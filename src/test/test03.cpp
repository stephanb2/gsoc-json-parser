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
		const char input[] = "[2, 12, [null, \"aa\", [] ] ]";

		json::strBuilder build;
		json::parser parser(input, input + sizeof(input) - 1, build);

		parser.test_run();
		std::cout << build.result() << std::endl;
	}

    {
		const char input[] = "[12, 2, [], 6]";

		json::stackBuilder build;
		json::parser parser(input, input + sizeof(input) - 1, build);

		parser.json_value();
		dynamic::var result = build.result();
		
		//this uses the overloaded ostream operator from dynamic-cpp
		std::cout << result << std::endl;
	}


    return 0;
}

/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-14
 *  @license    MIT License
 */

#include <protoc/json/parser.hpp>


using namespace protoc;
using namespace dynamic;

int main() {
    {
		const char input[] = "[2, 12, [null, \"aa\", [] ] ]";

		json::parser parser(input, input + sizeof(input) - 1);

		//this uses the overloaded assignment operator from dynamic-cpp
		//var is the dynamic container class.
		var value = parser.json_value();
		
		std::cout << value.type() << " size: " << value.count() << std::endl;

		//this uses the overloaded ostream operator from dynamic-cpp
		std::cout << value << std::endl;

		//retrieves the "aa" element in the nested array
		std::cout << value[2][1] << std::endl;
    }

    {
		const char *input = "[ , , 3, 4, ]";
		json::parser parser(input, input + sizeof(input) - 1);

		var value = parser.json_value();
		std::cout << value << std::endl;
    }
 
    return 0;
}

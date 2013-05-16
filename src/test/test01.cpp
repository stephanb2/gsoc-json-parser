/*
 *  @author     Stephan Bourgeois <stephanb2@hotmail.com>
 *  @version    0.1
 *  @since      2013-05-14
 *  @license    MIT License
 */

#include <protoc/json/parser.hpp>
#include <dynamic.h>

using namespace protoc;
using namespace dynamic;

int main() {

    const char input[] = "[2, 12]";

    json::parser parser(input, input + sizeof(input) - 1);

    parser.test_run();

    return 0;
}

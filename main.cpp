/* This is a parser example program
 * The parser allows to manage multiple parser functions for various scenarios and various input/output types
 * In this example, the input will be a char string in global memory. Char string is a printed number.
 * Output is an integer in the global memory
 * We will create a parser, bind a parser function,
 * create input and output objects, and feed them to the parser
 *
 * After that we will break a few things and check error codes
 * To make sure they work
*/


#include <iostream>
#include <cstdlib>
#include "tinytypeparser.h"
#include "user_parser.h"

const char example_int_as_string[] = "42069";
int output_int_as_int = 0;

//Creating a list of IDs for my parser functions
enum MyParsers {
	PARSER_CHARSTR_TO_INT, //We use only this in the example
	PARSER_EXTRA0, //Unused
	PARSER_EXTRA1, //Unused
	PARSER_EXTRA2, //Unused
	PARSER_COUNT,  //In case you want to iterate
};

int main() {

	/* Step 1: Create object, allocate vtable memory, bind parser functions */
	TinyTypeParser parser = TinyTypeParser();
	TinyTypeParser::parse_func_t vtable[4] = { }; //let's allocate memory for 4 different parser functions (this example uses 1)
	parser.parsefunc_vtable = vtable;
	parser.parsefunc_vtable_len = 4;
	parser.parsefunc_vtable[PARSER_CHARSTR_TO_INT] = my_parse_func_charstr_to_int; //function written by the user

	/* Step 2: Create Input and Output objects and configure them */
	TinyTypeParser::ParserInput input;
	input.data_type = TinyTypeParser::DataType::CHARSTR;
	input.memory = (void*) example_int_as_string;
	input.memory_bytelen = sizeof(example_int_as_string);

	TinyTypeParser::ParserOutput output;
	output.data_type = TinyTypeParser::DataType::INT;
	output.memory = &output_int_as_int;
	output.memory_bytelen = sizeof(int);

	/* Step 3: Parse */
	int parser_result_code;
	parser_result_code = parser.parse(PARSER_CHARSTR_TO_INT, &input,
				&output);
	std::cout << "Parsing charstr to integer" << std::endl;

	if (parser_result_code == TinyTypeParser::RETVAL_OK) {
		std::cout << "Parser returned success! The output integer is "
				<< int(output_int_as_int) << std::endl;
	} else {
		std::cout << "Parser returned failure! The error code is "
				<< int(parser_result_code) << std::endl;
	}
	output_int_as_int = 0; //resetting

	/* ========== END ========== */

	/* Now let's break some things and check the return codes */
	std::cout
			<< "Setting incorrect type for the input and checking the return code"
			<< std::endl;
	input.data_type = TinyTypeParser::DataType::INT32; //wrong type, must be int, user decides in their parser function what types are ok
	parser_result_code = parser.parse(PARSER_CHARSTR_TO_INT, &input, &output);
	if (parser_result_code == TinyTypeParser::RETVAL_OK) {
		std::cout << "Parser returned success! The output integer is "
				<< int(output_int_as_int) << std::endl;
	} else {
		std::cout << "Parser returned failure! The error code is "
				<< int(parser_result_code) << std::endl;
	}

	std::cout << "Triggering parser that is not bound (no vtable entry)"
			<< std::endl;
	parser_result_code = parser.parse(PARSER_EXTRA0, &input, &output);
	if (parser_result_code == TinyTypeParser::RETVAL_OK) {
		std::cout << "Parser returned success! The output integer is "
				<< int(output_int_as_int) << std::endl;
	} else {
		std::cout << "Parser returned failure! The error code is "
				<< int(parser_result_code) << std::endl;
	}

	return 0;
}

#include "user_parser.h"
#include <cstdlib>

TinyTypeParser::errcode_t my_parse_func_charstr_to_int(TinyTypeParser::ParserInput *input,
		TinyTypeParser::ParserOutput *output) {

	//error code is just an int
	TinyTypeParser::errcode_t retval = TinyTypeParser::RETVAL_OK;

	//checking if inputs are valid
	if (input == nullptr) {
		retval = TinyTypeParser::RETVAL_ERROR_INPUT_NOT_SET;
		goto end;
	}
	if (output == nullptr) {
		retval = TinyTypeParser::RETVAL_ERROR_OUTPUT_NOT_SET;
		goto end;
	}

	//checking types of input and output
	//if ok, actually parsing
	if (input->data_type == TinyTypeParser::DataType::CHARSTR) {
		if (output->data_type == TinyTypeParser::DataType::INT) {
			/*================*/
			/* parsing itself */
			*(int*)output->memory = atoi((char*)input->memory);
			/* end of parsing */
			/*================*/
		}else{
			retval = TinyTypeParser::RETVAL_OUTPUT_TYPE_UNSUPPORTED_BY_PARSER_FUNC;
			goto end;
		}
	}
	else{
		retval = TinyTypeParser::RETVAL_INPUT_TYPE_UNSUPPORTED_BY_PARSER_FUNC;
		goto end;
	}
	end: return retval;
}

#ifndef TINYTYPEPARSER_H_
#define TINYTYPEPARSER_H_

class TinyTypeParser {
public:
	typedef int errcode_t;

	enum RETVAL {
		RETVAL_OK,
		RETVAL_ERROR_BAD_VTABLE,
		RETVAL_ERROR_NO_PARSER,
		RETVAL_INPUT_TYPE_UNSUPPORTED_BY_PARSER_FUNC,
		RETVAL_OUTPUT_TYPE_UNSUPPORTED_BY_PARSER_FUNC,
		RETVAL_ERROR_INPUT_NOT_SET,
		RETVAL_ERROR_OUTPUT_NOT_SET,
	};

	enum class DataType {
		NONE,
		CHARSTR,
		CHARHEXSTR,
		SHORT,
		USHORT,
		INT,
		UINT,
		LONG,
		ULONG,
		LONGLONG,
		ULONGLONG,
		CHAR,
		UCHAR,
		INT16,
		UINT16,
		INT32,
		UINT32,
		INT64,
		UINT64,
		USERTYPE0,
		USERTYPE1,
		USERTYPE2,
		USERTYPE3,
		USERTYPE4,
		USERTYPE5,
		USERTYPE6,
		USERTYPE7,
		USERTYPE8,
	};
	typedef struct ParserInput {
		DataType data_type;
		void *memory;
		unsigned int memory_bytelen;
	} ParserInput;

	typedef struct ParserOutput {
		DataType data_type;
		void *memory;
		unsigned int memory_bytelen;
	} ParserOutput;

	typedef errcode_t (*parse_func_t)(ParserInput *input, ParserOutput *output);

	parse_func_t *parsefunc_vtable;
	unsigned int parsefunc_vtable_len;

	errcode_t parse(unsigned int parsefunc_id, ParserInput *input,
			ParserOutput *output) {
		int retval = RETVAL_OK;
		if ((parsefunc_vtable == nullptr) || (parsefunc_vtable_len == 0)) {
			retval = RETVAL_ERROR_BAD_VTABLE;
			goto end;
		}
		if (parsefunc_vtable[parsefunc_id] != nullptr) {
			retval = parsefunc_vtable[parsefunc_id](input, output);
			goto end;
		} else {
			retval = RETVAL_ERROR_NO_PARSER;
			goto end;
		}
		end: return retval;
	}

};

#endif /* TINYTYPEPARSER_H_ */

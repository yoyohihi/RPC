#include <sstream>
#include <stdlib.h>
#include <string>

#include "Exception.h"
#include "debug.h"
#include "rpc_args.h"
#include "Util.h"


using namespace rpcLib;


bool argTypes::isInput(uint32_t type)
{
	uint32_t mask = 1 << ARG_INPUT;
	return (mask & type);
}

bool argTypes::isOutput(uint32_t type)
{
	uint32_t mask = 1 << ARG_OUTPUT;
	return (mask & type);
}

bool argTypes::isArray(uint32_t type,int* arr_len)
{
	*arr_len = (type & 0x0000ffff);
	if (*arr_len == 0)
	{
		return false;
	}

	return true;
}

unsigned int argTypes::getType(uint32_t type)
{
    unsigned int ret = (type & 0x00ff0000) >> 16;
	// verify
	switch (ret)
	{
		case ARG_CHAR:
		case ARG_SHORT:
		case ARG_INT:
		case ARG_LONG:
		case ARG_DOUBLE:
		case ARG_FLOAT:
		   return ret;
		default:
		   debug(ERROR,"an unknown argument type detected!");
		   throw Exception::UnhandledCaseError();
		   break;
	}

	return ARG_UNKNOWN;
}

std::string argTypes::t2s(int type)
{
	std::string ret;
	switch (type)
	{
	case ARG_CHAR:
		ret = "C";
		break;
	case ARG_SHORT:
		ret = "S";
		break;
	case ARG_INT:
		ret = "I";
		break;
	case ARG_LONG:
		ret = "L";
		break;
	case ARG_DOUBLE:
		ret = "D";
		break;
	case ARG_FLOAT:
		ret = "F";
		break;
	default:
		debug(ERROR,"get an unknown type");
		break;
	}

	return ret;
}

int argTypes::getTypeSize(std::string in)
{
	if (in == "C") return sizeof(char);
	if (in == "S") return sizeof(short);
	if (in == "I") return sizeof(int);
	if (in == "L") return sizeof(long);
	if (in == "D") return sizeof(double);
	if (in == "F") return sizeof(float);

	debug(ERROR,"got an unknown type, it is %s",in.c_str());
	return -1;
}

std::string argTypes::getFuncSignature(std::string func_name, int* types,int* argLen)
{
	std::stringstream stream;
	stream << func_name << "(";

	std::string in  = "";
	std::string out = "";

	int arr_len;
	int i;

	for (i = 0 ; types[i] != 0; ++i)
	{
		if (isInput(types[i]))
		{
			if (isArray(types[i],&arr_len))
			{
				 debug(DEBUG,"detects an array, size %d",arr_len);
				 in += "ARR:";
				 std::string string_type = t2s(getType(types[i]));
				 in += string_type;
				 in += ",";
				 in = in + arr_len;
			}
			else
			{
				std::string string_type = t2s(getType(types[i]));
				in += string_type;
			}

			in += " ";
		}

		if (isOutput(types[i]))
		{
			if (isArray(types[i],&arr_len))
			{
				 debug(DEBUG,"detects an array, size %d",arr_len);
				 out += "ARR:";
				 std::string string_type = t2s(getType(types[i]));
				 out += string_type;
				 out += ",";
				 out = out + arr_len;
			}
			else
			{
				std::string string_type = t2s(getType(types[i]));
				out += string_type;
			}
		}
	}

	*argLen = i;

	stream << in << ";" << out;

	stream << ")";

	debug(DEBUG,"FUNC %s",stream.str().c_str());
	return stream.str();
}


int argTypes::getOutputIndex(int* types)
{
	for (int i = 0 ; types[i] != 0; ++i)
	{
		if (isOutput(types[i]))
		{
			return i;
		}
	}

	return -1;
}






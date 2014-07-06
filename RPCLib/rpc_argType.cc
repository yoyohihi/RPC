#include <sstream>
#include "Exception.h"
#include "debug.h"
#include "rpc_args.h"


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
		case ARG_INPUT:
		case ARG_OUTPUT:
		   return ret;
		default:
		   throw Exception::UnhandledCaseError();
		   break;
	}

	return ARG_UNKNOWN;
}

std::string argTypes::deSugar(std::string func_name, int* types)
{
	std::stringstream stream;
	stream << func_name << " :";

	for (int i = 0 ; types[i] != 0; ++i)
	{
		unsigned int func_type = getType(types[i]);
		stream << func_type;
		if (types[i+1] != 0)
		{
			stream << " ";
		}
	}
	return stream.str();
}







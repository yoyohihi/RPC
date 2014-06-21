#include "rpc_lib.h"


using namespace rpcLib;

// implementation of namespace : argTypes

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

argTypes::argType argTypes::getType(uint32_t type)
{
    argType ret = (type & 0x00ff0000) >> 16;
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
		   throw exception::UnknownArgType();
		   break;
	}

	return ARG_UNKNOWN;
}

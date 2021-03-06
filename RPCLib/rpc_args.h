#ifndef _RPC_ARGS_H_
#define _RPC_ARGS_H_

#include <stdint.h>

namespace rpcLib
{

	namespace argTypes
	{
		typedef enum argType
		{
			ARG_UNKNOWN = 0,
			ARG_CHAR  = 1,
			ARG_SHORT = 2,
			ARG_INT   = 3,
			ARG_LONG  = 4,
			ARG_DOUBLE= 5,
			ARG_FLOAT = 6,
			ARG_INPUT = 31,
			ARG_OUTPUT= 30
		} argType;

		// I/O
		bool isOutput(uint32_t type);
		bool isInput(uint32_t type);

        // Array
		bool isArray(uint32_t type);
		int getArraySize(uint32_t type);

        // getter
		unsigned int getType(uint32_t type);

        // create a new argType
		int Create(bool isInput,bool isOutput, int type, int size = 0);

		// de-sugar functions
		std::string deSugar(std::string func_name, int* types);
	} // end

}

#endif

#ifndef _RPC_LIB_H_
#define _RPC_LIN_H_

#include <stdint.h>


namespace rpcLib
{
	namespace argTypes
	{
		typedef enum
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
		argType getType(uint32_t type);

        // create a new argType
		int Create(bool isInput,bool isOutput, int type, int size = 0);
	} // implementation in rpc_argTypes.cc


	namespace returnCode
	{
		const int SUCCESS = 0;
		const int FAIL    = -1;
	}

	namespace exception
	{
		class UnknownArgType{};
	}
}


// RPC LIB API declaration
typedef int (*skeleton)(int *, void **);

int rpcInit();
int rpcCall(char* name, int* argTypes, void** args);
int rpcCacheCall(char* name, int* argTypes, void** args);
int rpcRegister(char* name, int* argTypes, skeleton f);
int rpcExecute();
int rpcTerminate();

#endif

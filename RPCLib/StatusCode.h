#ifndef _STATUS_CODE_H_
#define _STATUS_CODE_H_


namespace rpcLib
{
	namespace Status
	{
		const int SUCCESS         =  0;  //< indicating a succeed status
		const int SUCCESS_WARNING =  1;  //< indicating a succeed status with warning(e.g a duplicated registration)
		const int EXEC_IN_PROCESS =  2;  //< indicating the function is in process of calculating
		const int FAIL_EXEC       = -1;  //< indicating server fails to execute the function
		const int FAIL_CONNS      = -2;  //< indicating a failure due to connection issue
		const int FAIL_SENT       = -3;  //< indicating a failure due to data sending issue
		const int FAIL_DATA       = -4;  //< indicating data get corrupted during the transmission
		const int FAIL_LOC        = -5;  //< indicating the locating request is failed
		const int FAIL_REG        = -6;  //< indicating fail to register server
		const int FAIL_SETUP      = -7;  //< indicating a failure due to setup issue
	}
}

#endif

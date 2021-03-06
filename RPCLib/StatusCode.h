#ifndef _STATUS_CODE_H_
#define _STATUS_CODE_H_


namespace rpcLib
{
	namespace Status
	{
		const int SUCCESS    = 0;
		const int FAIL_SETUP = -1;
		const int FAIL_CONNS = -2;
		const int FAIL_SENT  = -3;

		const int READY      = 1;
		const int NOT_READY  = 2;
	}
}

#endif

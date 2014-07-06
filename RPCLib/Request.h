#ifndef _REQUEST_H_
#define _REQUEST_H_


namespace rpcLib
{
	namespace Request
	{
		const int REQ_UNKNOWN = 0; //<unknown request
		const int REQ_LOC     = 1; //<Location Request
		const int REQ_REG     = 2; //<Registeration Request
		const int REQ_QUIT    = 3; //<Termination Request
		const int REQ_CLOC    = 4; //<Cache Location Request
	}
}


#endif

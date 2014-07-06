#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>
#include "Protocol.h"

namespace rpcLib
{

class Socket
{
public:
	Socket();
	virtual ~Socket();

	virtual std::string getHostName()            = 0;
	virtual uint32_t    getPortNum()             = 0;
	virtual uint32_t    getFileDescriptor()      = 0;
	virtual void        create_connection()      = 0;

<<<<<<< HEAD:RPCLib/Socket.h
	virtual int         receiveInt();
	virtual int         sendInt(int data);
=======
	virtual void        sendProtocol(Protocol* p);
	virtual int         receiveInt();
>>>>>>> FETCH_HEAD:RPC/RPCLib/Socket.h

};

}


#endif

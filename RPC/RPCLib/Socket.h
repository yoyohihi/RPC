#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>

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

	virtual void        sendProtocol(Protocol* p);
	virtual int         receiveInt();

};

}


#endif

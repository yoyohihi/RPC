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

	virtual std::string getHostname() = 0;
	virtual uint32_t getPortNum() = 0;
	virtual uint32_t getFileDescriptor() = 0;
	virtual void connect() = 0;

};

}


#endif

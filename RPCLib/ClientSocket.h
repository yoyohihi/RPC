#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

#include <string>
#include "Socket.h"

namespace rpcLib
{
class ClientSocket: public Socket
{
public:
	ClientSocket();
	ClientSocket(uint32_t port, std::string& addr);
	virtual ~ClientSocket();

	virtual std::string getHostName();
	virtual uint32_t getPortNum();
	virtual uint32_t getFileDescriptor();
	virtual void create_connection();

	virtual int  sendString(const char* data);
	virtual int  sendInt(int data);
	virtual int  sendVoid(void* data, int len);

	virtual int   receiveInt();
	virtual char* receiveString();
	virtual void* receiveVoid();
private:
	uint32_t    m_port;              //<Client socket port number
	uint32_t    m_fileDescriptor;    //<Client socket file descriptor
	std::string m_hostName;          //<Client socket host name

};
}

#endif

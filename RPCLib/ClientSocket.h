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
	ClientSocket(uint32_t port, std::string addr);
	virtual ~ClientSocket();

	virtual std::string getHostName();
	virtual uint32_t getPortNum();
	virtual uint32_t getFileDescriptor();
	virtual void create_connection();

	virtual void sendProtocol(Protocol& p);
	virtual int  receiveInt();
	virtual int  sendInt(int data);
private:
	uint32_t    m_port;
	uint32_t    m_fileDescriptor;
	std::string m_hostName;

};
}

#endif

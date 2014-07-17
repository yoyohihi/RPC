#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include <string>
#include "Socket.h"

namespace rpcLib
{
class ServerSocket: public Socket
{
public:
	ServerSocket();
	ServerSocket(uint32_t port, std::string& addr);
	~ServerSocket();

	virtual std::string getHostName();
	virtual uint32_t getPortNum();
	virtual uint32_t getFileDescriptor();
	virtual void create_connection();

	virtual int   receiveInt();
	virtual char* receiveString();
	virtual void* receiveVoid();

	virtual int   sendInt(int value);
	virtual int   sendString(const char* data);
	virtual int   sendVoid(void* data,int len);

	virtual void  assignComm(int fd);
	virtual int   getServingClient();

private:
	uint32_t    m_port;            //< server port
	uint32_t    m_fileDescriptor;  //< server socket file descriptor
	uint32_t    m_commSocket;      //< communication file Descriptor
	std::string m_hostName;        //< server host name
};
}

#endif

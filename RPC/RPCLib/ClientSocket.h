#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

#include <string>

namespace rpcLib
{
class ClientSocket: public Socket
{
public:
	ClientSocket();
	virtual ~ClientSocket();

	virtual std::string getHostName();
	virtual uint32_t getPortNum();
	virtual uint32_t getFileDescriptor();
private:
	uint32_t    m_port;
	uint32_t    m_fileDescriptor;
	std::string m_hostName;

};
}

#endif

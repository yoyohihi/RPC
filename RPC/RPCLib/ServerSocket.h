#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include <string>

namespace rpcLib
{
class ServerSocket: public Socket
{
public:
	ServerSocket();
	~ServerSocket();

	virtual std::string getHostName();
private:
	uint32_t    port;
	uint32_t    fileDescriptor;
	std::string hostName;
};
}

#endif

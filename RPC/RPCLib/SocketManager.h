#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include <vector>



namespace rpcLib
{
class Socket;

class SocketManager
{
private:
	std::vector<Socket*> m_clientConns;
public:
	SocketManager();
	~SocketManager();

	void addSock(Socket* sock);
	void removeSock(Socket* sock);

};
}

#endif

#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include <vector>
#include "Socket.h"


namespace rpcLib
{
class SocketManager
{
private:
	std::vector<Socket*> m_manager;
	Socket*              m_curSock;
	uint32_t             m_curPtr;
public:
	SocketManager();
	~SocketManager();

	void addSock(Socket* sock);
	void removeSock(Socket* sock);
	Socket* rr_schedule();

};
}

#endif

#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include <vector>



namespace rpcLib
{
class ClientSocket;

class SocketManager
{
private:
	std::vector<ClientSocket*> m_clientConns;
};
}

#endif

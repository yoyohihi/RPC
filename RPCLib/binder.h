#ifndef _BINDER_H_
#define _BINDER_H_

#include "Socket.h"
#include "SocketManager.h"


#include <map>
#include <string>
#include <cstdlib>

namespace rpcLib
{

class Binder : private SocketManager
{
private:
	void addSock(Socket* sock);
	void removeSock(Socket* sock);
	void registerSock(Socket* sock);
	void deregisterSock(Socket* sock);
<<<<<<< HEAD:RPCLib/binder.h
	void locate(int fd);
=======
	void locate(Socket* sock);
>>>>>>> FETCH_HEAD:RPC/RPCLib/binder.h
	int  recvReq();

	Socket* m_server;

public:
	Binder();
	~Binder();

	void start();
	void tearDown();
};

}



#endif

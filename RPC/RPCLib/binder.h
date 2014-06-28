#ifndef _BINDER_H_
#define _BINDER_H_

#include <map>
#include <string>

namespace rpcLib
{

class Binder : private SocketManager
{
private:
	void addSock(Socket* sock);
	void removeSock(Socket* sock);
	void registerSock(Socket* sock);
	void deregisterSock(Socket* sock);
	void locate(Socket* sock);
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

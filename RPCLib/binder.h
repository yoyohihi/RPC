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
	void func_register();
	void locate();
	void clocate();

	Socket* m_server;

public:
	Binder();
	~Binder();

	void start();
	void stop();
};

}



#endif

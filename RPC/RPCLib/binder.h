#ifndef _BINDER_H_
#define _BINDER_H_

#include <map>
#include <string>

namespace rpcLib
{

class Binder : private SocketManager{
private:
	void addSocket();
public:
	Binder();
	~Binder();

	void start();
	void tearDown();
};

}



#endif

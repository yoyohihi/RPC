#include "Socket.h"
#include "debug.h"

using namespace rpcLib;

Socket::Socket()
{

}

Socket::~Socket()
{

}


int Socket::sendInt(int data)
{
	debug(DEBUG,"base socket send");
	return 0;
}

void Socket::sendProtocol(Protocol& p)
{

}

int Socket::receiveInt()
{
	return 0;
}

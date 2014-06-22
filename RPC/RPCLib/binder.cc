#include "binder.h"
#include "debug.h"


using namespace rpcLib;


int main()
{
	Binder* b = new Binder();

	try
	{
		b->start();
	}
	catch(Exception::ConnectionError &e)
	{
		delete b;
		return 0;
	}

	b->tearDown();
	delete b;

	return 0;
}


Binder::Binder()
{

}

Binder::~Binder()
{

}

void Binder::start()
{

}

void Binder::tearDown()
{

}

void Binder::addSocket(Socket* sock)
{

}

void Binder::removeSock(Socket* sock)
{

}


void Binder::registerSock(Socket* sock)
{

}

void Binder::deregisterSock(Socket* sock)
{

}

void Binder::locate(Socket* sock)
{

}

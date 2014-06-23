#include "binder.h"
#include "debug.h"

#include <iostream>

using namespace rpcLib;


Binder::Binder():
m_server(0)
{
	if ((m_server = new ServerSocket()) == NULL)
	{
		debug("not enough memory");
		throw Exception::NullPointerError();
	}
}

Binder::~Binder()
{
	delete m_server;
	m_server = NULL;
}

void Binder::start()
{
	m_server->create_connection();

	std::cout << "BINDER_ADDRESS " << m_server->getHostName() << std::endl;
	std::cout << "BINDER_PORT "    << m_server->getPortNum() << std::endl;


}

void Binder::tearDown()
{

}

void Binder::addSock(Socket* sock)
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

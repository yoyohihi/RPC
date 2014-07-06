#include "SocketManager.h"
#include "debug.h"

#include <vector>

using namespace rpcLib;


SocketManager::SocketManager():
m_curSock(0),
m_curPtr(0)
{

}

SocketManager::~SocketManager()
{

}

void SocketManager::addSock(Socket* sock)
{
	m_manager.push_back(sock);
}

void SocketManager::removeSock(Socket* sock)
{
	for(std::vector<Socket*>::iterator it = m_manager.begin(); it != m_manager.end(); it++)
	{
		if (*it == sock)
		{
			m_manager.erase(it);
			delete sock;
			sock = NULL;
			return;
		}
	}
	debug(DEBUG,"trying to remove a sock that does not reside in vector");
}

Socket* SocketManager::rr_schedule()
{
	int size = m_manager.size();
	if (m_curPtr == size)
	{
		m_curPtr = 0;
	}
	else
	{
		++m_curPtr;
	}

	return m_manager[m_curPtr];
}

#include "SocketManager.h"
#include "debug.h"

#include <vector>
#include <list>
#include "Socket.h"
#include "ClientSocket.h"
#include "StatusCode.h"
#include "Security.h"
#include "Request.h"

using namespace rpcLib;


SocketManager::SocketManager()
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
	debug(ERROR,"trying to remove a sock that does not reside in vector");
}

Socket* SocketManager::rr_schedule(std::vector<Socket*> sock_list)
{
	Socket* victim = sock_list[0];

	return victim;
}

void SocketManager::addDatabase(std::string id, Socket* client)
{
	m_database[id].push_back(client);
}


void SocketManager::addServerSocket(char* id,uint32_t port,std::string addr)
{
	std::map<std::string,std::vector<Socket*> >::iterator it = m_database.find(std::string(id));
	Socket* client = new ClientSocket(port,addr);
	try{
		//client->create_connection();
		addSock(client);
		addDatabase(std::string(id),client);
	}
	catch(...)
	{
		debug(ERROR,"client connection error in sock mgr");
	}
}

void SocketManager::teminate_notifyAll()
{
	Security s;
	Socket* client = NULL;
	int req = s.encrypt(Request::REQ_QUIT);
	int size = m_manager.size();
	for (int i = 0; i < size; ++i)
	{
		client = m_manager[i];
		try
		{
			client->create_connection();
			client->sendInt(req);
		}
		catch(...)
		{
			debug(INFO,"dup connection!");
		}
		delete client;
		client = NULL;
	}
}

int SocketManager::locate_server(char* func_id, uint32_t* port, char* addr)
{
	std::map<std::string,std::vector<Socket*> >::iterator it = m_database.find(std::string(func_id));

	if (it == m_database.end()) // not found
	{
		return Status::FAIL_LOC;
	}

	// return port & address
	// do a round robin scheduling
	std::vector<Socket*> sock_list = it->second;
	Socket* client = rr_schedule(sock_list);

	*port = client->getPortNum();
	const char* hn = client->getHostName().c_str();
	int size = strlen(hn);
	strncpy(addr,hn,size);
	addr[size] = '\0';

	debug(DEBUG,"Locate successfully, get port number %d, server host name %s",*port,addr);

	return Status::SUCCESS;
}

int SocketManager::clocate_server(char* id, std::vector<Socket*> *cache)
{
	std::map<std::string,std::vector<Socket*> >::iterator it = m_database.find(std::string(id));

	if (it == m_database.end())
	{
		return Status::FAIL_LOC;
	}
	else
	{
		*cache = it->second;
		return Status::SUCCESS;
	}

	return 0;
}


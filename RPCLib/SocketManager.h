#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include "Socket.h"



namespace rpcLib
{
class SocketManager
{
private:
	std::vector<Socket*> m_manager;
	std::map<std::string,std::vector<Socket*> > m_database;

	std::list<Socket*> servers;
	std::set<std::pair<Socket*, std::string> > registered;

	void addSock(Socket* sock);
	void addDatabase(std::string id, Socket* client);

	void removeSock(Socket* sock);
	Socket* rr_schedule(std::vector<Socket*> sock_list);
	int rr_schedule(std::string function_name, Socket* target);
public:
	SocketManager();
	~SocketManager();

	void addServerSocket(char* id,uint32_t port, std::string addr);
	void teminate_notifyAll();
	int  locate_server(char* id, uint32_t* port, char* addr);
	int  clocate_server(char* id, std::vector<Socket*> *cache);

};
}

#endif

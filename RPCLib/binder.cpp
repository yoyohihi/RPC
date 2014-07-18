#include "debug.h"
#include "binder.h"
#include "Socket.h"
#include "Const.h"
#include "SocketManager.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Security.h"
#include "Exception.h"
#include "StatusCode.h"
#include "Request.h"

#include <iostream>
#include <sys/types.h>
#include <list>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/unistd.h>

using namespace rpcLib;


Binder::Binder():
m_server(0)
{
	if ((m_server = new ServerSocket()) == NULL)
	{
		debug(ERROR,"not enough memory");
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

	fd_set master,reader;

	FD_ZERO(&master);
	FD_ZERO(&reader);

	int server_fd = m_server->getFileDescriptor();
	int new_fd;

	FD_SET(server_fd,&master);
	int max_fd = server_fd;

	while (1)
	{
		reader = master;
		if (select(max_fd+1,&reader,NULL,NULL,NULL) == -1)
		{
			debug(ERROR,"select error");
		}

		for (int i = 0 ; i <= max_fd; ++i)
		{
			if (FD_ISSET(i,&reader))
			{
				if (i == server_fd)
				{
					struct sockaddr_storage client;
					socklen_t sock_size = sizeof (sockaddr_storage);
					new_fd = accept(server_fd,(struct sockaddr*)&client,&sock_size);
					if (new_fd == -1) debug(ERROR,"accept error");

					FD_SET(new_fd,&master);
					if (new_fd > max_fd) max_fd = new_fd;
					debug(DEBUG,"accepted connection");
				}
				else
				{
					m_server->assignComm(i);
					int request,data;
					data = m_server->receiveInt();
					if (data > 0)
					{
						//int data = s.decrypt(revLen);
						debug(DEBUG,"received request %d",data);

						switch (data)
						{
						case Request::REQ_LOC:
							locate();
							break;
						case Request::REQ_REG:
							func_register();
							break;
						case Request::REQ_QUIT:
							debug(INFO,"Quit singal received!");
							teminate_notifyAll();
							// clean up current function
							return;
						case Request::REQ_CLOC:
							clocate();
							break;
						default:
							throw Exception::UnhandledCaseError();
						}
					}
					else
					{
						close(i);
						FD_CLR(i, &master);
					}


				}
			}
		}
	}
}

void Binder::stop()
{

}


void Binder::func_register()
{
	debug(INFO,"registering function...");
	char* reg_info          = m_server->receiveString(); // function signature
	int server_port         = m_server->receiveInt();    // server port
	char* server_addr       = m_server->receiveString(); // server address

	debug(DEBUG,"binder receives reg info %s",reg_info);
	debug(DEBUG,"binder receives server port %d",server_port);
	debug(DEBUG,"binder receives server addr %s",server_addr);

	std::string addr(server_addr);

	// register
	addServerSocket(reg_info,server_port,addr);

	m_server->sendInt(Status::SUCCESS);

	delete reg_info;
	delete server_addr;
}

void Binder::locate()
{
	debug(INFO,"locating server....");
	char* data_str = m_server->receiveString();

	char addr[Const::maxBuffer];
	uint32_t port;

	int ret = locate_server(data_str,&port,addr);

	if (ret == Status::SUCCESS)
	{
		m_server->sendInt(ret);
		m_server->sendInt(port);
		m_server->sendString(addr);
	}
	else if (ret == Status::FAIL_LOC)
	{
		m_server->sendInt(ret);
	}

	delete data_str;
}

void Binder::clocate()
{
	debug(INFO,"cache locating...");

	char* data = m_server->receiveString();

	std::vector<Socket*> cache;

	int ret = clocate_server(data,&cache);

	if (ret == Status::FAIL_LOC)
	{
		debug(DEBUG,"FAIL TO LOCATE");
		m_server->sendInt(ret);
		return;
	}
	else if (ret == Status::SUCCESS)
	{
		m_server->sendInt(ret);
	}

	// send cache to client

	int size = cache.size();
	debug(INFO,"cache size %d",size);
	m_server->sendInt(size);

	for (int i = 0 ; i < size; ++i)
	{
		Socket* server = cache[i];
		int port         = server->getPortNum();
		std::string addr = server->getHostName();
		m_server->sendInt(port);
		m_server->sendString(addr.c_str());
	}


	delete data;
}

































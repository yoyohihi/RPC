#include "debug.h"
#include "binder.h"
#include "Socket.h"
#include "SocketManager.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Protocol.h"
#include "Security.h"
#include "Exception.h"
#include "StatusCode.h"
#include "Request.h"

#include <iostream>
#include <sys/types.h>
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

	Security s;

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
					debug(DEBUG,"accepted");
				}
				else
				{
					//debug(DEBUG,"retrieving data");
					int request,revLen;
					revLen = recv(i,&request,sizeof(request),0);
					if (revLen > 0)
					{
						int data = s.decrypt(request);
						debug(INFO,"received data %d",data);
						switch (data)
						{
						case Request::REQ_LOC:
							locate(i);
							break;
						case Request::REQ_REG:
							break;
						case Request::REQ_QUIT:
							break;
						case Request::REQ_UNKNOWN:
							break;
						case Request::REQ_CLOC:
							break;
						default:
							throw Exception::UnhandledCaseError();
						}
					}
					else
					{
						// if code runs here, we have to handle failures
					}


				}
			}
		}
	}
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

void Binder::locate(int fd)
{
	debug(INFO,"locating....");
	int ret = Status::SUCCESS;

	send(fd,&ret,sizeof(int),0);
}

































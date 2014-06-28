#include "ServerSocket.h"
#include "debug.h"
#include "Exception.h"
#include "Const.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace rpcLib;



ServerSocket::ServerSocket():
m_port(0),
m_hostName(""),
m_fileDescriptor(0)
{

}

ServerSocket::~ServerSocket()
{
	if (0 != m_fileDescriptor)
	{
		close(m_fileDescriptor);
	}
}

void ServerSocket::create_connection()
{
    struct sockaddr_in server_addr;
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = 0;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    m_fileDescriptor = socket(AF_INET,SOCK_STREAM,0);

    if (m_fileDescriptor > 0)
    {
    	char hostname[Const::maxBuffer];
        if((gethostname(hostname, sizeof hostname)) == -1)
        {
            close(m_fileDescriptor);
            debug("error in getting host name!");
            throw Exception::ConnectionError();
        }
        m_hostName = std::string(hostname);

        if(bind(m_fileDescriptor, (struct sockaddr*)&server_addr, sizeof server_addr))
        {
            close(m_fileDescriptor);
            debug("bind error!");
            throw Exception::ConnectionError();
        }

        if (listen(m_fileDescriptor,Const::maxConns) != 0)
        {
        	close(m_fileDescriptor);
        	debug("listen error!");
        	throw Exception::ConnectionError();
        }

        socklen_t sockLen = sizeof(server_addr);
        if(getsockname(m_fileDescriptor, (struct sockaddr *)&server_addr, &sockLen) == -1)
        {
            close(fileDescriptor);
            debug("error in getting port!");
            throw Exception::ConnectionError();
        }
        m_port = ntohs(server_addr.sin_port);
        debug("server side socket established!, host name: %s ; port: %d",m_hostName.c_str(),server_addr.sin_port);
        return;
    }

    debug("socket error");
    throw Exception::ConnectionError();
}

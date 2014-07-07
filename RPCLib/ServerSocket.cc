#include "ServerSocket.h"
#include "debug.h"
#include "Exception.h"
#include "Const.h"
#include "StatusCode.h"


#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/unistd.h>

using namespace rpcLib;



ServerSocket::ServerSocket():
m_port(0),
m_hostName(""),
m_fileDescriptor(0),
m_accept(0)
{

}

ServerSocket::~ServerSocket()
{
	if (0 != m_accept)
	{
		close(m_accept);
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
            debug(DEBUG,"error in getting host name!");
            throw Exception::ConnectionError();
        }
        m_hostName = std::string(hostname);

        if(bind(m_fileDescriptor, (struct sockaddr*)&server_addr, sizeof server_addr))
        {
            close(m_fileDescriptor);
            debug(DEBUG,"bind error!");
            throw Exception::ConnectionError();
        }

        if (listen(m_fileDescriptor,Const::maxConns) != 0)
        {
        	close(m_fileDescriptor);
        	debug(DEBUG,"listen error!");
        	throw Exception::ConnectionError();
        }

        socklen_t sockLen = sizeof(server_addr);
        if(getsockname(m_fileDescriptor, (struct sockaddr *)&server_addr, &sockLen) == -1)
        {
            close(m_fileDescriptor);
            debug(DEBUG,"error in getting port!");
            throw Exception::ConnectionError();
        }
        m_port = ntohs(server_addr.sin_port);
        debug(INFO,"server side socket established!, host name: %s ; port: %d",m_hostName.c_str(),m_port);
        return;
    }

    debug(ERROR,"server socket error");
    throw Exception::ConnectionError();
}


int ServerSocket::receiveInt()
{
    int bytesRecv;
    uint32_t net_value;

    bytesRecv = recv(m_accept, (void*)&net_value, sizeof(uint32_t), 0);
    if( bytesRecv == 0 )
    {
    	debug(ERROR,"received nothing");
    }

    unsigned int value = ntohl(net_value);
    return value;
}


std::string ServerSocket::getHostName()
{
	return m_hostName;
}

uint32_t ServerSocket::getFileDescriptor()
{
	return m_fileDescriptor;
}

uint32_t ServerSocket::getPortNum()
{
	return m_port;
}






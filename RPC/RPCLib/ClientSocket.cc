#include "ClientSocket.h"
#include "Exception.h"
#include "debug.h"

#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>


using namespace rpcLib;


ClientSocket::ClientSocket():
m_port(0),
m_fileDescriptor(0),
m_hostName("")
{

}

ClientSocket::ClientSocket(uint32_t port, std::string addr):
m_port(port),
m_fileDescriptor(0),
m_hostName(addr)
{

}

ClientSocket::~ClientSocket()
{
	if (0 != m_fileDescriptor)
	{
		close(m_fileDescriptor);
	}
}

std::string ClientSocket::getHostName()
{
	return m_hostName;
}

uint32_t ClientSocket::getFileDescriptor()
{
	return m_fileDescriptor;
}

uint32_t ClientSocket::getPortNum()
{
	return m_port;
}

void ClientSocket::create_connection()
{
	m_fileDescriptor = socket(PF_INET,SOCK_STREAM,0);

	if (m_fileDescriptor > 0)
	{
		struct sockaddr_in info;
		struct hostent* host = gethostbyname(m_hostName.c_str());

		if (host == NULL)
		{
			debug("get a null host!");
			close(m_fileDescriptor);
			throw Exception::ConnectionError();
		}

	    memcpy( &(info.sin_addr), host->h_addr_list[0], host->h_length);
	    info.sin_family = AF_INET;
	    info.sin_port   = htons(m_port);

	    if (connect(m_fileDescriptor, (struct sockaddr *)&info, sizeof(sockaddr_in)) != 0)
	    {
	        close(m_fileDescriptor);
	        debug("connection refused!");
	        throw Exception::ConnectionError();
	    }
	    debug("client side connection successfully");
	    return;
	}
	debug("error on connecting!");
	throw Exception::ConnectionError();
}

void ClientSocket::sendProtocol(Protocol& p)
{

}




















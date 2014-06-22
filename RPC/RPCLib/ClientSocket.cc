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

ClientSocket::~ClientSocket()
{

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

void ClientSocket::connect()
{
	debug("new client calling connect!");
	m_fileDescriptor = socket(PF_INET,SOCK_STREAM,0);

	if (m_fileDescriptor > 0)
	{
		struct sockaddr_in info;
		struct hostent* host = gethostbyname(m_hostName.c_str());

		if (host == NULL)
		{
			debug("get a null host!");
			close(m_fileDescriptor);
			throw Exception::NullPointer();
		}



	}
	debug("error on connecting!");
	throw Exception::SocketError();
}




















#include "ClientSocket.h"
#include "Exception.h"
#include "debug.h"
#include "StatusCode.h"

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

ClientSocket::ClientSocket(uint32_t port, std::string& addr):
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
			debug(ERROR,"get a null host!");
			close(m_fileDescriptor);
			throw Exception::ConnectionError();
		}

	    memcpy( &(info.sin_addr), host->h_addr_list[0], host->h_length);
	    info.sin_family = AF_INET;
	    info.sin_port   = htons(m_port);

	    if (connect(m_fileDescriptor, (struct sockaddr *)&info, sizeof(sockaddr_in)) != 0)
	    {
	        close(m_fileDescriptor);
	        debug(ERROR,"connection refused!");
	        throw Exception::ConnectionError();
	    }
	    debug(INFO,"client side connection successfully! connected to port %d",m_port);
	    return;
	}
	debug(ERROR,"error on connecting!");
	throw Exception::ConnectionError();
}

int ClientSocket::sendString(const char* input)
{
	int size = strlen(input) + 1;

	// first send the length

	if (Status::FAIL_SENT == sendInt(size))
	{
		return Status::FAIL_SENT;
	}

	if (size != send(m_fileDescriptor,(void*)input,size,0))
	{
		debug(ERROR,"client fails to send a string");
		return Status::FAIL_SENT;
	}
	return Status::SUCCESS;
}

int ClientSocket::receiveInt()
{
	int data;
	int len = recv(m_fileDescriptor,(void*)&data,sizeof(int),0);
	if (len <= 0)
	{
		return Status::FAIL_CONNS;
	}

	if (len != sizeof(int))
	{
		debug(ERROR,"data get splitting");
		return Status::FAIL_DATA;
	}
	return data;
}

int ClientSocket::sendInt(int data)
{
	int size = sizeof (int);
	if (size != send(m_fileDescriptor,(void*)&data,sizeof(int),0))
	{
		debug(ERROR,"client fails to send int");
		return Status::FAIL_SENT;
	}

	return Status::SUCCESS;
}

char* ClientSocket::receiveString()
{
	int length = receiveInt();
    if (length == -1) return NULL;

    int byteRecv;
	char* ret = new char[length];
	if (ret != NULL)
	{
		byteRecv = recv(m_fileDescriptor,(void*)ret,length,0);
		if (byteRecv != length)
		{
			debug(ERROR,"did not receive full string");
			delete ret;
			return NULL;
		}

		ret[length-1] = '\0';
		return ret;
	}

	return NULL;
}


int ClientSocket::sendVoid(void* data, int len)
{
	if (Status::FAIL_SENT == sendInt(len))
	{
		return Status::FAIL_SENT;
	}

	if (len != send(m_fileDescriptor,data,len,0))
	{
		debug(ERROR,"client fails to send void data");
		return Status::FAIL_SENT;
	}

	return Status::SUCCESS;

}

void* ClientSocket::receiveVoid()
{
	int len = receiveInt();
	if (len == -1) return NULL;

	int byteRecv;
	void* data = malloc(len);
	if (data != NULL)
	{
		byteRecv = recv(m_fileDescriptor,data,len,0);
		if (byteRecv != len)
		{
			debug(ERROR,"did not receive full void data");
			free(data);
			return NULL;
		}
		return data;
	}

	return NULL;
}



















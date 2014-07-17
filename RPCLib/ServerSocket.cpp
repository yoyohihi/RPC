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
#include <cstdlib>

using namespace rpcLib;



ServerSocket::ServerSocket():
m_port(0),
m_hostName(""),
m_fileDescriptor(0),
m_commSocket(0)
{

}

ServerSocket::ServerSocket(uint32_t port, std::string& addr):
m_port(port),
m_hostName(addr),
m_fileDescriptor(0),
m_commSocket(0)
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
            m_fileDescriptor = 0;
            debug(DEBUG,"error in getting host name!");
            throw Exception::ConnectionError();
        }
        m_hostName = std::string(hostname);

        if(bind(m_fileDescriptor, (struct sockaddr*)&server_addr, sizeof server_addr))
        {
            close(m_fileDescriptor);
            m_fileDescriptor = 0;
            debug(DEBUG,"bind error!");
            throw Exception::ConnectionError();
        }

        if (listen(m_fileDescriptor,Const::maxConns) != 0)
        {
        	close(m_fileDescriptor);
        	m_fileDescriptor = 0;
        	debug(DEBUG,"listen error!");
        	throw Exception::ConnectionError();
        }

        socklen_t sockLen = sizeof(server_addr);
        if(getsockname(m_fileDescriptor, (struct sockaddr *)&server_addr, &sockLen) == -1)
        {
            close(m_fileDescriptor);
            m_fileDescriptor = 0;
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
	int data;
	int len = recv(m_commSocket,(void*)&data,sizeof(int),0);

	if (len <= 0)
	{
		debug(INFO,"seems like client closes the connection");
		return Status::FAIL_CONNS;
	}

	if (len != sizeof(int))
	{
		debug(ERROR,"data get splitting");
		return Status::FAIL_DATA;
	}

	return data;
}

char* ServerSocket::receiveString()
{
	int length = receiveInt();
    if (length == -1) return NULL;

    int byteRecv;
	char* ret = new char[length];
	if (ret != NULL)
	{
		byteRecv = recv(m_commSocket,(void*)ret,length,0);
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

int ServerSocket::sendInt(int data)
{
	int size = sizeof (int);
	if (size != send(m_commSocket,(void*)&data,sizeof(int),0))
	{
		debug(ERROR,"server fails to send int");
		return Status::FAIL_SENT;
	}

	return Status::SUCCESS;
}

int ServerSocket::sendString(const char* c_data)
{
	int size = strlen(c_data) + 1;

	// first send the length

	if (Status::FAIL_SENT == sendInt(size))
	{
		return Status::FAIL_SENT;
	}

	if (size != send(m_commSocket,(void*)c_data,size,0))
	{
		debug(ERROR,"server fails to send a string");
		return Status::FAIL_SENT;
	}

	return Status::SUCCESS;
}

int ServerSocket::sendVoid(void* data, int len)
{
	if (Status::FAIL_SENT == sendInt(len))
	{
		return Status::FAIL_SENT;
	}

	if (len != send(m_commSocket,data,len,0))
	{
		debug(ERROR,"server fails to send void data");
		return Status::FAIL_SENT;
	}

	return Status::SUCCESS;

}

void* ServerSocket::receiveVoid()
{
	int len = receiveInt();
	if (len == -1) return NULL;

	int byteRecv;
	void* data = malloc(len);
	if (data != NULL)
	{
		byteRecv = recv(m_commSocket,data,len,0);
		if (byteRecv != len)
		{
			debug(ERROR,"server did not receive full void data");
			free(data);
			return NULL;
		}
		return data;
	}

	return NULL;
}

int ServerSocket::getServingClient()
{
	return m_commSocket;
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

void ServerSocket::assignComm(int fd)
{
	m_commSocket = fd;
}






#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>
#include <cstdlib>

namespace rpcLib
{

class Socket
{
public:
	Socket();
	virtual ~Socket();

	virtual std::string getHostName()            = 0;
	virtual uint32_t    getPortNum()             = 0;
	virtual uint32_t    getFileDescriptor()      = 0;
	virtual void        create_connection()      = 0;

	virtual int         receiveInt(){return 0;}
	virtual char*       receiveString(){return NULL;}
	virtual void*       receiveVoid(){return NULL;}


	virtual int         sendInt(int data){return 0;}
	virtual int         sendString(const char* data){return 0;}
	virtual int         sendVoid(void* data, int len){return 0;}

	virtual void assignComm(int fd){}
	virtual int  getServingClient(){return 0;}

};

}


#endif

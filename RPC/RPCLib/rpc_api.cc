#include "rpc_lib.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Exception.h"
#include "debug.h"
#include "StatusCode.h"

#include <string>

using namespace rpcLib;



int rpcInit()
{
	char* port    = getenv("BINDER_PORT");
	char* address = getenv("BINDER_ADDRESS");

	if (port && address)
	{
		BinderPort    = atoi(port);
		BinderAddress = std::string(address);
	}
	else
	{
		debug("setup error");
		return Status::FAIL_SETUP;
	}

	Socket* client = new ClientSocket(BinderPort,BinderAddress);
	Socket* server = new ServerSocket();

	try
	{
		client->create_connection();
		server->create_connection();
	}
	catch(Exception::ConnectionError &e)
	{
		delete client;
		delete server;
		return Status::FAIL_CONNS;
	}

	return Status::SUCCESS;
}

int rpcRegister(char* name, int* argTypes, skeleton f)
{

}


int rpcCall(char* name, int* argTypes, void** args)
{
	std::string Hostname = "";
	uint32_t    port     = 0;

	if (BinderAddress == "" || BinderPort == 0)
	{
		return Status::FAIL_SETUP;
	}

	Socket* client = new ClientSocket(BinderAddress,BinderPort);

	try
	{
		client->create_connection();

		Protocol p;
		p.packData(Request::REQ_LOC,name,argTypes);
		client->sendProtocol(p);

	}
	catch(...)
	{

	}
}





int rpcCacheCall(char* name, int* argTypes, void** args);
int rpcExecute();
int rpcTerminate();

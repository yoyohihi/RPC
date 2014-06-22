#include "rpc_lib.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Exception.h"
#include "debug.h"
#include "StatusCode.h"

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

	}



}



int rpcCall(char* name, int* argTypes, void** args);
int rpcCacheCall(char* name, int* argTypes, void** args);
int rpcRegister(char* name, int* argTypes, skeleton f);
int rpcExecute();
int rpcTerminate();

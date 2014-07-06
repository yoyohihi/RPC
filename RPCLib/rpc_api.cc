#include "Socket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Exception.h"
#include "Protocol.h"
#include "Security.h"
#include "debug.h"
#include "StatusCode.h"
#include "Const.h"
#include "Request.h"
#include "binder.h"
#include "rpc_args.h"
#include "Config.h"

#include <string>

using namespace rpcLib;

typedef int (*skeleton)(int *, void **);

int rpcInit()
{
	char* port    = getenv("BINDER_PORT");
	char* address = getenv("BINDER_ADDRESS");

	if (port && address)
	{
		Config::BinderPort    = atoi(port);
		Config::BinderAddress = std::string(address);
	}
	else
	{
		debug(ERROR,"setup error");
		return Status::FAIL_SETUP;
	}

	Config::m_BinderClient = new ClientSocket(Config::BinderPort,Config::BinderAddress);

	try
	{
		Config::m_BinderClient->create_connection();
	}
	catch(Exception::ConnectionError &e)
	{
		delete Config::m_BinderClient;
		return Status::FAIL_CONNS;
	}

	return Status::SUCCESS;
}

int rpcRegister(char* name, int* argTypes, skeleton f)
{
	if (NULL == Config::m_BinderClient)
	{
		return Status::FAIL_SETUP;
	}

	try
	{
		std::string reg = argTypes::deSugar(std::string(name),argTypes);
		debug(DEBUG,"Registering %s in Binder!",reg.c_str());


	}
	catch(...)
	{

	}

	return Status::SUCCESS;
}


int rpcCall(char* name, int* argTypes, void** args)
{
	std::string Hostname = "";
	uint32_t    port     = 0;

	int result;

	if (Config::BinderAddress == "" || Config::BinderPort == 0)
	{
		return Status::FAIL_SETUP;
	}

	if (NULL == Config::m_BinderClient)
	{
		return Status::FAIL_SETUP;
	}

	Security s;
	Socket* client = new ClientSocket(Config::BinderPort,Config::BinderAddress);

	try
	{
		client->create_connection();

		int req = Request::REQ_LOC;
		client->sendInt(s.encrypt(req));

		result = client->receiveInt();

		debug(INFO,"client returned value %d",result);



	}
	catch(...)
	{
		debug(ERROR,"returned from exception");
		return -1;
	}

	return Status::SUCCESS;
}





int rpcCacheCall(char* name, int* argTypes, void** args);
int rpcExecute();
int rpcTerminate();

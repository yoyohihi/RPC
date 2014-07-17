#include "Socket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "Exception.h"
#include "Security.h"
#include "debug.h"
#include "StatusCode.h"
#include "Const.h"
#include "Request.h"
#include "binder.h"
#include "rpc_args.h"
#include "Config.h"
#include "api_header.h"
#include "Util.h"

#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <pthread.h>
#include <time.h>

using namespace rpcLib;

static int sendRequestToServer(std::string& func, Socket* client, int* argTypes, void** args ,int argLen);

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
	Config::m_BinderServer = new ServerSocket();

	try
	{
		Config::m_BinderClient->create_connection();
		Config::m_BinderServer->create_connection();
	}
	catch(Exception::ConnectionError &e)
	{
		delete Config::m_BinderClient;
		delete Config::m_BinderServer;
		Config::m_BinderClient = NULL;
		Config::m_BinderServer = NULL;

		return Status::FAIL_CONNS;
	}

	Config::done_setup_server = 1;
	debug(DEBUG,"rpc init successfully!");
	return Status::SUCCESS;
}


int rpcRegister(char* name, int* argTypes, skeleton f)
{
	int result = Status::FAIL_REG;
	if (1 != Config::done_setup_server)
	{
		return result;
	}

	int req,argLen;
	try
	{
		std::string reg = argTypes::getFuncSignature(name,argTypes,&argLen);

		req = Request::REQ_REG;
		Config::m_BinderClient->sendInt(req);
		Config::m_BinderClient->sendString(reg.c_str());
		debug(DEBUG,"Registering %s in Binder!",reg.c_str());

		// sending server port & address
		Config::m_BinderClient->sendInt(Config::m_BinderServer->getPortNum());
		Config::m_BinderClient->sendString(Config::m_BinderServer->getHostName().c_str());

		// get result;
		result = Config::m_BinderClient->receiveInt();
		if (result == Status::SUCCESS_WARNING)
		{
			debug(INFO,"Warning: duplicated function reg");
			return Status::SUCCESS_WARNING;
		}

		// register it in local server database
		Config::func_database[reg] = f;
	}
	catch(...)
	{
		return Status::FAIL_REG;
	}

	return Status::SUCCESS;
}


int rpcCall(char* name, int* argTypes, void** args)
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

	int result,req;
	int argLen;

	Socket* client = new ClientSocket(Config::BinderPort,Config::BinderAddress);
	std::string toSend = argTypes::getFuncSignature(name,argTypes,&argLen);

	try
	{
		client->create_connection();

		// firstly, locate the server via binder
		req = Request::REQ_LOC;
		client->sendInt(req);
		client->sendString(toSend.c_str());


		// get reply from binder
		result = client->receiveInt();

		if (result == Status::SUCCESS)
		{
			// receive server port and server address;
			uint32_t server_port            = client->receiveInt();
			const char* server_address      = client->receiveString();
			std::string in(server_address);

			if (server_address)
			{
				delete client; // delete the connection with binder
				client = new ClientSocket(server_port,in); // new connection with server

				delete server_address;
				server_address = NULL;

				client->create_connection();

				return sendRequestToServer(toSend,client,argTypes,args,argLen);
			}
		}
		else if (result == Status::FAIL_LOC)
		{
			debug(ERROR,"binder failed to locate server!");
			goto f1;
		}
		else
		{
			debug(ERROR,"an unknown result received, it is %d",result);
			goto f1;
		}
	}
	catch(...)
	{
		debug(ERROR,"returned from exception");
        return -1;
	}

f1:	Config::done_setup_client = 1;
	return result;
}

static void handle_request()
{
	debug(INFO,"server is handling request!");
	// first receive function signature
	char* func_id = Config::m_BinderServer->receiveString();
	int argLen    = Config::m_BinderServer->receiveInt();

	std::string func(func_id);
	delete func_id;
	func_id = NULL;

	// receive argTypes
	int* argTypes = (int*)malloc(sizeof(int)*(argLen+1));

	int i;
	for (i = 0 ; i < argLen; ++i)
	{
		int single_type = Config::m_BinderServer->receiveInt();
		argTypes[i] = single_type;
	}
	argTypes[i] = 0;

	// argTypes finished!
	// receive arguments

	void** args = (void**)malloc(argLen * sizeof(void*));

	for (i = 0; i < argLen ; ++i)
	{
		void* arg = Config::m_BinderServer->receiveVoid();
		if (arg == NULL)
		{
			debug(ERROR,"server receives null pointer!");
		}
		*(args+i) = arg;
	}

	// run it at background as we dont know how long it will process
	addNewBacklog(func,argTypes,args,Config::m_BinderServer->getServingClient());

	debug(DEBUG,"backlog added!");

	// reply client as EXEC_IN_PROCESS
	Config::m_BinderServer->sendInt(Status::EXEC_IN_PROCESS);
}

void sendResultToClient(thread_worker* worker)
{
	int ret_code = worker->ret_code;

	Config::m_BinderServer->assignComm(worker->client);

	if (Status::SUCCESS == ret_code)
	{
		Config::m_BinderServer->sendInt(Status::SUCCESS);
		// success
		int* argTypes = worker->argTypes;
		void** args = worker->args;
		for (int i = 0 ; argTypes[i] != 0 ; ++i)
		{
			// send size
			int arr_len;
			int size;
			if (argTypes::isArray(argTypes[i],&arr_len))
			{
				size = arr_len * argTypes::getTypeSize(argTypes::t2s(argTypes::getType(argTypes[i])));
			}
			else
			{
				size = argTypes::getTypeSize(argTypes::t2s(argTypes::getType(argTypes[i])));
			}
			debug(INFO,"server has sent %d to client as the %d argument!",size,i);

			Config::m_BinderServer->sendVoid(args[i],size);
		}

		// clean up
		for (int i = 0 ; argTypes[i] != 0 ; ++i)
		{
			free(args[i]);
		}
		free(argTypes);
		debug(INFO,"server is done");
	}
	else if (Status::FAIL_EXEC == ret_code)
	{
		Config::m_BinderServer->sendInt(Status::FAIL_EXEC);
	}
}


int rpcExecute()
{
	if (Config::done_setup_server != 1)
	{
		return Status::FAIL_SETUP;
	}

	fd_set master,reader;

	FD_ZERO(&master);
	FD_ZERO(&reader);

	int server_fd = Config::m_BinderServer->getFileDescriptor();
	int new_fd;

	FD_SET(server_fd,&master);
	int max_fd = server_fd;

	Security s;
	const int encrypt_quit = s.encrypt(Request::REQ_QUIT);

	std::vector<thread_worker*>::iterator it;

	struct timeval tv = {2, 0}; // set timeout

	while (1)
	{
		reader = master;
		if (select(max_fd+1,&reader,NULL,NULL,&tv) == -1)
		{
			debug(ERROR,"select error");
		}

		begin:
		// we scan through all the backlog to see if any task has been finished!
		for (it = Config::backlog.begin() ; it != Config::backlog.end(); ++it)
		{
			thread_worker* worker = *it;
			if (worker->ret_code != -2)
			{
				debug(INFO,"prepare to send result!");
				// finish!
				sendResultToClient(worker);
				delete worker;
				worker = NULL;
				Config::backlog.erase(it);
				debug(DEBUG,"server deletes backlog");
				goto begin;
			}
		}


		for (int i = 0 ; i <= max_fd; ++i)
		{
			if (FD_ISSET(i,&reader))
			{
				if (i == server_fd)
				{
					struct sockaddr_storage client;
					socklen_t sock_size = sizeof (sockaddr_storage);
					new_fd = accept(server_fd,(struct sockaddr*)&client,&sock_size);
					if (new_fd == -1) debug(ERROR,"accept error");

					FD_SET(new_fd,&master);
					if (new_fd > max_fd) max_fd = new_fd;
					debug(DEBUG,"accepted connection");
				}
				else
				{
					Config::m_BinderServer->assignComm(i);
					int req = Config::m_BinderServer->receiveInt();

					if (req < 0)
					{
						debug(INFO,"connection closed!");
						close(i);
						FD_CLR(i, &master);
						continue;
					}

					if (req == encrypt_quit)
					{
						// only binder will send encrypted quit command to server
						// if client sends a quit command to server, server will ignore it.
						debug(INFO,"Verified, the quit command came from binder!");
					    debug(INFO,"cleaning up...");
						goto done;
					}
					else if (req == Request::REQ_EXEC)
					{
						handle_request();
					}
					else
					{
						debug(INFO,"server gets a cracked request, it is %d",req);
					}
				}
			}
		} // end for loop
	}

done:
    // if at this point, we still have backlogs, we must terminate them and send a failure signal to client
	for (it = Config::backlog.begin() ; it != Config::backlog.end(); ++it)
	{
		thread_worker* worker = *it;
		if (worker->ret_code == -2)
		{
			worker->ret_code = Status::FAIL_EXEC;
		}
		sendResultToClient(worker);
		delete worker;
		worker = NULL;
	}
	Config::backlog.clear();

	delete Config::m_BinderClient;
	delete Config::m_BinderServer;
	Config::m_BinderClient = NULL;
	Config::m_BinderServer = NULL;

	Config::BinderAddress = "";
	Config::BinderPort    = 0;

	Config::func_database.clear();

	return Status::SUCCESS;
}


int rpcTerminate()
{
	if (Config::done_setup_client != 1)
	{
		return Status::FAIL_SETUP;
	}

	int req = Request::REQ_QUIT;
	int result;

	Socket* client = new ClientSocket(Config::BinderPort,Config::BinderAddress);

	try
	{
		client->create_connection();
		client->sendInt(req);

		result = client->receiveInt();
	}
	catch(...)
	{

	}

	delete client;
	client = NULL;

	return result;
}

void* worker(void* in)
{
	thread_worker* backlog = (thread_worker*)(in);

	backlog->ret_code = Config::func_database[backlog->func](backlog->argTypes,backlog->args);

	debug(INFO,"worker finishes,ret code %d",backlog->ret_code);

	pthread_exit(NULL);
}


int addNewBacklog(std::string& func, int* argTypes, void** args, int client)
{
	pthread_t t1;

	thread_worker* in = new thread_worker(client,func,argTypes,args);
	Config::backlog.push_back(in);

	pthread_create(&t1,NULL,worker,(void*)in);


	return Status::SUCCESS;
}


int rpcCacheCall(char* name, int* argTypes, void** args)
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

	int result,req;
	int argLen;

	Socket* client = NULL;

	std::string toSend = argTypes::getFuncSignature(name,argTypes,&argLen);


	exec:
	// search from local cache
	std::map<std::string, std::vector<Socket*> >::iterator it = Config::cache.find(toSend);

	if (it != Config::cache.end())
	{
		debug(INFO,"found a local cache!");
		// found!
		std::vector<Socket*> server_list = it->second;

		re_search:
		int server_cnt = server_list.size();

		for (int i = 0 ; i < server_cnt; ++i)
		{
			Socket* victim          = server_list[i];
			int server_port         = victim->getPortNum();
			std::string server_addr = victim->getHostName();

			client = new ClientSocket(server_port,server_addr);

			try
			{
				client->create_connection();
			}
			catch(...)
			{
				// if server fails to connect, code goes here.
				debug(DEBUG,"server has closed the connection, trying to fins other one...");
				// delete the server, and try to find another one
				server_list.erase(server_list.begin() + i);
				goto re_search;
			}

			// if code goes here, we established the connection successfully
			return sendRequestToServer(toSend,client,argTypes,args,argLen);

		}

	}

	debug(INFO,"no local cache found");

	// if there is nothing in local cache, we send a request to binder
	client = new ClientSocket(Config::BinderPort,Config::BinderAddress);

	try
	{
		client->create_connection();

		req = Request::REQ_CLOC;
		client->sendInt(req);
		client->sendString(toSend.c_str());

		result = client->receiveInt();

		if (result == Status::SUCCESS)
		{
			// get the cache

			debug(INFO,"successfully located!");
			// first get the len of list of servers
			int len = client->receiveInt();

			for (int i = 0 ; i < len ; ++i)
			{
				debug(INFO,"adding server...");
				// receive port & addr pair
				int port   = client->receiveInt();
				char* addr = client->receiveString();

				debug(INFO,"adding cache... port %d, addr %s",port,addr);

				std::string in(addr);

				Socket* server = new ServerSocket(port,in);
				delete addr;

				Config::cache[toSend].push_back(server);
			}

		}
		else if (result == Status::FAIL_LOC)
		{
			delete client;
			return result;
		}
	}
	catch(...)
	{
		delete client;
		return Status::FAIL_LOC;
	}

	delete client;
	client = NULL;

	goto exec;

}


static int sendRequestToServer(std::string& func, Socket* client, int* argTypes, void** args, int argLen)
{
	int req,result;

	//prepare execution argument
	//first send func signature
	req = Request::REQ_EXEC;
	client->sendInt(req);
	client->sendString(func.c_str());

	debug(DEBUG,"sent sig");

	// send len of args
	client->sendInt(argLen);

	// send argsTypes
	for (int i = 0 ; i < argLen ; ++i)
	{
		client->sendInt(argTypes[i]);
	}

	// send input
	for (int i = 0 ; i < argLen ; ++i)
	{
		// send size
		int arr_len;
		int size;
		if (argTypes::isArray(argTypes[i],&arr_len))
		{
			size = arr_len * argTypes::getTypeSize(argTypes::t2s(argTypes::getType(argTypes[i])));
		}
		else
		{
			size = argTypes::getTypeSize(argTypes::t2s(argTypes::getType(argTypes[i])));
		}
		debug(INFO,"client has sent %d to server as the %d argument!",size,i);

		client->sendVoid(args[i],size);
	}

	result = client->receiveInt();

	if (result == Status::EXEC_IN_PROCESS)
	{
		debug(DEBUG,"IN PROCESS");
		// block here, wait for result
		result = client->receiveInt();
		if (result == Status::SUCCESS)
		{
			debug(DEBUG,"Receive result");
			// copy content
			for (int i = 0 ; i < argLen; ++i)
			{
				void* ret_arg = client->receiveVoid();
				args[i] = ret_arg;
			}



		}
		else if (result == Status::FAIL_EXEC)
		{
			debug(INFO,"server fails to execute the function!");
		}
		else
		{
			debug(ERROR,"received an unknown status code, it is %d",result);
		}
	}

	delete client;
	client = NULL;
	return result;

}


















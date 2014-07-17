#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef int (*skeleton)(int *, void **);

#include <map>
#include "api_header.h"
#include <vector>

namespace rpcLib
{
	class Socket;
	namespace Config
	{
		// binder port & address
		uint32_t BinderPort;
		std::string BinderAddress;

		// server side comm
		Socket* m_BinderClient;
		Socket* m_BinderServer;

		//server side database
		std::map<std::string,skeleton> func_database; //< {key,value} = {func_signature,func_name}
		//server side backlog

		// setup
		int done_setup_server;
		int done_setup_client;

		// backlog
		std::vector<thread_worker*> backlog;

		// quit request
		volatile int quit_signal;

		// client side cache
		std::map<std::string,std::vector<Socket*> > cache;
	}
}

#endif

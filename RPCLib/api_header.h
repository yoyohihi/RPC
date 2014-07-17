#ifndef _API_
#define _API_


struct thread_worker
{
	thread_worker(int m_client, std::string& m_func,int* m_argTypes, void** m_args)
	{
		client = m_client;
		ret_code = -2;
		args = m_args;
		argTypes = m_argTypes;
		func = m_func;
	}
	int client;
	volatile int ret_code;
	void** args;
	int*   argTypes;
	std::string func;
};


typedef int (*skeleton)(int *, void **);

int rpcInit();
int rpcCall(char* name, int* argTypes, void** args);
int rpcCacheCall(char* name, int* argTypes, void** args);
int rpcRegister(char* name, int* argTypes, skeleton f);
int rpcExecute();
int rpcTerminate();

int addNewBacklog(std::string& func, int* argTypes, void** args, int client);
void* worker(void* in);

#endif

#ifndef _CONFIG_H_
#define _CONFIG_H_



namespace rpcLib
{
	namespace Config
	{
		// binder port & address
		uint32_t BinderPort;
		std::string BinderAddress;

		// pipes
		Socket* m_BinderClient;
	}
}

#endif

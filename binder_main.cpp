#include "RPCLib/binder.h"
#include "RPCLib/Exception.h"


using namespace rpcLib;

int main()
{
	Binder b;

	try
	{
		b.start();
	}
	catch(Exception::ConnectionError &e)
	{
		return 0;
	}

	b.stop();

	return 0;
}

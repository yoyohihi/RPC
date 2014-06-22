#include "binder.h"
#include "Exception.h"


using namespace rpcLib;

int main()
{
	Binder* b = new Binder();

	try
	{
		b->start();
	}
	catch(Exception::ConnectionError &e)
	{
		delete b;
		return 0;
	}

	b->tearDown();
	delete b;

	return 0;
}

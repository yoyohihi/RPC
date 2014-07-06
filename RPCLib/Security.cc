#include "debug.h"
#include "Security.h"

using namespace rpcLib;

Security::Security():
hashVal(188)
{

}

Security::~Security()
{

}

int Security::encrypt(int data)
{
	return data*10+hashVal;
}

int Security::decrypt(int data)
{
	return (data-hashVal) / 10;
}

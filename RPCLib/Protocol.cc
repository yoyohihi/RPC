#include "Protocol.h"
#include "debug.h"
#include "Request.h"
#include "Exception.h"

#include <cstdlib>
#include <cstring>

using namespace rpcLib;


Protocol::Protocol():
m_request(Request::REQ_UNKNOWN),
m_name(0),
m_type(0)
{
}

Protocol::Protocol(int request,char* name, int* type):
m_request(request),
m_name(name),
m_type(type)
{
	if (m_name == NULL || m_type == NULL || m_request == Request::REQ_UNKNOWN)
	{
		debug(ERROR,"protocol setup error");
		throw Exception::ProtocolError();
	}
}

Protocol::Protocol(int request):
m_request(request)
{
	m_name = 0;
	m_type = 0;
}

Protocol::~Protocol()
{

}

int* Protocol::getType()
{
	return m_type;
}

int Protocol::getRequest()
{
	return m_request;
}

char* Protocol::getName()
{
	return m_name;
}

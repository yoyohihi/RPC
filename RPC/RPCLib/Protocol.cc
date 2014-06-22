#include "protocol.h"
#include "debug.h"

#include <cstdlib>
#include <cstring>

using namespace rpcLib;


Protocol::Protocol():
m_length(0),
m_data(NULL),
m_type(argTypes::ARG_UNKNOWN)
{
}

Protocol::~Protocol()
{
	if (m_data)
	{
		debug("deleting protocol data");
		delete []m_data;
	}
	m_data = NULL;
}

void Protocol::addData(double toAdd)
{
	debug("protocol adding double!");
	m_type   = argTypes::ARG_DOUBLE;
	m_length = (sizeof toAdd);
	debug("data length %d",m_length);
	if ((m_data = new char[m_length]) != NULL)
	{
		memcpy(m_data,(void*)&toAdd,m_length);
		return;
	}
	debug("error return!");
}

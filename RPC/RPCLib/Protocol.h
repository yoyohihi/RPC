#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "rpc_lib.h"

namespace rpcLib
{

class Protocol {
public:
	Protocol();
	~Protocol();

	void addData(float toAdd);
	void addData(double toAdd);
	void addData(unsigned long toAdd);
	void addData(unsigned long long toAdd);
private:
	argTypes::argType        m_type;
	size_t                   m_length;
	unsigned char*           m_data;
};
}


#endif

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

namespace rpcLib
{

class Protocol {
public:
	Protocol();
	Protocol(int request, char* name, int* type);
	~Protocol();

	int*  getType();
	int   getRequest();
	char* getName();
private:
	int*     m_type;
	int      m_request;
	char*    m_name;
};
}


#endif

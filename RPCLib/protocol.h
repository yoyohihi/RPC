#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

namespace rpcLib
{

class Protocol {
public:
	Protocol();
	Protocol(int request,char* name, int* types);
	Protocol(int request);
	~Protocol();

	int   getRequest();
	int*  getType();
	char* getName();
private:
	int                      m_request;
	int*                     m_type;
	char*                    m_name;
};
}


#endif

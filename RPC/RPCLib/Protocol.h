#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

namespace rpcLib
{

class Protocol {
public:
	Protocol();
	~Protocol();

	void packData(int request, char* name, int* type);
private:
	argTypes::argType        m_type;
	size_t                   m_length;
	unsigned char*           m_data;
};
}


#endif

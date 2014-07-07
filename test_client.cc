

#include <cstdlib>

extern int rpcCall(char* name,int* type, void** data);

int main()
{
	void *data[2] = {(NULL),(NULL)};

	rpcCall("test",NULL,data);

	return 0;
}

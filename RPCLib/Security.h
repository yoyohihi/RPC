#ifndef _SECURITY_H_
#define _SECURITY_H_


namespace rpcLib
{
	class Security
	{
	public:
		Security();
		~Security();

		int encrypt(int data);
		int decrypt(int data);
	private:
		const int hashVal;
	};
}


#endif

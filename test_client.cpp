

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#define ARG_CHAR    1
#define ARG_SHORT   2
#define ARG_INT     3
#define ARG_LONG    4
#define ARG_DOUBLE  5
#define ARG_FLOAT   6

#define ARG_INPUT   31
#define ARG_OUTPUT  30


typedef int (*skeleton)(int *, void **);

extern int rpcInit();
extern int rpcCall(char* name, int* argTypes, void** args);
extern int rpcCacheCall(char* name, int* argTypes, void** args);
extern int rpcRegister(char* name, int* argTypes, skeleton f);
extern int rpcExecute();
extern int rpcTerminate();

#define CHAR_ARRAY_LENGTH 100

int main() {
	long a3[11] = {11, 109, 107, 105, 103, 101, 102, 104, 106, 108, 110};
	int count3 = 1;
	int argTypes3[count3 + 1];
	void **args3;

	argTypes3[0] = (1 << ARG_OUTPUT) | (1 << ARG_INPUT) | (ARG_LONG << 16) | 11;
	argTypes3[1] = 0;

	args3 = (void **)malloc(count3 * sizeof(void *));
	args3[0] = (void *)a3;

	int count = 5;

	// Call f3 on server1
	while(count--) {
		int s3 = rpcCacheCall("f3", argTypes3, args3);
		/* test the return of f3 */
		printf(
			"\nEXPECTED return of f3 is: 110 109 108 107 106 105 104 103 102 101 11\n"
		);

		if (s3 >= 0) {
			printf("ACTUAL return of f3 from server1 is: ");
			int i;
			for (i = 0; i < 11; i++) {
				printf(" %ld", *(((long *)args3[0]) + i));
			}
			printf("\n");
		}
		else {
			printf("Error: %d\n", s3);
		}
	}
}

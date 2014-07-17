// Test rpcCacheCall
// Steps:
// 1. Start server1
// 2. Start client7 which calls f3 shared by server1 and server2
// 3. Stop server1
// 4. Start server2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../rpc.h"
#include "../client.h"

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

	// Wait 15 seconds before making another call to f3 on server2
	usleep(15 * 1000);

	int s3 = rpcCacheCall("f3", argTypes3, args3);
	/* test the return of f3 */
	printf(
		"\nEXPECTED return of f3 from server2 is: 11 101 102 103 104 105 106 107 108 109 110\n"
	);

	if (s3 >= 0) {
		printf("ACTUAL return of f3 is: ");
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
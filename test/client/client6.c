// Test against server1 and server2. server2 should be started after server1.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"
#include "../client.h"

void test_function_overload() {
	/* prepare the arguments for f2 */
	float a2 = 3.14159;
	double b2 = 1234.1001;
	int count2 = 3;
	char *return2 = (char *)malloc(CHAR_ARRAY_LENGTH * sizeof(char));
	int argTypes2[count2 + 1];
	void **args2;

	argTypes2[0] = (1 << ARG_OUTPUT) | (ARG_CHAR << 16) | CHAR_ARRAY_LENGTH;
	argTypes2[1] = (1 << ARG_INPUT) | (ARG_FLOAT << 16);
	argTypes2[2] = (1 << ARG_INPUT) | (ARG_FLOAT << 16);
	argTypes2[3] = 0;

	args2 = (void **)malloc(count2 * sizeof(void *));
	args2[0] = (void *)return2;
	args2[1] = (void *)&a2;
	args2[2] = (void *)&b2;

	int s2 = rpcCall("f2", argTypes2, args2);
	/* test the return of f2 */
	printf("\nEXPECTED return of f2 is: 31235\n"); // The last digit is 5 instead of 4
	if (s2 >= 0) {
		printf("ACTUAL return of f2 is: %s\n", (char *)args2[0]);
	}
	else {
		printf("Error: %d\n", s2);
	}
}

void test_round_robin_call() {
	long a3[11] = {11, 109, 107, 105, 103, 101, 102, 104, 106, 108, 110};
	int count3 = 1;
	int argTypes3[count3 + 1];
	void **args3;

	argTypes3[0] = (1 << ARG_OUTPUT) | (1 << ARG_INPUT) | (ARG_LONG << 16) | 11;
	argTypes3[1] = 0;

	args3 = (void **)malloc(count3 * sizeof(void *));
	args3[0] = (void *)a3;

	// First hit server1 by calling f4
	char *a4 = "non_exist_file_to_be_printed";
	int count4 = 1;
	int argTypes4[count4 + 1];
	void **args4;

	argTypes4[0] = (1 << ARG_INPUT) | (ARG_CHAR << 16) | strlen(a4);
	argTypes4[1] = 0;

	args4 = (void **)malloc(count4 * sizeof(void *));
	args4[0] = (void *)a4;

	int s4 = rpcCall("f4", argTypes4, args4);

	if (s4 == 0) {
		printf("%s\n", "ERROR: incorrect return value of f4");
	}

	int nCalls = 4;
	int state = 2;

	// f3 on server2 should be selected since server1 was selected when calling f4
	// Assume that the other client are not active between these calls
	while(nCalls--) {
		int s3 = rpcCall("f3", argTypes3, args3);

		int head;
		switch (state) {
			case 0:
				head = *((long *)args3[0]);
				state = (head == 11 ? 1 : 2); // 1 for server1 and two for server2 
			break;
			case 1:
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
				state = 2;
			break;
			case 2:
				printf(
					"\nEXPECTED return of f3 is: 11 101 102 103 104 105 106 107 108 109 110\n"
				);

				if (s3 >= 0) {
					printf("ACTUAL return of f3 server2 is: ");
					int i;
					for (i = 0; i < 11; i++) {
						printf(" %ld", *(((long *)args3[0]) + i));
					}
					printf("\n");
				}
				else {
					printf("Error: %d\n", s3);
				}
				state = 1;
			break;
			default:
				printf("Invalid state!\n");
			break;
		}
	}
}

void test_overload_function() {
	short input[1] = {2};
	short output[2] = {1, 1};
	int count = 2;

	int argTypes[count + 1];
	argTypes[0] = (1 << ARG_INPUT) | (ARG_SHORT << 16) | 1;
	argTypes[1] = (1 << ARG_OUTPUT) | (ARG_SHORT << 16) | 2;
	argTypes[2] = 0;

	void **args;
	args = (void **)malloc(count * sizeof(void *));
	args[0] = (void *)input;
	args[1] = (void *)output;

	int s = rpcCall("f20", argTypes, args);
	/* test the return of f5 */
	printf(
	  "\nEXPECTED return of f20 is: 3 3\n"
	);

	if (s >= 0) {
	  printf("ACTUAL return of f20 is: ");
	  int i;
	  for (i = 0; i < 2; i++) {
	    printf(" %hd", *(((short *)args[1]) + i));
	  }
	  printf("\n");
	}
	else {
	  printf("Error: %d\n", s);
	}
}

int main() {
	test_function_overload();
	test_round_robin_call();
	test_overload_function();
	graceful_exit();
}
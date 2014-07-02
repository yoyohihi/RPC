/*
 * client.c
 *
 * This file is the client program,
 * which prepares the arguments, calls "rpcCall", and checks the returns.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rpc.h"

#define CHAR_ARRAY_LENGTH 100

void test_f5() {
  /* prepare the arguments for f5 */
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

  int s = rpcCall("f5", argTypes, args);
  /* test the return of f5 */
  printf(
    "\nEXPECTED return of f5 is: 2 2\n"
  );

  if (s >= 0) {
    printf("ACTUAL return of f5 is: ");
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

void test_f6() {
  /* prepare the arguments for f6 */
  double output;
  int count = 1;

  int argTypes[count + 1];
  argTypes[0] = (1 << ARG_OUTPUT) | (ARG_DOUBLE << 16);
  argTypes[1] = 0;

  void **args;
  args = (void **)malloc(count * sizeof(void *));
  args[0] = (void *)&output;

  int s = rpcCall("f6", argTypes, args);
  /* test the return of f5 */
  printf(
    "\nEXPECTED return of f6 is: 3.14159265359\n"
  );

  if (s >= 0) {
    printf("ACTUAL return of f6 is: ");
    printf("%f\n", *((double*)args));
    printf("\n");
  }
  else {
    printf("Error: %d\n", s);
  }
}

void test_f7() {
  /* prepare the arguments for f7 */
  int count = 0;

  int argTypes[count + 1];
  argTypes[0] = 0;

  void **args;
  args = (void **)malloc(count * sizeof(void *));

  int s = rpcCall("f7", argTypes, args);
  /* test the return of f5 */
  printf(
    "\nEXPECTED return of f7 is: \n"
  );

  if (s >= 0) {
    printf("ACTUAL return of f7 is: ");
    printf("\n");
  }
  else {
    printf("Error: %d\n", s);
  }  
}

int main() {

  /* prepare the arguments for f0 */
  int a0 = 5;
  int b0 = 10;
  int count0 = 3;
  int return0;
  int argTypes0[count0 + 1];
  void **args0;

  argTypes0[0] = (1 << ARG_OUTPUT) | (ARG_INT << 16);
  argTypes0[1] = (1 << ARG_INPUT) | (ARG_INT << 16);
  argTypes0[2] = (1 << ARG_INPUT) | (ARG_INT << 16);
  argTypes0[3] = 0;

  args0 = (void **)malloc(count0 * sizeof(void *));
  args0[0] = (void *)&return0;
  args0[1] = (void *)&a0;
  args0[2] = (void *)&b0;

  /* prepare the arguments for f1 */
  char a1 = 'a';
  short b1 = 100;
  int c1 = 1000;
  long d1 = 10000;
  int count1 = 5;
  long return1;
  int argTypes1[count1 + 1];
  void **args1;

  argTypes1[0] = (1 << ARG_OUTPUT) | (ARG_LONG << 16);
  argTypes1[1] = (1 << ARG_INPUT) | (ARG_CHAR << 16);
  argTypes1[2] = (1 << ARG_INPUT) | (ARG_SHORT << 16);
  argTypes1[3] = (1 << ARG_INPUT) | (ARG_INT << 16);
  argTypes1[4] = (1 << ARG_INPUT) | (ARG_LONG << 16);
  argTypes1[5] = 0;

  args1 = (void **)malloc(count1 * sizeof(void *));
  args1[0] = (void *)&return1;
  args1[1] = (void *)&a1;
  args1[2] = (void *)&b1;
  args1[3] = (void *)&c1;
  args1[4] = (void *)&d1;

  /* prepare the arguments for f2 */
  float a2 = 3.14159;
  double b2 = 1234.1001;
  int count2 = 3;
  char *return2 = (char *)malloc(CHAR_ARRAY_LENGTH * sizeof(char));
  int argTypes2[count2 + 1];
  void **args2;

  argTypes2[0] = (1 << ARG_OUTPUT) | (ARG_CHAR << 16) | CHAR_ARRAY_LENGTH;
  argTypes2[1] = (1 << ARG_INPUT) | (ARG_FLOAT << 16);
  argTypes2[2] = (1 << ARG_INPUT) | (ARG_DOUBLE << 16);
  argTypes2[3] = 0;

  args2 = (void **)malloc(count2 * sizeof(void *));
  args2[0] = (void *)return2;
  args2[1] = (void *)&a2;
  args2[2] = (void *)&b2;

  /* prepare the arguments for f3 */
  long a3[11] = {11, 109, 107, 105, 103, 101, 102, 104, 106, 108, 110};
  int count3 = 1;
  int argTypes3[count3 + 1];
  void **args3;

  argTypes3[0] = (1 << ARG_OUTPUT) | (1 << ARG_INPUT) | (ARG_LONG << 16) | 11;
  argTypes3[1] = 0;

  args3 = (void **)malloc(count3 * sizeof(void *));
  args3[0] = (void *)a3;

  /* prepare the arguemtns for f4 */
  char *a4 = "non_exist_file_to_be_printed";
  int count4 = 1;
  int argTypes4[count4 + 1];
  void **args4;

  argTypes4[0] = (1 << ARG_INPUT) | (ARG_CHAR << 16) | strlen(a4);
  argTypes4[1] = 0;

  args4 = (void **)malloc(count4 * sizeof(void *));
  args4[0] = (void *)a4;

  /* rpcCalls */
  int s0 = rpcCall("f0", argTypes0, args0);
  /* test the return f0 */
  printf("\nEXPECTED return of f0 is: %d\n", a0 + b0);
  if (s0 >= 0) {
    printf("ACTUAL return of f0 is: %d\n", *((int *)(args0[0])));
  }
  else {
    printf("Error: %d\n", s0);
  }


  int s1 = rpcCall("f1", argTypes1, args1);
  /* test the return of f1 */
  printf("\nEXPECTED return of f1 is: %ld\n", a1 + b1 * c1 - d1);
  if (s1 >= 0) {
    printf("ACTUAL return of f1 is: %ld\n", *((long *)(args1[0])));
  }
  else {
    printf("Error: %d\n", s1);
  }


  int s2 = rpcCall("f2", argTypes2, args2);
  /* test the return of f2 */
  printf("\nEXPECTED return of f2 is: 31234\n");
  if (s2 >= 0) {
    printf("ACTUAL return of f2 is: %s\n", (char *)args2[0]);
  }
  else {
    printf("Error: %d\n", s2);
  }


  int s3 = rpcCall("f3", argTypes3, args3);
  /* test the return of f3 */
  printf(
    "\nEXPECTED return of f3 is: 110 109 108 107 106 105 104 103 102 101 11\n"
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

  int s4 = rpcCall("f4", argTypes4, args4);
  /* test the return of f4 */
  printf("\ncalling f4 to print an non existed file on the server");
  printf("\nEXPECTED return of f4: some integer other than 0");
  printf("\nACTUAL return of f4: %d\n", s4);

  /* rpcTerminate */
  printf("\ndo you want to terminate? y/n: ");
  if (getchar() == 'y')
    rpcTerminate();

  test_f5();
  test_f6();
  test_f7();

  /* end of client.c */
  return 0;
}



#include "test/server_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>



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


/* return: OUT; a, b: IN */
int f0(int a, int b) {

	sleep(20);
  return a + b;
}


/* returns: OUT; a, b, c, d: IN */
long f1(char a, short b, int c, long d) {

  return a + b * c - d;
}


/* return string is the concatenation of the integer
   part of the float and the interger part of the double
   return: OUT string; a, b: IN */

char* f2(float a, double b) {

  float ai;
  double bi;
  char *str1;
  char *str2;

  a = modff(a, &ai);
  b = modf(b, &bi);

  str1 = (char *)malloc(100);

  sprintf(str1, "%lld%lld", (long long)ai, (long long)bi);

  return str1;
}


/*
 * bubble sort
 * the first element in the array indicates the size of the array
 * a: INOUT array
 */


/*
 * print file named by a
 * a: IN array
 */

void f4(char a[]) {

  /* print file a to a printer */
}


int f0_Skel(int *argTypes, void **args) {

  *(int *)args[0] = f0(*(int *)args[1], *(int *)args[2]);
  return 0;
}

int f1_Skel(int *argTypes, void **args) {

  *((long *)*args) = f1( *((char *)(*(args + 1))),
		        *((short *)(*(args + 2))),
		        *((int *)(*(args + 3))),
		        *((long *)(*(args + 4))) );

  return 0;
}

int f2_Skel(int *argTypes, void **args) {

  /* (char *)*args = f2( *((float *)(*(args + 1))), *((double *)(*(args + 2))) ); */
  *args = f2( *((float *)(*(args + 1))), *((double *)(*(args + 2))) );

  return 0;
}


/*
 * this skeleton doesn't do anything except returns
 * a negative value to mimic an error during the
 * server function execution, i.e. file not exist
 */
int f4_Skel(int *argTypes, void **args) {

  return -1; /* can not print the file */
}


void f3(long* input) {
  long size = input[0];
  long tmp = 0;

  for (int i = 0; i < size - 1; i++) {
    tmp = input[10 - i];
    input[10 - i] = input[i];
    input[i] = tmp;
  }
}

int f3_Skel(int *argTypes, void **args) {

  f3((long *)(*args));
  return 0;
}



int main(int argc, char *argv[]) {

  /* create sockets and connect to the binder */
  rpcInit();

  // Test function overload
  int count2 = 1;
  int argTypes2[count2 + 1];
  argTypes2[0] = (1 << ARG_OUTPUT) | (ARG_CHAR << 16) | 100;
  argTypes2[1] = (1 << ARG_INPUT) | (ARG_FLOAT << 16);
  argTypes2[2] = (1 << ARG_INPUT) | (ARG_FLOAT << 16); // The type is changed from double to float
  argTypes2[3] = 0;
  //rpcRegister("f2", argTypes2, *f2_Skel_2);

  // Testing same function call (f3) registered by two servers
  /*
   * f3 takes an array of long.
  */
  int count3 = 1;
  int argTypes3[count3 + 1];
  argTypes3[0] = (1 << ARG_OUTPUT) | (1 << ARG_INPUT) | (ARG_LONG << 16) | 11;
  argTypes3[1] = 0;
  rpcRegister("f3", argTypes3, *f3_Skel);

  // Testing same function call (f20) registered twice with different skeletons
  int count20 = 2;
  int argTypes20[count20 + 1];
  argTypes20[0] = (1 << ARG_INPUT) | (ARG_SHORT << 16) | 1;
  argTypes20[1] = (1 << ARG_OUTPUT) | (ARG_SHORT << 16) | 2;
  argTypes20[2] = 0;
  //rpcRegister("f20", argTypes20, *f20_Skel);

  //rpcRegister("f20", argTypes20, *f20_Skel_2);

  /* call rpcExecute */
  rpcExecute();

  /* return */
  return 0;
}

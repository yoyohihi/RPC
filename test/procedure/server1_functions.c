#include "../server1_functions.h"
#include <stdio.h>
#include <string.h>

// Function implementations
int f0(int a, int b) {
  return a + b;
}

long f1(char a, short b, int c, long d) {
  return a + b * c - d;
}

char* f2(float a, double b) {

  char* ret = new char[5];
  ret[0] = '3';
  ret[1] = '1';
  ret[2] = '2';
  ret[3] = '3';

  if (a == 3.14159 && b == 1234.1001) {
    ret[4] = '4';
    return ret;
  }

  ret[4] = '5';

  return ret;
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

void f5(short* input, short* output) {
  output[0] = input[0];
  output[1] = input[0];
  return;
}

double f6() {
  return 3.14159265359;
}

void f7() {
  return;
}

// Skeletons
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

int f3_Skel(int *argTypes, void **args) {

  f3((long *)(*args));
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


int f5_Skel(int *argTypes, void **args) {
  f5((short *) (*args), (short *) (*(args + 1)));
  return 0;
}

int f6_Skel(int *argTypes, void **args) {
  *((double *) *args) = f6();
  return 0;
}

int f7_Skel(int *argTypes, void **args) {
  f7();
  return 0;
}
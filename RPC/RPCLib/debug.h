#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define debug(fmt,argv...) \
	do {\
		printf("\e[31mDEBUG: "fmt"\e[m\n",##argv); \
	}while(0)

#else
#define debug(fmt,argv...) \
	(void)0
#endif


#endif

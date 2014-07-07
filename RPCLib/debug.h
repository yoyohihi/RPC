#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#define IDEBUG (1)

#define INFO  (1)
#define ERROR (2)
#define DEBUG (3)

#define debug(type,fmt,argv...) \
	do {\
		switch (type) \
		{ \
		case INFO: \
		     printf("\e[34mINFO:  "fmt"\e[m\n",##argv); \
		     break; \
		case DEBUG: \
		     if (IDEBUG) \
		     { \
		    	 printf("\e[32mDEBUG: "fmt"\e[m\n",##argv); \
		     } \
		     break; \
		case ERROR: \
			printf("\e[31mERROR:  "fmt"\e[m\n",##argv); \
			break; \
		} \
	}while(0)



#endif

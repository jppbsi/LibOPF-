#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>

void Error(char *msg, char *func); /* It prints an error message and exits the program. */

double *AllocDoubleArray(int n); /* It allocates a double array of size n */

#endif
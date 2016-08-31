#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/*--------- Common definitions -----------*/
#define NIL -1
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.e-14
#define RNMX (1.0-EPS)

/*--------- Common operations -------------*/
#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y))?(x):(y))
#endif

/*--------- Messages -------------*/
void Error(char *msg, char *func); /* It prints an error message and exits the program. */

/*--------- Memory Allocation -------------*/
double *AllocDoubleArray(int n); /* It allocates a double array of size n. */
int *AllocIntArray(int n); /* It allocates an integer array of size n. */

/*------------ Number generation -----------*/
double ran(int *idum); /* It generates a random number. */
int seedrandinter(int seed); /* It initializes the random number generator. */
int RandomInteger(int low, int high); /* It returns a random integer number uniformly distributed within [low,high]. */
double RandomDouble(double low, double high); /* It returns a random double number uniformly distributed within [low,high]. */

#endif
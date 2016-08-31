/*
  Copyright (C) <2016> <Alexandre Xavier Falc‹o and Jo‹o Paulo Papa>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  please see full copyright in COPYING file.
  -------------------------------------------------------------------------
  written by A.X. Falc‹o <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Aug 30th 2016

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.
*/

#include "common.h"

/*--------- Messages -------------*/
/* It prints an error message and exits the program.
Parameters:
msg: message to the user
func: function where the error has occurred */
void Error(char *msg, char *func){
    fprintf(stderr,"Error: %s @%s.\n", msg, func);
    exit(-1);
}

/*--------- Memory Allocation -------------*/
/* It allocates a float array of size n.
Parameters:
n: size of the array */
float *AllocFloatArray(int n){
    float *v = NULL;
    
    v = (float *)malloc(n*sizeof(float));
    if(!v) Error("Cannot allocate memory space", "AllocDoubleArray");
  
    return(v);
}

/* It allocates an integer array of size n.
Parameters:
n: size of the array */
int *AllocIntArray(int n){
    int *v = NULL;
    
    v = (int *)malloc(n*sizeof(int));
    if(!v) Error("Cannot allocate memory space", "AllocIntArray");
  
    return(v);
}

/*------------ Number generation -----------*/
/* The source code to generate random numbers was taken from http://www.physics.drexel.edu/courses/Comp_Phys/Physics-306/random.c. */

static int randx = 0;

/* It generates a random number.
Parameters:
idum: input seed number */
float ran(int *idum){
    int j;
    int k;
    static int idum2 = 123456789;
    static int iy = 0;
    static int iv[NTAB];
    float temp;

    if (*idum <= 0){
	if (-(*idum) < 1)
	    *idum = 1;
	else
	    *idum = -(*idum);
	idum2 = (*idum);

	for (j = NTAB+7; j >= 0; j--){
	    k = (*idum)/IQ1;
	    *idum = IA1*(*idum-k*IQ1) - k*IR1;
	    if (*idum < 0) *idum += IM1;
	    if (j < NTAB) iv[j] = *idum;
	}
	iy = iv[0];
    }
    k = (*idum)/IQ1;
    *idum = IA1*(*idum-k*IQ1) - k*IR1;
    if (*idum < 0) *idum += IM1;

    k = idum2/IQ2;
    idum2 = IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;

    j = iy/NDIV;
    iy = iv[j] - idum2;
    iv[j] = *idum;
    if (iy < 1) iy += IMM1;

    if ((temp = AM*iy) > RNMX)
	return RNMX;
    else
	return temp;
}

/* It initializes the random number generator.
Parameters:
seed: seed number */
int seedrandinter(int seed){	
    if (seed == 0) seed = (int)time(NULL);
					
    randx = -abs(seed);
    return seed;	
}

/* It returns a random integer number uniformly distributed within [low,high].
Parameters:
low: lower boundary
high: upper boundary */
int RandomInteger(int low, int high){	
    if (randx == 0) seedrandinter(0);
    return (int)(low + (high-low)*((float)ran(&randx)));
}

/* It returns a random float number uniformly distributed within [low,high].
Parameters:
low: lower boundary
high: upper boundary */
float RandomFloat(float low, float high){	
    if (randx == 0) seedrandinter(0);
    return low + (high-low)*((float)ran(&randx));
}
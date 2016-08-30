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

/* It prints an error message and exits the program.
Parameters:
msg: message to the user
func: function where the error has occurred */
void Error(char *msg, char *func){
    fprintf(stderr,"Error: %s @%s.\n", msg, func);
    exit(-1);
}

/* It allocates a double array of size n.
Parameters:
n: size of the array */
double *AllocDoubleArray(int n){
    double *v = NULL;
    
    v = (double *)malloc(n*sizeof(double));
    if(!v) Error("Cannot allocate memory space", "AllocDoubleArray");
  
    return(v);
}

/*
  Copyright (C) <2016> <Alexandre Xavier Falco and Joo Paulo Papa>

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
  written by A.X. Falco <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Aug 30th 2016

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.
*/

#include "set.h"

/*--------- Memory Allocation -------------*/
/* It creates a set.
S: pointer to the set
elem: element to be inserted */
void InsertSet(Set **S, int elem){
  Set *p = NULL;

  p = (Set *)malloc(sizeof(Set));
  
  if(!p) Error("Cannot allocate memory space","InsertSet");
  
  if(*S == NULL){
    p->elem  = elem;
    p->next  = NULL;
  }else{
    p->elem  = elem;
    p->next  = *S;
  }
  *S = p;
}

/* It deallocates a set.
Parameters:
S: pointer to the set */
void DestroySet(Set **S){
    Set *p = NULL;
    
    while(*S != NULL){
        p = *S;
        *S = p->next;
        free(p);
    } 
}

/*--------- Auxiliary Functions -------------*/
/* It removes an element from the set.
Parameters:
S: pointer to the set */
int RemoveSet(Set **S){
    Set *p = NULL;
    int elem = NIL;

    if (*S){
        p = *S;
        elem = p->elem;
        *S = p->next;
        free(p);
    }
    
    return(elem);
}

/* It gets the size of the set.
Parameters:
S: set */
int GetSetSize(Set *S){
    Set *aux = NULL;
    int size=0;
    
    aux = S;
    while(aux){
        size++;
        aux = aux->next;
    }
    
    return size;
}

/* It makes a copy of the set.
Parameters:
S: set to be coppied */
Set *CloneSet(Set *S){
    if(!S) Error("Invalid input", "CloneSet");
    
    Set *tmp = NULL, *C = NULL, **tail = NULL;
    int p;
    
    tmp = S;
    p = tmp->elem;
    C = (Set *)malloc(sizeof(Set));
    C->elem = p;
    C->next = NULL;
    tail = &(C->next);
    tmp = tmp->next;

    while(tmp){
  	p = tmp->elem;
	*tail = (Set *)malloc(sizeof(Set));
	(*tail)->elem = p;
	(*tail)->next = NULL;
	tail = &((*tail)->next);
        tmp = tmp->next;
    }
    
    return C;
}
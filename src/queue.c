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

#include "queue.h"

/*--------- Memory Allocation -------------*/
/* It creates an integer-valued queue.
Parameters:
nbuckets: number of buckets of the queue
nelems: number of elements in each bucket
value: pointer to the values to be added in the queue */
Queue *CreateQueue(int nbuckets, int nelems, int *value){
    Queue *Q = NULL;
    
    if(nbuckets < 1 || nelems < 1|| !value) Error("Invalid input", "CreateQueue");
    
    Q = (Queue *)malloc(1*sizeof(Queue));
    if(!Q) Error ("Cannot allocate memory space", "CreateQueue");
    
    Q->C.first = NULL; Q->C.first = (int *)malloc((nbuckets+1)*sizeof(int));
    Q->C.last = NULL; Q->C.last = (int *)malloc((nbuckets+1)*sizeof(int));
    Q->C.nbuckets = nbuckets;
    if(!Q->C.first || !Q->C.last) Error("Cannot allocate memory space", "CreateQueue");
    
    Q->L.elem = NULL; Q->L.elem = (QNode *)malloc(nelems*sizeof(QNode));
    Q->L.nelems = nelems;
    Q->L.value   = value;
    if(!Q->L.elem) Error("Cannot allocate memory space", "CreateQueue");
    ResetQueue(Q);
    
    return Q;   
}

/* It deallocates a queue.
Parameters:
Q: pointer to the queue to be deallocated */
void DestroyQueue(Queue **Q){
    Queue *aux = NULL;

    aux = *Q;
    if(!aux) Error("Invalid input", "DestroyQueue");
    
    if (aux->C.first != NULL) free(aux->C.first);
    if (aux->C.last  != NULL) free(aux->C.last);
    if (aux->L.elem  != NULL) free(aux->L.elem);
    free(aux);
    *Q = NULL;
}

/*--------- Auxiliary Functions -------------*/
/* It resets the queue.
Parameters:
Q: queue to be reset */
void ResetQueue(Queue *Q){
    
    if(!Q) Error("Invalid input", "ResetQueue");
    
    int i;

    Q->C.minvalue = INT_MAX;
    Q->C.maxvalue = INT_MIN;
    SetTieBreak(Q,FIFOBREAK);
    SetRemovalPolicy(Q,MINVALUE);
    
    for (i = 0; i < Q->C.nbuckets+1; i++)
        Q->C.first[i]=Q->C.last[i]=NIL;

    for (i = 0; i < Q->L.nelems; i++){
        Q->L.elem[i].next =  Q->L.elem[i].prev = NIL;
        Q->L.elem[i].color = WHITE;
    }
}

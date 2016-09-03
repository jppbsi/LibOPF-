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

  This program is a collection of functions to create, destroy, and
  manipulate a priority queue.

  A priority queue Q consists of two data structures: a circular
  queue C and a table L that encodes all possible doubly-linked
  lists.

  Q requires that the maximum possible increment along the paths be a
  non-negative integer less than the number of buckets in C. An extra
  bucket is created to store infinity values (positive and negative)
  for the LIFO policy. The queue size increases dynamically whenever
  (maxvalue-minvalue) > (nbuckets-1).

  Q->C.first[i] gives the first element that is in bucket i.
  Q->C.last[i]  gives the last  element that is in bucket i.
  Q->C.nbuckets gives the number of buckets in C.
  Q->C.minvalue  gives the minimum value of a node in queue.
  Q->C.maxvalue  gives the maximum value of a node in queue.
  Q->C.tiebreak gives the FIFO or LIFO tie breaking policy
  Q->C.removal_policy gives the MINVALUE or MAXVALUE removal policy

  All possible doubly-linked lists are represented in L. Each bucket
  contains a doubly-linked list that is treated as a FIFO.

  Q->L.elem[i].next: the next element to i
  Q->L.elem[i].prev: the previous element to i
  Q->L.elem[i].color: the color of i (WHITE=never inserted, GRAY=inserted,
  BLACK=removed)
  Q->L.nelems: gives the total number of elements that can be
  inserted in Q (It is usually the number of pixels in a given image
  or the number of nodes in a graph)
  Q->L.value[i]: gives the value of element i in the graph.

  Insertions and updates are done in O(1).
  Removal may take O(K+1), where K+1 is the number of buckets.
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

/* It empties the queue.
Parameters:
Q: queue to be emptied */
int EmptyQueue(Queue *Q){
    
    if(!Q) Error("Invalid input", "EmptyQueue");
    
    int last,current;

    if(Q->C.removal_policy == MINVALUE) current = Q->C.minvalue%Q->C.nbuckets;
    else current = Q->C.nbuckets-1-(Q->C.maxvalue%Q->C.nbuckets);

    if(Q->C.first[current] != NIL) return 0;

    last = current;
    current = (current+1)%(Q->C.nbuckets);

    while((Q->C.first[current] == NIL) && (current != last))
        current = (current + 1) % (Q->C.nbuckets);

    if(Q->C.first[current] == NIL)
        if (Q->C.first[Q->C.nbuckets] == NIL) return(1);

    return 0;
}

/* It grows the queue.
Parameters:
Q: pointer do the queue
nbuckets: number of additional buckets */
Queue *GrowQueue(Queue **Q, int nbuckets){
    
    if(!(*Q) || nbuckets < 1) Error("Invalid input", "InsertGQueue");
    
    Queue *Q1 = NULL;
    int i,bucket;
    
    Q1 = CreateQueue(nbuckets, (*Q)->L.nelems, (*Q)->L.value);
    
    if(!Q1) Error("Cannot allocate memory space", "GrowQueue");
    
    Q1->C.minvalue = (*Q)->C.minvalue;
    Q1->C.maxvalue = (*Q)->C.maxvalue;
    Q1->C.tiebreak = (*Q)->C.tiebreak;
    Q1->C.removal_policy = (*Q)->C.removal_policy;
    
    for(i = 0; i<(*Q)->C.nbuckets; i++){
        if((*Q)->C.first[i] != NIL){
            bucket = (*Q)->L.value[(*Q)->C.first[i]]%Q1->C.nbuckets;
            Q1->C.first[bucket] = (*Q)->C.first[i];
            Q1->C.last[bucket] = (*Q)->C.last[i];
        }
    }
    
    if((*Q)->C.first[(*Q)->C.nbuckets] != NIL){
        bucket = Q1->C.nbuckets;
        Q1->C.first[bucket] = (*Q)->C.first[(*Q)->C.nbuckets];
        Q1->C.last[bucket] = (*Q)->C.last[(*Q)->C.nbuckets];
    }

    for(i = 0; i < (*Q)->L.nelems; i++)
        Q1->L.elem[i] = (*Q)->L.elem[i];

    DestroyQueue(Q);
    
    return Q1;
}

/* It inserts an element in the queue.
Parameters:
Q: pointer to the queue
elem: element to be inserted */
void InsertQueue(Queue **Q, int elem){
    
    if(!(*Q)) Error("Invalid input", "InsertQueue");
    
    int bucket, minvalue = (*Q)->C.minvalue, maxvalue = (*Q)->C.maxvalue;

    if(((*Q)->L.value[elem]==INT_MAX)||((*Q)->L.value[elem]==INT_MIN)) bucket = (*Q)->C.nbuckets;
    else{

        if((*Q)->L.value[elem] < minvalue) minvalue = (*Q)->L.value[elem];
        if((*Q)->L.value[elem] > maxvalue) maxvalue = (*Q)->L.value[elem];
        if((maxvalue-minvalue) > ((*Q)->C.nbuckets-1)) (*Q) = GrowQueue(Q,2*(maxvalue-minvalue)+1);
        if((*Q)->C.removal_policy == MINVALUE) bucket = (*Q)->L.value[elem]%(*Q)->C.nbuckets;
        else bucket = (*Q)->C.nbuckets-1-((*Q)->L.value[elem]%(*Q)->C.nbuckets);
        (*Q)->C.minvalue = minvalue;
        (*Q)->C.maxvalue = maxvalue;
    }
    
    if((*Q)->C.first[bucket] == NIL){
        (*Q)->C.first[bucket] = elem;
        (*Q)->L.elem[elem].prev = NIL;
    }
    else{
        (*Q)->L.elem[(*Q)->C.last[bucket]].next = elem;
        (*Q)->L.elem[elem].prev = (*Q)->C.last[bucket];
    }

    (*Q)->C.last[bucket] = elem;
    (*Q)->L.elem[elem].next = NIL;
    (*Q)->L.elem[elem].color = GRAY;
}

/* It pops from the queue.
Parameters:
Q: queue */
int RemoveQueue(Queue *Q){
    if(!Q) Error("Invalid input", "RemoveQueue");
    
    int elem=NIL, next, prev;
    int last, current;

    if(Q->C.removal_policy == MINVALUE) current = Q->C.minvalue%Q->C.nbuckets;
    else current = Q->C.nbuckets-1-(Q->C.maxvalue%Q->C.nbuckets);

    /* It moves to next element */
    if(Q->C.first[current] == NIL){
        last = current;
        current = (current + 1) % (Q->C.nbuckets);

        while((Q->C.first[current] == NIL) && (current != last))
            current = (current + 1) % (Q->C.nbuckets);

        if(Q->C.first[current] != NIL){
            if(Q->C.removal_policy==MINVALUE) Q->C.minvalue = Q->L.value[Q->C.first[current]];
            else Q->C.maxvalue = Q->L.value[Q->C.first[current]];
        }
        else{
            if(Q->C.first[Q->C.nbuckets] != NIL){
                current = Q->C.nbuckets;
                if(Q->C.removal_policy==MINVALUE) Q->C.minvalue = Q->L.value[Q->C.first[current]];
                else Q->C.maxvalue = Q->L.value[Q->C.first[current]];
            }
            else Error("Queue is empty","RemoveQueue");
        }
    }

    if(Q->C.tiebreak == LIFOBREAK){
        elem = Q->C.last[current];
        prev = Q->L.elem[elem].prev;
        if (prev == NIL)           /* there was a single element in the list */
            Q->C.last[current] = Q->C.first[current]  = NIL;
        else{
            Q->C.last[current]   = prev;
            Q->L.elem[prev].next = NIL;
        }
    }
    else{   /* Assume FIFO policy for breaking ties */
        elem = Q->C.first[current];
        next = Q->L.elem[elem].next;
        if(next == NIL)           /* there was a single element in the list */
            Q->C.first[current] = Q->C.last[current]  = NIL;
        else{
            Q->C.first[current] = next;
            Q->L.elem[next].prev = NIL;
        }
    }

    Q->L.elem[elem].color = BLACK;

    return elem;
}

/* It removes a specific element from the queue.
Parameters:
Q: queue
elem: element to be removed */
void RemoveQueueElem(Queue *Q, int elem){
    if(!Q) Error("Invalid input", "RemoveQueueElem");
    
    int prev,next,bucket;

    if((Q->L.value[elem] == INT_MAX) || (Q->L.value[elem] == INT_MIN)) bucket = Q->C.nbuckets;
    else{
        if(Q->C.removal_policy == MINVALUE) bucket = Q->L.value[elem]%Q->C.nbuckets;
        else bucket = Q->C.nbuckets-1-(Q->L.value[elem]%Q->C.nbuckets);
    }

    prev = Q->L.elem[elem].prev;
    next = Q->L.elem[elem].next;

    /* if elem is the first element */
    if(Q->C.first[bucket] == elem){
        Q->C.first[bucket] = next;
        if (next == NIL) /* elem is also the last one */
            Q->C.last[bucket] = NIL;
        else
            Q->L.elem[next].prev = NIL;
    }
    else{    /* elem is in the middle or it is the last */
        Q->L.elem[prev].next = next;
        if (next == NIL) /* if it is the last */
            Q->C.last[bucket] = prev;
        else
            Q->L.elem[next].prev = prev;
    }
    
    Q->L.elem[elem].color = BLACK;
}

/* It updates a vaue in the queue.
Parameters:
Q: pointer to the queue
elem: element to be updated
newvalue: value of the new element */
void UpdateQueue(Queue **Q, int elem, int newvalue){
    if(!(*Q) ||  elem < 0) Error("Invalid input", "UpdateQueue");
    
    RemoveQueueElem(*Q, elem);
    (*Q)->L.value[elem] = newvalue;
    InsertQueue(Q, elem);
}
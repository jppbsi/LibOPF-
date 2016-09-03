#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "common.h"

typedef struct _Qnode{ 
  int  next;
  int  prev;
  char color;
}QNode;

typedef struct _Doublylinkedlists{
  QNode *elem;  /* all possible doubly-linked lists of the circular queue */
  int nelems;  /* total number of elements */
  int *value;   /* the value of the nodes in the graph */
}DoublyLinkedLists; 

typedef struct _Circularqueue { 
  int  *first;   /* list of the first elements of each doubly-linked list */
  int  *last;    /* list of the last  elements of each doubly-linked list  */
  int  nbuckets; /* number of buckets in the circular queue */
  int  minvalue;  /* minimum value of a node in queue */
  int  maxvalue;  /* maximum value of a node in queue */
  char tiebreak; /* 1 is LIFO, 0 is FIFO (default) */
  char removal_policy; /* 0 is MINVALUE and 1 is MAXVALUE */
}CircularQueue;

typedef struct _Queue{ /* Priority queue by Dial implemented as proposed by A. Falcao */
  CircularQueue C;
  DoublyLinkedLists L;
}Queue;

/*--------- Memory Allocation -------------*/
Queue *CreateQueue(int nbuckets, int nelems, int *value); /* It creates an integer-valued queue. */
void DestroyQueue(Queue **Q); /* It deallocates a queue. */

/*--------- Auxiliary Functions -------------*/
void ResetQueue(Queue *Q); /* It resets the queue. */
int EmptyQueue(Queue *Q); /* It empties the queue. */
Queue *GrowQueue(Queue **Q, int nbuckets); /* It grows the queue. */
void InsertGQueue(Queue **Q, int elem); /* It inserts an element in the queue. */
int RemoveQueue(Queue *Q); /* It pops from the queue. */
void RemoveQueueElem(Queue *Q, int elem); /* It removes a specific element from the queue. */
void UpdateQueue(Queue **Q, int elem, int newvalue); /* It updates a vaue in the queue. */

#endif
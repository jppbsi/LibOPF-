#ifndef _HEAP_H_
#define _HEAP_H_

#include "common.h"

/*--------- Common operations -------------*/
#define HEAP_DAD(i) ((i - 1) / 2)
#define HEAP_LEFTSON(i) (2 * i + 1)
#define HEAP_RIGHTSON(i) (2 * i + 2)

typedef struct _Heap {
  float *cost;
  char *color;
  int *pixel;
  int *pos;
  int last;
  int n;
  char removal_policy; /* 0 is MINVALUE and 1 is MAXVALUE */
}Heap;

/*--------- Memory Allocation -------------*/
Heap *CreateHeap(int n, float *cost); /* It allocates a heap. */
void DestroyHeap(Heap **H); /* It deallocates a heap. */

/*--------- Auxiliary Functions -------------*/
void ResetHeap(Heap *H); /* It resets the heap. */
void SetRemovalPolicyHeap(Heap *H, char policy); /* It sets the removal policy. */
char IsFullRealHeap(Heap *H); /* It verifies whether the heap is full or not. */
char IsEmptyRealHeap(Heap *H); /* It verifies whether the heap is empty or not. */
void GoUpHeap(Heap *H, int i); /* It goes upwards in the heap. */
void GoDownHeap(Heap *H, int i); /* It goes downwards in the heap. */
char InsertHeap(Heap *H, int p); /* It inserts a new heap node p. */
void UpdateHeap(Heap *H, int p, float value); /* It updates the heap value at position p. */
char RemoveHeap(Heap *H, int *p); /* It removes heap node p.*/

#endif